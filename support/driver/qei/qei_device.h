/**
 * @file qei_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:35 PM
 *
 * @brief QEI support for specific devices
 */

#ifndef QEI_DEVICE_H
#define QEI_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)
#    include "qei_pic24f_dspic33f.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "qei_pic24e_dspic33e.h"
#elif defined(ARCHI_dspic30f)
#    include "qei_dspic30f.h"
#elif defined(ARCHI_dspic33ak)
#    include "qei_dspic33a.h"
#elif defined(ARCHI_pic32mk)
#    include "qei_pic32mk.h"
#else
#    define QEI_COUNT 0
#endif

#ifdef QEI_32B
typedef uint32_t qei_type;
#else
typedef uint16_t qei_type;
#endif

#if QEI_COUNT >= 1
enum
{
#    if QEI_COUNT >= 1
    QEI1_ID = 0,
#    endif
#    if QEI_COUNT >= 2
    QEI2_ID = 1,
#    endif
#    if QEI_COUNT >= 3
    QEI3_ID = 2,
#    endif
#    if QEI_COUNT >= 4
    QEI4_ID = 3,
#    endif
#    if QEI_COUNT >= 5
    QEI5_ID = 4,
#    endif
#    if QEI_COUNT >= 6
    QEI6_ID = 5,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // QEI_DEVICE_H
