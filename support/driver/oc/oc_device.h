/**
 * @file oc_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:34 PM
 *
 * @brief OC support for specific devices
 */

#ifndef OC_DEVICE_H
#define OC_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ========= specific includes ========
#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "oc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
#    include "oc_pic24f_dspic30f_dspic33f.h"
#elif defined(ARCHI_pic24fj)
#    if defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102) || defined(DEVICE_24FJ32MC101) || defined(DEVICE_24FJ32MC102) || defined(DEVICE_24FJ32MC104)
#        include "oc_pic24f_dspic30f_dspic33f.h"
#    else
#        include "oc_pic24e_dspic33e.h"
#    endif
#elif defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
#    include "oc_pic32.h"
#else
#    warning Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // OC_DEVICE_H
