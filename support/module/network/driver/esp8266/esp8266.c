/**
 * @file esp8266.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date February 10, 2016, 09:32 PM
 *
 * @brief ESP8266 driver for RTProg network module
 */

#include "esp8266.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <board.h>

#include "driver/uart.h"
#include "sys/buffer.h"

// data receive from esp
uint8_t esp8266_socket = 0;
uint16_t sizeRecPacket = 0;
uint16_t idRecPacket = 0;
uint8_t recPacketFlag = 0;
char /*__attribute__((far))*/ recPacket[2049];
char esp8266_ip[16] = "";
char esp8266_ipid = 0;

typedef enum
{
    FSM_UNKNOW = 0,
    FSM_WAITING_VALIDATE,
    FSM_START,

    FSM_ready_r,
    FSM_ready_e,
    FSM_ready_a,
    FSM_ready_d,
    FSM_ready_y,

    FSM_OK_O,
    FSM_OK_K,

    FSM_SENDOK_S,
    FSM_SENDOK_E,
    FSM_SENDOK_N,
    FSM_SENDOK_D,
    FSM_SENDOK_Sp,
    FSM_SENDOK_O,
    FSM_SENDOK_K,

    FSM_ERROR_E,
    FSM_ERROR_R1,
    FSM_ERROR_R2,
    FSM_ERROR_O,
    FSM_ERROR_R3,

    FSM_FAIL_F,
    FSM_FAIL_A,
    FSM_FAIL_I,
    FSM_FAIL_L,

    FSM_PLUS,

    FSM_IP_C,
    FSM_IP_I,
    FSM_IP_F,
    FSM_IP_S,
    FSM_IP_R,
    FSM_IP_dP,
    FSM_IP_S2,
    FSM_IP_T,
    FSM_IP_A,
    FSM_IP_WIP,
    FSM_IP_IP,

    FSM_IPD_I,
    FSM_IPD_P,
    FSM_IPD_D,
    FSM_IPD_COMMA_1,
    FSM_IPD_SOCKET_DIGIT,
    FSM_IPD_COMMA_2,
    FSM_IPD_SIZE_DIGITS,
    FSM_PACKET_RX,
    FSM_RX_COMPLETE

} WIFIstatus;
volatile WIFIstatus wifistatus = FSM_START;

volatile WIFI_STATE pendingState = WIFI_STATE_NONE;
volatile WIFI_STATE state = WIFI_STATE_NONE;

uint8_t esp8266_config = 0;

void esp8266_parse(char rec);

rt_dev_t esp8266_uart;

STATIC_BUFFER(buff, 100);

void esp8266_uart_init()
{
    // uart init
    esp8266_uart = uart(ESP8266_UART);
    uart_open(esp8266_uart);
    uart_setBaudSpeed(esp8266_uart, 115200);
    uart_setBitConfig(esp8266_uart, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(esp8266_uart);
}

#define esp8266_write(data, size) uart_write(esp8266_uart, (data), (size))
#define esp8266_send_cmd(cmd) uart_write(esp8266_uart, (cmd), strlen(cmd))
#define esp8266_send_cmddat(cmd, size) uart_write(esp8266_uart, (cmd), (size))

void esp8266_init()
{
    esp8266_uart_init();

    // buffer cmd construction init
    STATIC_BUFFER_INIT(buff, 100);
}

void esp8266_task()
{
    char buffRx[200];
    ssize_t read_size;

    // read esp uart
	read_size = uart_read(esp8266_uart, buffRx, 200);
    if (read_size > 0)
    {
        int i;
        char *buffPtr;
        // parse it
        buffPtr = buffRx;
        for (i=0; i<read_size; i++)
        {
            esp8266_parse(*buffPtr);
            buffPtr++;
        }
        //printf("state:%d\n",state);
    }

    // config
    if ((esp8266_config>>1) < 7)
    {
        if (esp8266_config & 0x01)
        {
            if (state != WIFI_STATE_NONE)
            {
                esp8266_config++;
                state = WIFI_STATE_NONE;
            }
        }
        else
        {
            switch (esp8266_config>>1)
            {
            case 0:
                esp8266_send_cmd("ATE1\r\n");
                break;
            case 1:
                esp8266_send_cmd("AT+CIPMUX=1\r\n");
                break;
            case 2:
                esp8266_setMode(ESP8266_MODE_STA_AP);
                break;
            case 3:
                esp8266_connect_ap("iotRT", "iotwifiA");
                break;
            case 4:
                esp8266_ap_setConfig("rtnet", "pwd2017A", ESP8266_ECN_WPA2, 5);
                break;
            case 5:
                esp8266_server_create(80);
                break;
            case 6:
                esp8266_send_cmd("AT+CIFSR\r\n");
                break;
            }
            esp8266_config++;
        }
    }
}

void esp8266_parse(char rec)
{
    switch(wifistatus)
    {
        case FSM_UNKNOW:
            if (rec == '\n')
                wifistatus = FSM_START;
            else
                wifistatus = FSM_UNKNOW;
            break;
        case FSM_WAITING_VALIDATE:
            if (rec == '\n')
            {
                //validate
                if(pendingState!=WIFI_STATE_NONE)
                    state = pendingState;
                pendingState = WIFI_STATE_NONE;

                wifistatus = FSM_START;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;
        case FSM_START:
            if (rec == '\r')
                wifistatus = FSM_WAITING_VALIDATE;
            else if (rec == '+')
                wifistatus = FSM_PLUS;
            else if (rec == 'S')
                wifistatus = FSM_SENDOK_S;
            else if (rec == 'E')
                wifistatus = FSM_ERROR_E;
            else if (rec == 'r')
                wifistatus = FSM_ready_r;
            else if (rec == 'F')
                wifistatus = FSM_FAIL_F;
            else if (rec == '>')
            {
                state = WIFI_STATE_SEND_DATA;
                wifistatus = FSM_UNKNOW;
            }
            else if (rec == 'O')
                wifistatus = FSM_OK_O;
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_SENDOK_S:
            if (rec == 'E') wifistatus = FSM_SENDOK_E; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_E:
            if (rec == 'N') wifistatus = FSM_SENDOK_N; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_N:
            if (rec == 'D') wifistatus = FSM_SENDOK_D; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_D:
            if (rec == ' ') wifistatus = FSM_SENDOK_Sp; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_Sp:
            if (rec == 'O') wifistatus = FSM_SENDOK_O; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_O:
            if (rec == 'K') wifistatus = FSM_SENDOK_K; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_SENDOK_K:
            if (rec == '\r')
            {
                pendingState = WIFI_STATE_SEND_OK;
                wifistatus = FSM_WAITING_VALIDATE;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_ERROR_E:
            if (rec == 'R') wifistatus = FSM_ERROR_R1; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ERROR_R1:
            if (rec == 'R') wifistatus = FSM_ERROR_R2; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ERROR_R2:
            if (rec == 'O') wifistatus = FSM_ERROR_O; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ERROR_O:
            if (rec == 'R') wifistatus = FSM_ERROR_R3; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ERROR_R3:
            if (rec == '\r')
            {
                pendingState = WIFI_STATE_ERROR;
                wifistatus = FSM_WAITING_VALIDATE;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_FAIL_F:
            if (rec == 'A') wifistatus = FSM_FAIL_A; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_FAIL_A:
            if (rec == 'I') wifistatus = FSM_FAIL_I; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_FAIL_I:
            if (rec == 'L') wifistatus = FSM_FAIL_L; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_FAIL_L:
            if (rec == '\r')
            {
                pendingState = WIFI_STATE_FAIL;
                wifistatus = FSM_WAITING_VALIDATE;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_ready_r:
            if (rec == 'e') wifistatus = FSM_ready_e; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ready_e:
            if (rec == 'a') wifistatus = FSM_ready_a; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ready_a:
            if (rec == 'd') wifistatus = FSM_ready_d; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ready_d:
            if (rec == 'y') wifistatus = FSM_ready_y; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_ready_y:
            if (rec == '\r')
            {
                pendingState = WIFI_STATE_READY;
                wifistatus = FSM_WAITING_VALIDATE;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_OK_O:
            if (rec == 'K') wifistatus = FSM_OK_K; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_OK_K:
            if (rec == '\r')
            {
                pendingState = WIFI_STATE_OK;
                wifistatus = FSM_WAITING_VALIDATE;
            }
            else
                wifistatus = FSM_UNKNOW;
            break;

        case FSM_PLUS:
            if (rec == 'I') wifistatus = FSM_IPD_I;
            else if (rec == 'C') wifistatus = FSM_IP_C; // wait IP
            else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_C:
            if (rec == 'I') wifistatus = FSM_IP_I; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_I:
            if (rec == 'F') wifistatus = FSM_IP_F; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_F:
            if (rec == 'S') wifistatus = FSM_IP_S; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_S:
            if (rec == 'R') wifistatus = FSM_IP_R; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_R:
            if (rec == ':') wifistatus = FSM_IP_dP; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_dP:
            if (rec == 'S') wifistatus = FSM_IP_S2; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_S2:
            if (rec == 'T') wifistatus = FSM_IP_T; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_T:
            if (rec == 'A') wifistatus = FSM_IP_A; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_A:
            if (rec == 'I') wifistatus = FSM_IP_WIP; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IP_WIP:
            if (rec == '"')
            {
                wifistatus = FSM_IP_IP;
                esp8266_ipid = 0;
            }
            else if (rec == '\r') wifistatus = FSM_UNKNOW;
            else wifistatus = FSM_IP_WIP; // wait IP
            break;
        case FSM_IP_IP:
            if ((rec >= '0' && rec <= '9') || rec == '.')
                esp8266_ip[esp8266_ipid++] = rec;
            else
            {
                esp8266_ip[esp8266_ipid] = 0;
                wifistatus = FSM_UNKNOW;
            }
            break;
        case FSM_IPD_I:
            if (rec == 'P') wifistatus = FSM_IPD_P; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_P:
            if (rec == 'D') wifistatus = FSM_IPD_D; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_D:
            if (rec == ',') wifistatus = FSM_IPD_COMMA_1; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_COMMA_1:
            if (rec >= '0' && rec <= '9')
            {
                wifistatus = FSM_IPD_SOCKET_DIGIT;
                esp8266_socket = rec - '0';
            }
            else
                wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_SOCKET_DIGIT:
            if (rec == ',') wifistatus = FSM_IPD_COMMA_2; else wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_COMMA_2:
            if (rec >= '0' && rec <= '9')
            {
                wifistatus = FSM_IPD_SIZE_DIGITS;
                sizeRecPacket = (rec - '0');
            }
            else
                wifistatus = FSM_UNKNOW;
            break;
        case FSM_IPD_SIZE_DIGITS:
            if (rec == ':')
            {
                idRecPacket = 0;
                wifistatus = FSM_PACKET_RX;
            }
            else
            {
                if (rec >= '0' && rec <= '9')
                {
                    wifistatus = FSM_IPD_SIZE_DIGITS;
                    sizeRecPacket = sizeRecPacket * 10 + (rec - '0');
                }
                else
                    wifistatus = FSM_UNKNOW;
            }
            break;
        case FSM_PACKET_RX:
            recPacket[idRecPacket++] = rec;
            if (idRecPacket >= sizeRecPacket)
            {
                recPacketFlag=1;
                state = WIFI_STATE_RECEIVE_DATA;
                wifistatus = FSM_UNKNOW;
            }
            break;
        default:
            wifistatus = FSM_UNKNOW;
    }
}

char * esp8266_protectstr(char * destination, const char * source)
{
    char *ptr, *ptrsource;
    ptr = destination;
    ptrsource = (char *)source;

    while(*ptrsource!=0)
    {
        if(*ptrsource=='"' || *ptrsource==',' || *ptrsource=='\\')
            (*(ptr++))='\\';
        (*(ptr++))=*ptrsource;
        ptrsource++;
    }
    (*ptr) = 0;
    return destination;
}

WIFI_STATE get_state()
{
    return state;
}

uint8_t getRecSocket()
{
    return esp8266_socket;
}

char *getRecData()
{
    return recPacket;
}

uint16_t getRecSize()
{
    return sizeRecPacket;
}

uint8_t getRec()
{
    if(recPacketFlag==1)
    {
        recPacketFlag=0;
        return 1;
    }
    return 0;
}

uint8_t esp8266_open_tcp_socket(char *ip_domain, uint16_t port)
{
    char protected[64];

    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSTART=\"TCP\",\"");

    esp8266_protectstr(protected, ip_domain);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",");
    buffer_aint(&buff, port);

    esp8266_send_cmddat(buff.data, buff.size);
    return 0;
}

uint8_t esp8266_open_udp_socket(char *ip_domain, uint16_t port, uint16_t localPort, uint8_t mode)
{
    char protected[64];

    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSTART=\"UDP\",\"");

    esp8266_protectstr(protected, ip_domain);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",");
    buffer_aint(&buff, (int)port);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)localPort);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)mode);

    esp8266_send_cmddat(buff.data, buff.size);
    return 0;
}

void esp8266_setMode(ESP8266_MODE mode)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CWMODE_CUR=");

    if(mode==ESP8266_MODE_AP) buffer_achar(&buff, '2');
    else if(mode==ESP8266_MODE_STA_AP) buffer_achar(&buff, '3');
    else buffer_achar(&buff, '1');

    buffer_astring(&buff, "\r\n");

    esp8266_send_cmddat(buff.data, buff.size);
}

int esp8266_ap_setConfig(char *ssid, char *pw, ESP8266_ECN pw_ecn, uint8_t channel)
{
    char protected[64];

    if (pw_ecn != ESP8266_ECN_OPEN && strlen(pw) < 8)
        return -1; // password too short

    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CWSAP_CUR=\"");

    esp8266_protectstr(protected, ssid);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",\"");

    esp8266_protectstr(protected, pw);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",");

    buffer_aint(&buff, (int)channel);
    buffer_astring(&buff, ",");

    buffer_aint(&buff, (int)pw_ecn);
    buffer_astring(&buff, "\r\n");

    esp8266_send_cmddat(buff.data, buff.size);
    return 0;
}

uint8_t esp8266_connect_ap(char *ssid, char *pw)
{
    char protected[64];

    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CWJAP_CUR=\"");

    esp8266_protectstr(protected, ssid);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",\"");

    esp8266_protectstr(protected, pw);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\"\r\n");

    esp8266_send_cmddat(buff.data, buff.size);
    return 0;
}

uint8_t esp8266_disconnect_ap()
{
    esp8266_send_cmd("AT+CWQAP\r\n");
    return 0;
}

void esp8266_close_socket(uint8_t sock)
{
    if(sock > 4)
        return;

    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPCLOSE=");
    buffer_aint(&buff, sock);
    buffer_astring(&buff, "\r\n");

    esp8266_send_cmddat(buff.data, buff.size);
}

void esp8266_write_socket(uint8_t sock, char *data, uint16_t size)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSEND=");
    buffer_aint(&buff, (int)sock);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)size);
    buffer_astring(&buff, "\r\n");
    esp8266_send_cmddat(buff.data, buff.size);

    while(state != WIFI_STATE_SEND_DATA) esp8266_task();
    state = WIFI_STATE_NONE;

    esp8266_write(data, size);
    while(state != WIFI_STATE_SEND_OK) esp8266_task();
}

void esp8266_write_socket_string(uint8_t sock, char *str)
{
    esp8266_write_socket(sock, str, strlen(str)+1);
}

void esp8266_server_create(uint16_t port)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSERVER=1,");
    buffer_aint(&buff, (int)port);
    buffer_astring(&buff, "\r\n");
    esp8266_send_cmddat(buff.data, buff.size);
}

void esp8266_server_destroy()
{
    esp8266_send_cmd("AT+CIPSERVER=0\r\n");
}

char *getIp()
{
    return esp8266_ip;
}
