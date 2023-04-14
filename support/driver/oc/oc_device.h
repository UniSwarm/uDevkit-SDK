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

enum
{
#if OC_COUNT >= 1
    OC1_ID = 0,
#endif
#if OC_COUNT >= 2
    OC2_ID = 1,
#endif
#if OC_COUNT >= 3
    OC3_ID = 2,
#endif
#if OC_COUNT >= 4
    OC4_ID = 3,
#endif
#if OC_COUNT >= 5
    OC5_ID = 4,
#endif
#if OC_COUNT >= 6
    OC6_ID = 5,
#endif
#if OC_COUNT >= 7
    OC7_ID = 6,
#endif
#if OC_COUNT >= 8
    OC8_ID = 7,
#endif
#if OC_COUNT >= 9
    OC9_ID = 8,
#endif
#if OC_COUNT >= 10
    OC10_ID = 9,
#endif
#if OC_COUNT >= 11
    OC11_ID = 10,
#endif
#if OC_COUNT >= 12
    OC12_ID = 11,
#endif
#if OC_COUNT >= 13
    OC13_ID = 12,
#endif
#if OC_COUNT >= 14
    OC14_ID = 13,
#endif
#if OC_COUNT >= 15
    OC15_ID = 14,
#endif
#if OC_COUNT >= 16
    OC16_ID = 15,
#endif
};

#ifdef __cplusplus
}
#endif

#endif  // OC_DEVICE_H
