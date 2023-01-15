/**
 * @file timer_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:35 PM
 *
 * @brief Timer support for specific devices
 */

#ifndef TIMER_DEVICE_H
#define TIMER_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "timer_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "timer_dspic33c.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)                       \
    || defined(ARCHI_pic32mzda)
#    include "timer_pic32.h"
#else
#    warning "Unsupported ARCHI"
#endif

#ifdef __cplusplus
}
#endif

#endif  // TIMER_DEVICE_H
