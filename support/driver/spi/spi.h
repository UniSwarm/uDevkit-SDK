/**
 * @file spi.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date May 02, 2016, 11:43 AM
 *
 * @brief SPI low level driver
 */

#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_device.h"

// ====== device assignation ======
#define spi(d) MKDEV(DEV_CLASS_SPI, (d)-1)
rt_dev_t spi_getFreeDevice(void);
int spi_open(rt_dev_t device);
int spi_close(rt_dev_t device);

// ==== device enable/disable =====
int spi_enable(rt_dev_t device);
int spi_disable(rt_dev_t device);

// ======== device settings =======
int spi_setfreq(rt_dev_t device, uint32_t freq);
uint32_t spi_Freq(rt_dev_t device);
uint32_t spi_effectiveFreq(rt_dev_t device);

int spi_setBitLength(rt_dev_t device, uint8_t bitLength);
uint8_t spi_bitLength(rt_dev_t device);

// ========= device write ========
ssize_t spi_write(rt_dev_t device, const char *data, size_t size);
int spi_flush(rt_dev_t device);

// ========= device read =========
ssize_t spi_read(rt_dev_t device, char *data, size_t size_max);

#ifdef __cplusplus
}
#endif

#endif  // SPI_H
