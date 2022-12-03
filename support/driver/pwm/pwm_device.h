/**
 * @file pwm_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
 *
 * @date December 3, 2022, 01:35 PM
 *
 * @brief PWM support for specific devices
 */

#ifndef PWM_DEVICE_H
#define PWM_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) \
    || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj)
#    include "pwm_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
#    include "pwm_pic32.h"
#else
#    error Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // PWM_DEVICE_H
