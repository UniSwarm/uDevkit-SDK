/**
 * @file ccp_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:27 PM
 *
 * @brief CCP support for specific devices
 */

#ifndef CCP_DEVICE_H
#define CCP_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "ccp_pic24_dspic33.h"
#elif defined(ARCHI_pic32mm)
#    include "ccp_pic32.h"
#else
#    warning "Unsupported ARCHI"
#endif

enum
{
#if CCP_COUNT >= 1
    CCP1_ID = 0,
#endif
#if CCP_COUNT >= 2
    CCP2_ID = 1,
#endif
#if CCP_COUNT >= 3
    CCP3_ID = 2,
#endif
#if CCP_COUNT >= 4
    CCP4_ID = 3,
#endif
#if CCP_COUNT >= 5
    CCP5_ID = 4,
#endif
#if CCP_COUNT >= 6
    CCP6_ID = 5,
#endif
#if CCP_COUNT >= 7
    CCP7_ID = 6,
#endif
#if CCP_COUNT >= 8
    CCP8_ID = 7,
#endif
#if CCP_COUNT >= 9
    CCP9_ID = 8,
#endif
};

#ifdef __cplusplus
}
#endif

#endif  // CCP_DEVICE_H
