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
dev_t spi_getFreeDevice();
void spi_releaseDevice(dev_t device);

// ==== device enable/disable =====
int spi_enable(dev_t device);
int spi_disable(dev_t device);

// ======== device settings =======
int spi_setBaudSpeed(dev_t device, uint32_t baudSpeed);
uint32_t spi_baudSpeed(dev_t device);
uint32_t spi_effectiveBaudSpeed(dev_t device);

int spi_setBitConfig(dev_t device, uint8_t bitLenght);
uint8_t spi_bitLenght(dev_t device);

// ========= device write ========
int spi_putc(dev_t device, const char c);
int spi_putw(dev_t device, const uint16_t word);

int spi_write(dev_t device, const char *data, size_t size);
int spi_flush(dev_t device);

// ========= device read =========
char spi_getc(dev_t device);
uint16_t spi_getw(dev_t device);
uint8_t spi_datardy(dev_t device);

#endif // SPI_H
