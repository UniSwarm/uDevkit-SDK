/**
 * @file qei_pic32mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
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

#ifdef __cplusplus
extern "C" {
#endif

// calculate QEI count and version on the device
#if defined(DEVICE_32MK0128MCA028) || defined(DEVICE_32MK0128MCA032) || defined(DEVICE_32MK0128MCA048)
#    define QEI_COUNT 2
#elif defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)
#    define QEI_COUNT 3
#elif defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100)                     \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define QEI_COUNT 6
#else
#    define QEI_COUNT 0
#endif

#define QEI_32B

#ifdef __cplusplus
}
#endif

#endif  // QEI_PIC32MK_H
