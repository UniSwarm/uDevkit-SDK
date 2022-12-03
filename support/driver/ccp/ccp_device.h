/**
 * @file ccp_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
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

#ifdef __cplusplus
}
#endif

#endif  // CCP_DEVICE_H
