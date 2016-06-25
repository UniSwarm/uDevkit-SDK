/**
 * @file spi.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date May 02, 2016, 11:43 AM 
 * 
 * @brief SPI low level driver
 */

#ifndef SPI_H
#define SPI_H

#include "driver/device.h"

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
 #include "spi_dspic.h"
#else
 #error Unsuported ARCHI
#endif

// ====== device assignation ======
rt_dev_t spi_getFreeDevice();
void spi_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int spi_enable(rt_dev_t device);
int spi_disable(rt_dev_t device);

// ======== device settings =======
int spi_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
uint32_t spi_baudSpeed(rt_dev_t device);
uint32_t spi_effectiveBaudSpeed(rt_dev_t device);

int spi_setBitConfig(rt_dev_t device, uint8_t bitLenght);
uint8_t spi_bitLenght(rt_dev_t device);

// ========= device write ========
ssize_t spi_write(rt_dev_t device, const char *data, size_t size);
int spi_flush(rt_dev_t device);

// ========= device read =========
char spi_getc(rt_dev_t device);
uint16_t spi_getw(rt_dev_t device);
uint8_t spi_datardy(rt_dev_t device);
ssize_t spi_read(rt_dev_t device, char *data, size_t size_max);

#endif // SPI_H
