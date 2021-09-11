/**
 * @file dma.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021
 *
 * @date September 11, 2021, 03:50 PM
 *
 * @brief DMA support for udevkit
 */

#ifndef DMA_H
#define DMA_H

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "dma_dspic33c.h"
#else
#    warning "Unsupported ARCHI"
#endif

#endif  // DMA_H
