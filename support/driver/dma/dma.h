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

void dma_init(uint16_t addrLow, uint16_t addrHigh);

// ====== device assignation ======
#define dma(d) MKDEV(DEV_CLASS_TIMER, ((d)-1))
rt_dev_t dma_getFreeDevice(void);
int dma_open(rt_dev_t device);
int dma_close(rt_dev_t device);

// ==== device enable/disable =====
int dma_enable(rt_dev_t device);
int dma_disable(rt_dev_t device);

// ======= specific include =======
#if defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "dma_dspic33c.h"
#else
#    warning "Unsupported ARCHI"
#endif

#ifdef SIMULATOR
#    define _dma_space_
#endif

#endif  // DMA_H
