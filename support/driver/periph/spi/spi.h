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

#include <stdint.h>
#include <stdlib.h>

// ====== device assignation ======
uint8_t spi_getFreeDevice();
void spi_releaseDevice(uint8_t device);

// ==== device enable/disable =====
int spi_enable(uint8_t device);
int spi_disable(uint8_t device);

// ======== device settings =======
int spi_setBaudSpeed(uint8_t device, uint32_t baudSpeed);
uint32_t spi_baudSpeed(uint8_t device);
uint32_t spi_effectiveBaudSpeed(uint8_t device);

int spi_setBitConfig(uint8_t device, uint8_t bitLenght);
uint8_t spi_bitLenght(uint8_t device);

// ========= device write ========
int spi_putc(uint8_t device, const char c);
int spi_putw(uint8_t device, const uint16_t word);

int spi_write(uint8_t device, const char *data, size_t size);
int spi_flush(uint8_t device);

// ========= device read =========
char spi_getc(uint8_t device);
uint16_t spi_getw(uint8_t device);
uint8_t spi_datardy(uint8_t device);

#include "board.h"
#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
 #include "spi_dspic.h"
#else
 #error Unsuported ARCHI
#endif

#endif // SPI_H
