/**
 * @file uart_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
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
#elif defined(ARCHI_dspic33ak)
#    include "uart_dspic33a.h"
#elif defined(ARCHI_pic32mx)
#    include "uart_pic32mx.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
#    include "uart_pic32mz_mm_mk.h"
#endif

#if UART_COUNT >= 1
enum
{
#    if UART_COUNT >= 1
    UART1_ID = 0,
#    endif
#    if UART_COUNT >= 2
    UART2_ID = 1,
#    endif
#    if UART_COUNT >= 3
    UART3_ID = 2,
#    endif
#    if UART_COUNT >= 4
    UART4_ID = 3,
#    endif
#    if UART_COUNT >= 5
    UART5_ID = 4,
#    endif
#    if UART_COUNT >= 6
    UART6_ID = 5,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // UART_DEVICE_H
