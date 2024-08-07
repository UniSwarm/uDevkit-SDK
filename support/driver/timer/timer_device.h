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
#elif defined(ARCHI_dspic33ak)
#    include "i2c_dspic33a.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)                       \
    || defined(ARCHI_pic32mzda)
#    include "timer_pic32.h"
#else
#    warning "Unsupported ARCHI"
#endif

#ifdef __cplusplus
}
#endif

#if TIMER_COUNT >= 1
enum
{
#    if TIMER_COUNT >= 1
    TIMER1_ID = 0,
#    endif
#    if TIMER_COUNT >= 2
    TIMER2_ID = 1,
#    endif
#    if TIMER_COUNT >= 3
    TIMER3_ID = 2,
#    endif
#    if TIMER_COUNT >= 4
    TIMER4_ID = 3,
#    endif
#    if TIMER_COUNT >= 5
    TIMER5_ID = 4,
#    endif
#    if TIMER_COUNT >= 6
    TIMER6_ID = 5,
#    endif
#    if TIMER_COUNT >= 7
    TIMER7_ID = 6,
#    endif
#    if TIMER_COUNT >= 8
    TIMER8_ID = 7,
#    endif
#    if TIMER_COUNT >= 9
    TIMER9_ID = 8,
#    endif
};
#endif

#endif  // TIMER_DEVICE_H
