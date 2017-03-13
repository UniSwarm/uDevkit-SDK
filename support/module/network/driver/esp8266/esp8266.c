#include "esp8266.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include <xc.h>

#include "driver/uart.h"
#include "sys/buffer.h"

// data receive from esp
uint8_t esp_socket = 0;
uint16_t sizeRecPacket = 0;
uint16_t idRecPacket = 0;
uint8_t recPacketFlag = 0;
char /*__attribute__((far))*/ recPacket[2049];

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

    FSM_PLUS,

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

uint8_t esp_config = 0;

void esp_parse(char rec);

rt_dev_t esp_uart;

STATIC_BUFFER(buff, 100);

void esp_uart_init()
{
    // uart init
    esp_uart = uart_getFreeDevice();
    uart_setBaudSpeed(esp_uart, 115200);
    uart_setBitConfig(esp_uart, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(esp_uart);
}

#define esp_write(data, size) uart_write(esp_uart, (data), (size))
#define esp_send_cmd(cmd) uart_write(esp_uart, (cmd), strlen(cmd))
#define esp_send_cmddat(cmd, size) uart_write(esp_uart, (cmd), (size))

void esp_init()
{
    esp_uart_init();
    
    // buffer cmd construction init
    STATIC_BUFFER_INIT(buff, 100);
}

void esp_task()
{
    char buffRx[200];
    ssize_t read_size;
    
    // read esp uart
	read_size = uart_read(esp_uart, buffRx, 200);
    if (read_size > 0)
    {
        int i;
        char *buffPtr;
        // parse it
        buffPtr = buffRx;
        for (i=0; i<read_size; i++)
        {
            printf("%c %d fsm: %d\n",*buffPtr,*buffPtr,wifistatus);
            esp_parse(*buffPtr);
            buffPtr++;
        }
        printf("state:%d\n",state);
    }
    
    // config
    if (esp_config < 4)
    {
        switch (esp_config)
        {
        case 0:
            esp_send_cmd("ATE0\r\n");
            esp_config++;
            break;
        case 1:
            if (state == WIFI_STATE_OK)
            {
                esp_config++;
                state = WIFI_STATE_NONE;
            }
            break;
        case 2:
            esp_send_cmd("AT+CIPMUX=1\r\n");
            esp_config++;
            break;
        case 3:
            if (state == WIFI_STATE_OK)
            {
                esp_config++;
                state = WIFI_STATE_NONE;
            }
            break;
        }
    }
}

void esp_parse(char rec)
{
    switch(wifistatus)
    {
        case FSM_UNKNOW:
            if (rec == '\r')
                wifistatus = FSM_WAITING_VALIDATE;
            else
                wifistatus = FSM_UNKNOW;
            break;
        case FSM_WAITING_VALIDATE:
            if (rec == '\n')
            {
                //validate
                if(pendingState!=WIFI_STATE_NONE) state = pendingState;
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
            if (rec == 'I') wifistatus = FSM_IPD_I; else wifistatus = FSM_UNKNOW;
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
                esp_socket = rec - '0';
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
            if(idRecPacket >= sizeRecPacket)
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

char * esp_protectstr(char * destination, const char * source)
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

void wait_ok()
{
    while(state != WIFI_STATE_OK);
    state = WIFI_STATE_NONE;
}

WIFI_STATE get_state()
{
    return state;
}

uint8_t getRecSocket()
{
    return esp_socket;
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

uint8_t esp_open_tcp_socket(char *ip_domain, uint16_t port)
{
    char protected[64];
    
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSTART=\"TCP\",\"");
    
    esp_protectstr(protected, ip_domain);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",");
    buffer_aint(&buff, port);

    esp_send_cmddat(buff.data, buff.size);
    return 0;
}

uint8_t esp_open_udp_socket(char *ip_domain, uint16_t port, uint16_t localPort, uint8_t mode)
{
    char protected[64];
    
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSTART=\"UDP\",\"");
    
    esp_protectstr(protected, ip_domain);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",");
    buffer_aint(&buff, (int)port);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)localPort);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)mode);

    esp_send_cmddat(buff.data, buff.size);
    return 0;
}

void esp_set_mode(ESP_MODE mode)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CWMODE_CUR=");

    if(mode==ESP_MODE_AP) buffer_achar(&buff, '2');
    else if(mode==ESP_MODE_STA_AP) buffer_achar(&buff, '3');
    else buffer_achar(&buff, '1');

    buffer_astring(&buff, "\r\n");

    esp_send_cmddat(buff.data, buff.size);
}

uint8_t esp_connect_ap(char *ssid, char *pw)        // warning, be careful to special car, protect with backslash
{
    char protected[64];
    
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CWJAP_CUR=\"");
    
    esp_protectstr(protected, ssid);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\",\"");
    
    esp_protectstr(protected, pw);
    buffer_astring(&buff, protected);
    buffer_astring(&buff, "\"\r\n");

    esp_send_cmddat(buff.data, buff.size);
    return 0;
}

uint8_t esp_disconnect_ap()
{
    esp_send_cmd("AT+CWQAP\r\n");
    return 0;
}

void esp_close_socket(uint8_t sock)
{
    if(sock > 4)
        return;
    
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPCLOSE=");
    buffer_aint(&buff, sock);
    buffer_astring(&buff, "\r\n");
    
    esp_send_cmddat(buff.data, buff.size);
}

void esp_write_socket(uint8_t sock, char *data, uint16_t size)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSEND=");
    buffer_aint(&buff, (int)sock);
    buffer_achar(&buff, ',');
    buffer_aint(&buff, (int)size);
    buffer_astring(&buff, "\r\n");
    esp_send_cmddat(buff.data, buff.size);

    while(state != WIFI_STATE_SEND_DATA);
    state = WIFI_STATE_NONE;

    esp_write(data, size);
    while(state != WIFI_STATE_SEND_OK);
}

void esp_write_socket_string(uint8_t sock, char *str)
{
    esp_write_socket(sock, str, strlen(str)+1);
}

void esp_server_create(uint16_t port)
{
    buffer_clear(&buff);
    buffer_astring(&buff, "AT+CIPSERVER=1,");
    buffer_aint(&buff, (int)port);
    buffer_astring(&buff, "\r\n");
    esp_send_cmddat(buff.data, buff.size);
}

void esp_server_destroy()
{
    esp_send_cmd("AT+CIPSERVER=0\r\n");
}
