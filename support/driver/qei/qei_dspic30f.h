/**
 * @file qei_dspic30f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC30F
 * Only one QEI device could be present in this architecture.
 *
 * Implementation based on Microchip document DS70063D :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70063D.pdf
 */

#ifndef QEI_DSPIC30F_H
#define QEI_DSPIC30F_H

#ifdef __cplusplus
extern "C" {
#endif

// calculate QEI count and version on the device
#if defined(DEVICE_30F2010) || defined(DEVICE_30F3010) || defined(DEVICE_30F3011) || defined(DEVICE_30F4011) || defined(DEVICE_30F4012)                        \
    || defined(DEVICE_30F5015) || defined(DEVICE_30F5016) || defined(DEVICE_30F6010A) || defined(DEVICE_30F6015)
#    define QEI_COUNT 1
#else
#    define QEI_COUNT 0
#endif

#define QEI_16B

#ifdef __cplusplus
}
#endif

#endif  // QEI_DSPIC30F_H
