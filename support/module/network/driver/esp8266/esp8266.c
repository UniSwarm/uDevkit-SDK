/**
 * @file esp8266.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date February 10, 2016, 09:32 PM
 *
 * @brief ESP8266 driver in AT mode for RTProg network module
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
uint16_t esp8266_sizePacket = 0;
uint16_t esp8266_idPacket = 0;
uint8_t esp8266_flagPacket = 0;
char /*__attribute__((far))*/ esp8266_dataPacket[2049];

// station IP
char esp8266_ip[16] = "";
uint8_t esp8266_ipid = 0;
char esp8266_mac[18] = "";
uint8_t esp8266_macid = 0;

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
    FSM_IP_WMAC,
    FSM_IP_MAC,

    FSM_IPD_I,
    FSM_IPD_P,
    FSM_IPD_D,
    FSM_IPD_COMMA_1,
    FSM_IPD_SOCKET_DIGIT,
    FSM_IPD_COMMA_2,
    FSM_IPD_SIZE_DIGITS,
    FSM_PACKET_RX,
    FSM_RX_COMPLETE

} ESP8266_FSMSTATE;
volatile ESP8266_FSMSTATE esp8266_fsmState = FSM_START;

typedef enum
{
    ESP8266_STATE_NONE = 0,
    ESP8266_STATE_READY,
    ESP8266_STATE_OK,
    ESP8266_STATE_ERROR,
    ESP8266_STATE_FAIL,
    ESP8266_STATE_RECEIVE_DATA,
    ESP8266_STATE_SEND_DATA,
    ESP8266_STATE_SEND_OK
} ESP8266_STATE;
volatile ESP8266_STATE esp8266_pendingState = ESP8266_STATE_NONE;
volatile ESP8266_STATE esp8266_state = ESP8266_STATE_NONE;

typedef enum
{
    ESP8266_CMD_NONE = 0,
    ESP8266_CMD_CUSTOM,
    ESP8266_CMD_OPENTCP,
    ESP8266_CMD_OPENUDP,
    ESP8266_CMD_SETMODE,
    ESP8266_CMD_APCONFIG,
    ESP8266_CMD_CONNECTAP,
    ESP8266_CMD_DISCONNECTAP,
    ESP8266_CMD_CLOSESOCKET,
    ESP8266_CMD_WRITESOCK_REQ,
    ESP8266_CMD_WRITESOCK_DATA,
    ESP8266_CMD_SERVERCREATE,
    ESP8266_CMD_SERVERDESTROY
} ESP8266_CMD;
volatile ESP8266_CMD esp8266_currentCmd = ESP8266_CMD_NONE;

uint8_t esp8266_config = 0;

void esp8266_parse(char rec);

rt_dev_t esp8266_uart;

STATIC_BUFFER(esp8266_txBuff, 100);

/**
 * @brief Internal function to initailise UART to ESP8266
 */
void esp8266_uart_init()
{
    // uart init
    esp8266_uart = uart(ESP8266_UART);
    uart_open(esp8266_uart);
    uart_setBaudSpeed(esp8266_uart, 115200);
    uart_setBitConfig(esp8266_uart, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(esp8266_uart);
}

/**
 * @brief Initailise driver for ESP8266
 */
void esp8266_init()
{
    esp8266_uart_init();

    // buffer cmd construction init
    STATIC_BUFFER_INIT(esp8266_txBuff, 100);
}

/**
 * @brief Task to call periodically
 */
void esp8266_task()
{
    char esp8266_rxBuff[200];
    ssize_t read_size;

    // read esp uart response and parse it
    read_size = uart_read(esp8266_uart, esp8266_rxBuff, 200);
    if (read_size > 0)
    {
        int i;
        char *esp8266_txBuffPtr;
        // parse it
        esp8266_txBuffPtr = esp8266_rxBuff;
        for (i = 0; i < read_size; i++)
        {
            esp8266_parse(*esp8266_txBuffPtr);
            esp8266_txBuffPtr++;
        }
    }

    // send base configuration (begining only)
    if ((esp8266_config >> 1) < 7)
    {
        if (esp8266_config & 0x01)
        {
            if (esp8266_state != ESP8266_STATE_NONE)
            {
                esp8266_config++;
                esp8266_state = ESP8266_STATE_NONE;
            }
        }
        else
        {
            switch (esp8266_config >> 1)
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

/**
 * @brief Internal function to parse response of AT commands
 * @param rec new char to parse
 */
void esp8266_parse(char rec)
{
    switch (esp8266_fsmState)
    {
    case FSM_UNKNOW:
        if (rec == '\n')
            esp8266_fsmState = FSM_START;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_WAITING_VALIDATE:
        if (rec == '\n')
        {
            // validate
            if (esp8266_pendingState != ESP8266_STATE_NONE)
                esp8266_state = esp8266_pendingState;
            esp8266_pendingState = ESP8266_STATE_NONE;

            esp8266_fsmState = FSM_START;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_START:
        if (rec == '\r')
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        else if (rec == '+')
            esp8266_fsmState = FSM_PLUS;
        else if (rec == 'S')
            esp8266_fsmState = FSM_SENDOK_S;
        else if (rec == 'E')
            esp8266_fsmState = FSM_ERROR_E;
        else if (rec == 'r')
            esp8266_fsmState = FSM_ready_r;
        else if (rec == 'F')
            esp8266_fsmState = FSM_FAIL_F;
        else if (rec == '>')
        {
            esp8266_state = ESP8266_STATE_SEND_DATA;
            esp8266_fsmState = FSM_UNKNOW;
        }
        else if (rec == 'O')
            esp8266_fsmState = FSM_OK_O;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_SENDOK_S:
        if (rec == 'E')
            esp8266_fsmState = FSM_SENDOK_E;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_E:
        if (rec == 'N')
            esp8266_fsmState = FSM_SENDOK_N;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_N:
        if (rec == 'D')
            esp8266_fsmState = FSM_SENDOK_D;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_D:
        if (rec == ' ')
            esp8266_fsmState = FSM_SENDOK_Sp;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_Sp:
        if (rec == 'O')
            esp8266_fsmState = FSM_SENDOK_O;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_O:
        if (rec == 'K')
            esp8266_fsmState = FSM_SENDOK_K;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_SENDOK_K:
        if (rec == '\r')
        {
            esp8266_pendingState = ESP8266_STATE_SEND_OK;
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_ERROR_E:
        if (rec == 'R')
            esp8266_fsmState = FSM_ERROR_R1;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ERROR_R1:
        if (rec == 'R')
            esp8266_fsmState = FSM_ERROR_R2;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ERROR_R2:
        if (rec == 'O')
            esp8266_fsmState = FSM_ERROR_O;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ERROR_O:
        if (rec == 'R')
            esp8266_fsmState = FSM_ERROR_R3;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ERROR_R3:
        if (rec == '\r')
        {
            esp8266_pendingState = ESP8266_STATE_ERROR;
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_FAIL_F:
        if (rec == 'A')
            esp8266_fsmState = FSM_FAIL_A;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_FAIL_A:
        if (rec == 'I')
            esp8266_fsmState = FSM_FAIL_I;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_FAIL_I:
        if (rec == 'L')
            esp8266_fsmState = FSM_FAIL_L;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_FAIL_L:
        if (rec == '\r')
        {
            esp8266_pendingState = ESP8266_STATE_FAIL;
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_ready_r:
        if (rec == 'e')
            esp8266_fsmState = FSM_ready_e;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ready_e:
        if (rec == 'a')
            esp8266_fsmState = FSM_ready_a;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ready_a:
        if (rec == 'd')
            esp8266_fsmState = FSM_ready_d;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ready_d:
        if (rec == 'y')
            esp8266_fsmState = FSM_ready_y;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_ready_y:
        if (rec == '\r')
        {
            esp8266_pendingState = ESP8266_STATE_READY;
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_OK_O:
        if (rec == 'K')
            esp8266_fsmState = FSM_OK_K;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_OK_K:
        if (rec == '\r')
        {
            esp8266_pendingState = ESP8266_STATE_OK;
            esp8266_fsmState = FSM_WAITING_VALIDATE;
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;

    case FSM_PLUS:
        if (rec == 'I')
            esp8266_fsmState = FSM_IPD_I;
        else if (rec == 'C')
            esp8266_fsmState = FSM_IP_C;  // wait IP
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_C:
        if (rec == 'I')
            esp8266_fsmState = FSM_IP_I;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_I:
        if (rec == 'F')
            esp8266_fsmState = FSM_IP_F;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_F:
        if (rec == 'S')
            esp8266_fsmState = FSM_IP_S;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_S:
        if (rec == 'R')
            esp8266_fsmState = FSM_IP_R;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_R:
        if (rec == ':')
            esp8266_fsmState = FSM_IP_dP;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_dP:
        if (rec == 'S')
            esp8266_fsmState = FSM_IP_S2;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_S2:
        if (rec == 'T')
            esp8266_fsmState = FSM_IP_T;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_T:
        if (rec == 'A')
            esp8266_fsmState = FSM_IP_A;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_A:
        if (rec == 'I')
            esp8266_fsmState = FSM_IP_WIP;
        else if (rec == 'M')
            esp8266_fsmState = FSM_IP_WMAC;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IP_WIP:
        if (rec == '"')
        {
            esp8266_fsmState = FSM_IP_IP;
            esp8266_ipid = 0;
        }
        else if (rec == '\r')
            esp8266_fsmState = FSM_UNKNOW;
        else
            esp8266_fsmState = FSM_IP_WIP;  // wait IP
        break;
    case FSM_IP_IP:
        if ((rec >= '0' && rec <= '9') || rec == '.')
            esp8266_ip[esp8266_ipid++] = rec;
        else
        {
            esp8266_ip[esp8266_ipid] = 0;
            esp8266_fsmState = FSM_UNKNOW;
        }
        break;
    case FSM_IP_WMAC:
        if (rec == '"')
        {
            esp8266_fsmState = FSM_IP_MAC;
            esp8266_macid = 0;
        }
        else if (rec == '\r')
            esp8266_fsmState = FSM_UNKNOW;
        else
            esp8266_fsmState = FSM_IP_WMAC;  // wait IP
        break;
    case FSM_IP_MAC:
        if ((rec >= '0' && rec <= '9') || rec == ':' || (rec >= 'a' && rec <= 'f'))
            esp8266_mac[esp8266_macid++] = rec;
        else
        {
            esp8266_mac[esp8266_macid] = 0;
            esp8266_fsmState = FSM_UNKNOW;
        }
        break;
    case FSM_IPD_I:
        if (rec == 'P')
            esp8266_fsmState = FSM_IPD_P;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_P:
        if (rec == 'D')
            esp8266_fsmState = FSM_IPD_D;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_D:
        if (rec == ',')
            esp8266_fsmState = FSM_IPD_COMMA_1;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_COMMA_1:
        if (rec >= '0' && rec <= '9')
        {
            esp8266_fsmState = FSM_IPD_SOCKET_DIGIT;
            esp8266_socket = rec - '0';
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_SOCKET_DIGIT:
        if (rec == ',')
            esp8266_fsmState = FSM_IPD_COMMA_2;
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_COMMA_2:
        if (rec >= '0' && rec <= '9')
        {
            esp8266_fsmState = FSM_IPD_SIZE_DIGITS;
            esp8266_sizePacket = (rec - '0');
        }
        else
            esp8266_fsmState = FSM_UNKNOW;
        break;
    case FSM_IPD_SIZE_DIGITS:
        if (rec == ':')
        {
            esp8266_idPacket = 0;
            esp8266_fsmState = FSM_PACKET_RX;
        }
        else
        {
            if (rec >= '0' && rec <= '9')
            {
                esp8266_fsmState = FSM_IPD_SIZE_DIGITS;
                esp8266_sizePacket = esp8266_sizePacket * 10 + (rec - '0');
            }
            else
                esp8266_fsmState = FSM_UNKNOW;
        }
        break;
    case FSM_PACKET_RX:
        esp8266_dataPacket[esp8266_idPacket++] = rec;
        if (esp8266_idPacket >= esp8266_sizePacket)
        {
            esp8266_flagPacket = 1;
            esp8266_state = ESP8266_STATE_RECEIVE_DATA;
            esp8266_fsmState = FSM_UNKNOW;
        }
        break;
    default:
        esp8266_fsmState = FSM_UNKNOW;
    }
}

/**
 * @brief Internal function to protect string from special char
 * (,\\") char in AT commands arguments
 * @param destination protected string argument
 * @param destination string to protect
 */
char *esp8266_protectstr(char *destination, const char *source)
{
    char *ptr, *ptrsource;
    ptr = destination;
    ptrsource = (char *)source;

    while (*ptrsource != 0)
    {
        if (*ptrsource == '"' || *ptrsource == ',' || *ptrsource == '\\')
            (*(ptr++)) = '\\';
        (*(ptr++)) = *ptrsource;
        ptrsource++;
    }
    (*ptr) = 0;
    return destination;
}

/**
 * @brief Gives the current status of AT response
 * @return current status
 */
ESP8266_STATUS esp8266_getStatus()
{
    return esp8266_state;
}

/**
 * @brief Give the id of the last socket received
 * @return socket id
 */
uint8_t esp8266_getRecSocket()
{
    return esp8266_socket;
}

/**
 * @brief Reads the last packet received
 * @return pointer to data
 */
char *esp8266_getRecData()
{
    return esp8266_dataPacket;
}

/**
 * @brief Gives the last packet received size in bytes
 * @return size of packet
 */
uint16_t esp8266_getRecSize()
{
    return esp8266_sizePacket;
}

/**
 * @brief Check if packet is received by a socket
 * @return 0 if no packet is received, 1 else
 */
uint8_t esp8266_getRec()
{
    if (esp8266_flagPacket == 1)
    {
        esp8266_flagPacket = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief Sends a custom commands
 * @param data data command to send
 * @param size command size
 */
void esp8266_send_cmddat(char data[], uint16_t size)
{
    uart_write(esp8266_uart, data, size);
    esp8266_currentCmd = ESP8266_CMD_CUSTOM;
}

/**
 * @brief Opens a TCP socket
 * @param ip_domain destination IP or domain
 * @param port destinantion port
 * @return 0 if OK
 */
uint8_t esp8266_open_tcp_socket(char *ip_domain, uint16_t port)
{
    char protected[64];

    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CIPSTART=\"TCP\",\"");

    esp8266_protectstr(protected, ip_domain);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\",");
    buffer_aint(&esp8266_txBuff, port);

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_OPENTCP;
    return 0; // TODO return sock id
}

/**
 * @brief Opens a UDP socket
 * @param ip_domain destination IP or domain
 * @param port destinantion port
 * @param localPort local port
 * @return 0 if OK
 */
uint8_t esp8266_open_udp_socket(char *ip_domain, uint16_t port,
                                uint16_t localPort)
{
    char protected[64];

    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CIPSTART=\"UDP\",\"");

    esp8266_protectstr(protected, ip_domain);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\",");
    buffer_aint(&esp8266_txBuff, (int)port);
    buffer_achar(&esp8266_txBuff, ',');
    buffer_aint(&esp8266_txBuff, (int)localPort);

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_OPENUDP;
    return 0; // TODO return sock id
}

/**
 * @brief Sets mode of Wifi access
 * @param mode mode of operation : station (ESP8266_MODE_STA)
 * / access point (ESP8266_MODE_AP) or both (ESP8266_MODE_STA_AP)
 */
void esp8266_setMode(ESP8266_MODE mode)
{
    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CWMODE_CUR=");

    if (mode == ESP8266_MODE_AP)
        buffer_achar(&esp8266_txBuff, '2');
    else if (mode == ESP8266_MODE_STA_AP)
        buffer_achar(&esp8266_txBuff, '3');
    else
        buffer_achar(&esp8266_txBuff, '1');

    buffer_astring(&esp8266_txBuff, "\r\n");

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_SETMODE;
}

/**
 * @brief Sets config of access point (only in AP mode or STA_AP) SSID,
 * password, security mode and channel
 * @param ssid Name of the access point
 * @param pw_ecn Security mode : none/open (ESP8266_ECN_OPEN) /
 * WPA (ESP8266_ECN_WPA), WPA2 (ESP8266_ECN_WPA2) or auto (ESP8266_ECN_WPA_WPA2)
 * @param channel wifi channel
 * @return 0 if OK
 */
int esp8266_ap_setConfig(char *ssid, char *pw, ESP8266_ECN pw_ecn,
                         uint8_t channel)
{
    char protected[64];

    if (pw_ecn != ESP8266_ECN_OPEN && strlen(pw) < 8)
        return -1;  // password too short

    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CWSAP_CUR=\"");

    esp8266_protectstr(protected, ssid);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\",\"");

    esp8266_protectstr(protected, pw);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\",");

    buffer_aint(&esp8266_txBuff, (int)channel);
    buffer_astring(&esp8266_txBuff, ",");

    buffer_aint(&esp8266_txBuff, (int)pw_ecn);
    buffer_astring(&esp8266_txBuff, "\r\n");

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_APCONFIG;
    return 0;
}

/**
 * @brief Connects the station to an access point (only in STA mode)
 * @param ssid Name of the access point to connect to
 * @param pw password of the access point
 * @return 0 if OK
 */
int esp8266_connect_ap(char *ssid, char *pw)
{
    char protected[64];

    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CWJAP_CUR=\"");

    esp8266_protectstr(protected, ssid);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\",\"");

    esp8266_protectstr(protected, pw);
    buffer_astring(&esp8266_txBuff, protected);
    buffer_astring(&esp8266_txBuff, "\"\r\n");

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_CONNECTAP;
    return 0;
}

/**
 * @brief Disconnects the station of the current access point
 * @return 0 if OK
 */
int esp8266_disconnect_ap()
{
    esp8266_send_cmd("AT+CWQAP\r\n");
    esp8266_currentCmd = ESP8266_CMD_DISCONNECTAP;
    return 0;
}

/**
 * @brief Closes a socket
 * @param sock id of the socket to close
 */
void esp8266_close_socket(uint8_t sock)
{
    if (sock > 4)
        return;

    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CIPCLOSE=");
    buffer_aint(&esp8266_txBuff, sock);
    buffer_astring(&esp8266_txBuff, "\r\n");

    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_CLOSESOCKET;
}

/**
 * @brief Writes data to a socket
 * @param sock id of the socket
 * @param data pointer of data to send
 * @param size size of data in bytes
 */
void esp8266_write_socket(uint8_t sock, char *data, uint16_t size)
{
    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CIPSEND=");
    buffer_aint(&esp8266_txBuff, (int)sock);
    buffer_achar(&esp8266_txBuff, ',');
    buffer_aint(&esp8266_txBuff, (int)size);
    buffer_astring(&esp8266_txBuff, "\r\n");

    // send request
    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_WRITESOCK_REQ;

    while (esp8266_state != ESP8266_STATE_SEND_DATA) esp8266_task(); // TODO FIXME
    esp8266_state = ESP8266_STATE_NONE;

    esp8266_send_cmddat(data, size);
    esp8266_currentCmd = ESP8266_CMD_WRITESOCK_DATA;
    while (esp8266_state != ESP8266_STATE_SEND_OK) esp8266_task(); // TODO FIXME
}

/**
 * @brief Writes a string to a socket
 * @param sock id of the socket
 * @param data pointer of string to send (0 terminated string)
 */
void esp8266_write_socket_string(uint8_t sock, char *str)
{
    esp8266_write_socket(sock, str, strlen(str));
}

/**
 * @brief Creates a local server
 * @param port local port to bind
 */
void esp8266_server_create(uint16_t port)
{
    buffer_clear(&esp8266_txBuff);
    buffer_astring(&esp8266_txBuff, "AT+CIPSERVER=1,");
    buffer_aint(&esp8266_txBuff, (int)port);
    buffer_astring(&esp8266_txBuff, "\r\n");
    esp8266_send_cmddat(esp8266_txBuff.data, esp8266_txBuff.size);
    esp8266_currentCmd = ESP8266_CMD_SERVERCREATE;
}

/**
 * @brief Destroy the local server
 */
void esp8266_server_destroy()
{
    esp8266_send_cmd("AT+CIPSERVER=0\r\n");
    esp8266_currentCmd = ESP8266_CMD_SERVERDESTROY;
}

/**
 * @brief Gets the station IP
 * @return string current IP
 */
char *esp8266_getIp()
{
    return esp8266_ip;
}

/**
 * @brief Gets the station MAC
 * @return string current MAC
 */
char *esp8266_getMac()
{
    return esp8266_mac;
}
