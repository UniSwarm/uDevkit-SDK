/**
 * @file spi.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date May 02, 2016, 11:43 AM
 *
 * @brief SPI low level driver
 */

#ifndef SPI_H
#define SPI_H

#include <driver/device.h>

// ====== device assignation ======
#define spi(d) MKDEV(DEV_CLASS_SPI, (d)-1)
rt_dev_t spi_getFreeDevice();
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

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "spi_pic24f_dspic33f.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) \
 || defined(ARCHI_dspic33ck) || defined(ARCHI_dspic33ch)
 #include "spi_pic24e_dspic33e.h"
#elif defined(ARCHI_dspic30f)
 #include "spi_dspic30f.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) \
   || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
 #include "spi_pic32.h"
#else
 #error Unsuported ARCHI
#endif

#endif // SPI_H
