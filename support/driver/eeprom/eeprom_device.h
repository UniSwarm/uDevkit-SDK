/**
 * @file eeprom_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 18, 2023, 01:51 PM
 *
 * @brief NVM support for specific devices
 */

#ifndef EEPROM_DEVICE_H
#define EEPROM_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#if defined(ARCHI_pic32mk)
#    include "eeprom_pic32mk.h"
#else
#    error Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // EEPROM_DEVICE_H
