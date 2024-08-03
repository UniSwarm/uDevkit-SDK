/**
 * @file sent_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 03:36 PM
 *
 * @brief SENT support for specific devices
 */

#ifndef SENT_DEVICE_H
#define SENT_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "sent_dspic33.h"
#elif defined(ARCHI_dspic33ak)
#    include "sent_dspic33a.h"
#else
#    warning "Unsupported ARCHI"
#endif

#if SENT_COUNT >= 1
enum
{
#    if SENT_COUNT >= 1
    SENT1_ID = 0,
#    endif
#    if SENT_COUNT >= 2
    SENT2_ID = 1,
#    endif
#    if SENT_COUNT >= 3
    SENT3_ID = 2,
#    endif
#    if SENT_COUNT >= 4
    SENT4_ID = 3,
#    endif
#    if SENT_COUNT >= 5
    SENT5_ID = 4,
#    endif
#    if SENT_COUNT >= 6
    SENT6_ID = 5,
#    endif
#    if SENT_COUNT >= 7
    SENT7_ID = 6,
#    endif
#    if SENT_COUNT >= 8
    SENT8_ID = 7,
#    endif
#    if SENT_COUNT >= 9
    SENT9_ID = 8,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // SENT_DEVICE_H
