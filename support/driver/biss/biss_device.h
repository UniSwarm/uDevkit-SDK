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
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_dspic33ak) || defined(ARCHI_pic32ak)
#    include "biss_dspic33a_pic32a.h"
#else
#    warning "Unsupported ARCHI"
#endif

#if BISS_COUNT >= 1
enum
{
#    if BISS_COUNT >= 1
    BISS1_ID = 0,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // BISS_DEVICE_H
