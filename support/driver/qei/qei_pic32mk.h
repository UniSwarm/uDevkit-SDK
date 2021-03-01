/**
 * @file qei_pic32mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date June 18, 2017, 23:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for PIC32MK
 *
 * Implementation based on Microchip document DS60001346A :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/60001346A.pdf
 */

#ifndef QEI_PIC32MK_H
#define QEI_PIC32MK_H

// calculate QEI count and version on the device
#if defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCM064) \
 || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) \
 || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
 #define QEI_COUNT 6
#else
 #define QEI_COUNT 0
#endif

#define QEI_32B

#endif // QEI_PIC32MK_H
