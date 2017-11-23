/**
 * @file network.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date February 22, 2017, 15:28 PM
 *
 * @brief Network module to handle various types of network interfaces for RTProg
 */

#include "network.h"

#include "web_server.h"

void network_init()
{
    #ifdef USE_esp8266
        esp8266_init();
        web_server_init();
    #endif
}

void network_task()
{
#ifdef USE_esp8266
    esp8266_task();
    web_server_task();
#endif
#ifdef USE_a6
    a6_task();
#endif
}
