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

#include "network_driver.h"
#ifdef USE_esp8266
  #include "driver/esp8266/esp8266.h"
#endif
#ifdef USE_a6
  #include "driver/a6/a6.h"
#endif

void network_init()
{
    #ifdef USE_esp8266
      esp8266_init();
    #endif
    #ifdef USE_a6
      a6_init();
    #endif
}

void network_task()
{
    #ifdef USE_esp8266
      esp8266_task();
    #endif
}
