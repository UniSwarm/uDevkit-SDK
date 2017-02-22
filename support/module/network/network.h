/**
 * @file network.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date February 22, 2016, 15:28 PM
 *
 * @brief Network module to handle various types of networks for RTProg
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "network_driver.h"

#ifdef USE_esp8266
  #include "driver/esp8266/esp8266.h"
#endif
#ifdef USE_a6
  #include "driver/a6/a6.h"
#endif

#endif // NETWORK_H
