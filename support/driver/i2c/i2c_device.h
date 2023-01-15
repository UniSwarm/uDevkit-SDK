/**
 * @file i2c_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:33 PM
 *
 * @brief I2C support for specific devices
 */

#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "i2c_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)                       \
    || defined(ARCHI_pic32mzda)
#    include "i2c_pic32.h"
#else
#    warning Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // I2C_DEVICE_H
