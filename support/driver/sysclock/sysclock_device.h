/**
 * @file sysclock_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2023
 *
 * @date January 22, 2023, 06:36 PM
 *
 * @brief System clock support for specific devices
 */

#ifndef SYSCLOCK_DEVICE_H
#define SYSCLOCK_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)                            \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "sysclock_pic24_dspic33.h"
#elif defined(ARCHI_dspic30f)
#    include "sysclock_dspic30f.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "sysclock_dspic33c.h"
#elif defined(ARCHI_pic32mx)
#    include "sysclock_pic32mx.h"
#elif defined(ARCHI_pic32mm)
#    include "sysclock_pic32mm.h"
#elif defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mk)
#    include "sysclock_pic32mz_mk.h"
#else
typedef int SYSCLOCK_CLOCK;
typedef int SYSCLOCK_SOURCE;
#    error Unsuported ARCHI for sysclock driver.
#endif

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_DEVICE_H
