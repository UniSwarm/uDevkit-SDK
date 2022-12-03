/**
 * @file qei_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
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

#ifdef __cplusplus
}
#endif

#endif  // QEI_DEVICE_H
