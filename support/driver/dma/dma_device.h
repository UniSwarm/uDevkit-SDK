/**
 * @file dma_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date August 4, 2026, 11:30 AM
 *
 * @brief DMA support for specific devices
 */

#ifndef DMA_DEVICE_H
#define DMA_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_dspic24fj) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "dma_pic24fj_dspic33c.h"
#else
#    warning "Unsupported ARCHI"
#endif

#if DMA_COUNT >= 1
enum
{
#    if DMA_COUNT >= 1
    DMA1_ID = 0,
#    endif
#    if DMA_COUNT >= 2
    DMA2_ID = 1,
#    endif
#    if DMA_COUNT >= 3
    DMA3_ID = 2,
#    endif
#    if DMA_COUNT >= 4
    DMA4_ID = 3,
#    endif
#    if DMA_COUNT >= 5
    DMA5_ID = 4,
#    endif
#    if DMA_COUNT >= 6
    DMA6_ID = 5,
#    endif
#    if DMA_COUNT >= 7
    DMA7_ID = 6,
#    endif
#    if DMA_COUNT >= 8
    DMA8_ID = 7,
#    endif
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // DMA_DEVICE_H
