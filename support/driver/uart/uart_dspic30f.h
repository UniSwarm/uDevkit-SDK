/**
 * @file uart_dspic30f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2019
 *
 * @date August 09, 2016, 11:44 AM
 *
 * @brief Uart support for udevkit (dsPIC30F family)
 *
 * Implementation based on Microchip document DS70000582E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70000582e.pdf
 */

#ifndef UART_DSPIC30F_H
#define UART_DSPIC30F_H

// calculate UART count on the device

#if defined(DEVICE_30F1010) || defined(DEVICE_30F2010) || defined(DEVICE_30F2011) \
 || defined(DEVICE_30F2012) || defined(DEVICE_30F2020) || defined(DEVICE_30F2023) \
 || defined(DEVICE_30F3010) || defined(DEVICE_30F3012) || defined(DEVICE_30F4012) \
 || defined(DEVICE_30F5015) || defined(DEVICE_30F5016)
 #define UART_COUNT 1
#elif defined(DEVICE_30F3011) || defined(DEVICE_30F3013) || defined(DEVICE_30F3014) \
 || defined(DEVICE_30F4011) || defined(DEVICE_30F4013) || defined(DEVICE_30F5011) \
 || defined(DEVICE_30F5013) || defined(DEVICE_30F6010) || defined(DEVICE_30F6010A) \
 || defined(DEVICE_30F6011) || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012) \
 || defined(DEVICE_30F6012A) || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A) \
 || defined(DEVICE_30F6014) || defined(DEVICE_30F6014A) || defined(DEVICE_30F6015)
 #define UART_COUNT 2
#else
 #define UART_COUNT 0
#endif

#define UART_MAXBRG 0x0000FFFF    // 16 bits divisor

#endif // UART_DSPIC30F_H
