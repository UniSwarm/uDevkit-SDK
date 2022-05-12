/**
 * @file spi_dspic30f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date October 10, 2016, 10:31 AM
 *
 * @brief SPI communication support driver for dsPIC30F
 */

#ifndef SPI_DSPIC30F_H
#define SPI_DSPIC30F_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_30F1010) || defined(DEVICE_30F2010) || defined(DEVICE_30F2010E) || defined(DEVICE_30F2011) || defined(DEVICE_30F2011E)                      \
    || defined(DEVICE_30F2012) || defined(DEVICE_30F2012E) || defined(DEVICE_30F2020) || defined(DEVICE_30F2023) || defined(DEVICE_30F3010)                    \
    || defined(DEVICE_30F3010E) || defined(DEVICE_30F3011) || defined(DEVICE_30F3011E) || defined(DEVICE_30F3012) || defined(DEVICE_30F3012E)                  \
    || defined(DEVICE_30F3013) || defined(DEVICE_30F3013E) || defined(DEVICE_30F3014) || defined(DEVICE_30F3014E) || defined(DEVICE_30F4011)                   \
    || defined(DEVICE_30F4011E) || defined(DEVICE_30F4012) || defined(DEVICE_30F4012E) || defined(DEVICE_30F4013) || defined(DEVICE_30F4013E)
#    define SPI_COUNT 1
#elif defined(DEVICE_30F5011) || defined(DEVICE_30F5011E) || defined(DEVICE_30F5013) || defined(DEVICE_30F5013E) || defined(DEVICE_30F5015)                    \
    || defined(DEVICE_30F5015E) || defined(DEVICE_30F5016) || defined(DEVICE_30F6010) || defined(DEVICE_30F6010A) || defined(DEVICE_30F6011)                   \
    || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012) || defined(DEVICE_30F6012A) || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A)                  \
    || defined(DEVICE_30F6014) || defined(DEVICE_30F6014A) || defined(DEVICE_30F6015)
#    define SPI_COUNT 2
#else
#    define SPI_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // SPI_DSPIC30F_H
