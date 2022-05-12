/**
 * @file network.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date February 22, 2017, 15:28 PM
 *
 * @brief Network module to handle various types
 * of network interfaces for uDevkit-SDK
 */

#ifndef NETWORK_H
#define NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "network_driver.h"
#ifdef USE_esp8266
#    include "driver/esp8266/esp8266.h"
#endif
#ifdef USE_a6
#    include "driver/a6/a6.h"
#endif

#include "web_server.h"

void network_init(void);
void network_task(void);

#ifdef __cplusplus
}
#endif

#endif  // NETWORK_H
