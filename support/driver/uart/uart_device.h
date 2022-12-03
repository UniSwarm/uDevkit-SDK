/**
 * @file uart_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
 *
 * @date December 3, 2022, 01:35 PM
 *
 * @brief UART support for specific devices
 */

#ifndef UART_DEVICE_H
#define UART_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)                            \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "uart_pic24_dspic33.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "uart_dspic33c.h"
#elif defined(ARCHI_dspic30f)
#    include "uart_dspic30f.h"
#elif defined(ARCHI_pic32mx)
#    include "uart_pic32mx.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
#    include "uart_pic32mz_mm_mk.h"
#endif

#ifdef __cplusplus
}
#endif

#endif  // UART_DEVICE_H
