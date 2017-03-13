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

void esp8266_send_cmd(char data[]);
void esp8266_write(char data[], uint16_t size);

void esp8266_rst();

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
    ESP8266_ECN_OPEN = 0,
    ESP8266_ECN_WPA = 2,
    ESP8266_ECN_WPA2 = 3,
    ESP8266_ECN_WPA_WPA2 = 4
} ESP8266_ECN;
int esp8266_ap_setConfig(char *ssid, char *pw, ESP8266_ECN pw_ecn, uint8_t channel);
uint8_t esp8266_connect_ap(char *ssid, char *pw);
uint8_t esp8266_disconnect_ap();

// ======== tcp/ip layer =========
uint8_t esp8266_open_tcp_socket(char *ip_domain, uint16_t port);
uint8_t esp8266_open_udp_socket(char *ip_domain, uint16_t port, uint16_t localPort, uint8_t mode);
void esp8266_close_socket(uint8_t sock);
void esp8266_write_socket(uint8_t sock, char *data, uint16_t size);
void esp8266_write_socket_string(uint8_t sock, char *str);

void esp8266_server_create(uint16_t port);
void esp8266_server_destroy();

typedef enum
{
    WIFI_STATE_NONE = 0,
    WIFI_STATE_READY,
    WIFI_STATE_OK,
    WIFI_STATE_ERROR,
    WIFI_STATE_RECEIVE_DATA,
    WIFI_STATE_SEND_DATA,
    WIFI_STATE_SEND_OK

} WIFI_STATE;
WIFI_STATE get_state();

uint8_t getRec();
uint8_t getRecSocket();
char *getRecData();
uint16_t getRecSize();

#endif   // ESP8266_H
