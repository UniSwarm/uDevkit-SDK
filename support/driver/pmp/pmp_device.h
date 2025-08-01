/**
 * @file pmp_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date August 1, 2025, 05:15 PM
 *
 * @brief Parallel Master Port (PMP) support for specific devices
 */

#ifndef PMP_DEVICE_H
#define PMP_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24fv) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33ep)                           \
    || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj)
#    include "pmp_pic24_dspic33.h"
#elif defined(ARCHI_pic32mx) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
#    include "pmp_pic32.h"
#else
#    error Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // PMP_DEVICE_H
