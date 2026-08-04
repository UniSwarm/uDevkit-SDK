/**
 * @file dma.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2023
 *
 * @date September 11, 2021, 03:50 PM
 *
 * @brief DMA support for udevkit
 */

#ifndef DMA_H
#define DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_device.h"

void dma_init(uint16_t addrLow, uint16_t addrHigh);

// ====== device assignation ======
#define dma(d) MKDEV(DEV_CLASS_DMA, ((d) - 1))
rt_dev_t dma_getFreeDevice(void);
int dma_open(rt_dev_t device);
int dma_close(rt_dev_t device);
bool dma_isOpened(rt_dev_t device);

// ==== device enable/disable =====
int dma_enable(rt_dev_t device);
int dma_disable(rt_dev_t device);
bool dma_isEnabled(rt_dev_t device);

int dma_setHandler(rt_dev_t device, void (*handler)(void));

#ifdef __cplusplus
}
#endif

#endif  // DMA_H
