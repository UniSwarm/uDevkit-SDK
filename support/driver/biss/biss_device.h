/**
 * @file biss_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 02:39 PM
 *
 * @brief BISS support for specific devices
 */

#ifndef BISS_DEVICE_H
#define BISS_DEVICE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_dspic33ak)
#    include "biss_dspic33a.h"
#else
#    warning "Unsupported ARCHI"
#endif

#if BISS_COUNT >= 1
enum
{
#    if BISS_COUNT >= 1
    BISS1_ID = 0,
#    endif
#    if BISS_COUNT >= 2
    BISS2_ID = 1,
#    endif
#    if BISS_COUNT >= 3
    BISS3_ID = 2,
#    endif
#    if BISS_COUNT >= 4
    BISS4_ID = 3,
#    endif
#    if BISS_COUNT >= 5
    BISS5_ID = 4,
#    endif
#    if BISS_COUNT >= 6
    BISS6_ID = 5,
#    endif
#    if BISS_COUNT >= 7
    BISS7_ID = 6,
#    endif
#    if BISS_COUNT >= 8
    BISS8_ID = 7,
#    endif
#    if BISS_COUNT >= 9
    BISS9_ID = 8,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // BISS_DEVICE_H
