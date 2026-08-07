/**
 * @file dma.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2026
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

void dma_init(const void *addrLow, const void *addrHigh);

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

// Transfert configuration
int dma_setSource(rt_dev_t device, const void *srcAddr, uint8_t addrMode);
int dma_setDestination(rt_dev_t device, void *dstAddr, uint8_t addrMode);
int dma_setTrigger(rt_dev_t device, uint8_t trigger);
int dma_setTransferMode(rt_dev_t device, uint8_t transferMode);
int dma_setTransferCount(rt_dev_t device, uint16_t transferCount);
int dma_setWordSize(rt_dev_t device, uint8_t wordSize);
int dma_setOptions(rt_dev_t device, uint8_t options);

int dma_softTrigger(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // DMA_H
