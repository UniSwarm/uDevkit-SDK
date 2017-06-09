/**
 * @file esp8266.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date February 10, 2016, 09:32 PM
 *
 * @brief ESP8266 driver for RTProg network module
 */

#ifndef ESP8266_H
#define ESP8266_H

#include <stdint.h>

void esp8266_init();

void esp8266_task();

#define esp8266_send_cmd(cmd) uart_write(esp8266_uart, (cmd), strlen(cmd))
void esp8266_send_cmddat(char data[], uint16_t size);

// ======== wifi layer =========
typedef enum
{
    ESP8266_MODE_STA = 0,
    ESP8266_MODE_AP,
    ESP8266_MODE_STA_AP
} ESP8266_MODE;
void esp8266_setMode(ESP8266_MODE mode);

typedef enum
{
    ESP8266_ECN_OPEN = 0,     ///< open access point, no password
    ESP8266_ECN_WPA = 2,      ///< WPA security
    ESP8266_ECN_WPA2 = 3,     ///< WPA2 security
    ESP8266_ECN_WPA_WPA2 = 4  ///< WPA/WPA2 mixed security
} ESP8266_ECN;
int esp8266_ap_setConfig(char *ssid, char *pw, ESP8266_ECN pw_ecn, uint8_t channel);
int esp8266_connect_ap(char *ssid, char *pw);
int esp8266_disconnect_ap();

// ======== tcp/ip layer =========
uint8_t esp8266_open_tcp_socket(char *ip_domain, uint16_t port);
uint8_t esp8266_open_udp_socket(char *ip_domain, uint16_t port, uint16_t localPort);
void esp8266_write_socket(uint8_t sock, char *data, uint16_t size);
void esp8266_write_socket_string(uint8_t sock, char *str);
void esp8266_close_socket(uint8_t sock);

void esp8266_server_create(uint16_t port);
void esp8266_server_destroy();

typedef enum
{
    ESP8266_STATUS_BUSY = 0,
    ESP8266_STATUS_READY

} ESP8266_STATUS;
ESP8266_STATUS esp8266_getStatus();

uint8_t esp8266_getRec();
uint8_t esp8266_getRecSocket();
char *esp8266_getRecData();
uint16_t esp8266_getRecSize();

char *esp8266_getIp();
char *esp8266_getMac();

#endif   // ESP8266_H
