/**
 * @file spi_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 3, 2022, 01:35 PM
 *
 * @brief SPI support for specific devices
 */

#ifndef SPI_DEVICE_H
#define SPI_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
#    include "spi_pic24f_dspic33f.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33ck) || defined(ARCHI_dspic33ch)
#    include "spi_pic24e_dspic33e.h"
#elif defined(ARCHI_dspic30f)
#    include "spi_dspic30f.h"
#elif defined(ARCHI_dspic33ak)
#    include "spi_dspic33a.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
#    include "spi_pic32.h"
#else
#    error Unsuported ARCHI
#endif

#if SPI_COUNT >= 1
enum
{
#    if SPI_COUNT >= 1
    SPI1_ID = 0,
#    endif
#    if SPI_COUNT >= 2
    SPI2_ID = 1,
#    endif
#    if SPI_COUNT >= 3
    SPI3_ID = 2,
#    endif
#    if SPI_COUNT >= 4
    SPI4_ID = 3,
#    endif
#    if SPI_COUNT >= 5
    SPI5_ID = 4,
#    endif
#    if SPI_COUNT >= 6
    SPI6_ID = 5,
#    endif
#endif
};

#ifdef __cplusplus
}
#endif

#endif  // SPI_DEVICE_H
