/**
 * @file qei_pic24f_dspic33f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC33FJ,
 * PIC24F, PIC24FJ and PIC24HJ
 *
 * Implementation based on Microchip document DS70208C :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/70208C.pdf
 */

#ifndef QEI_PIC24F_DSPIC33F_H
#define QEI_PIC24F_DSPIC33F_H

// calculate QEI count and version on the device
#if defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC708A) \
 || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202) \
 || defined(DEVICE_33FJ16MC304) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710A) \
 || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC204) \
 || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508A) \
 || defined(DEVICE_33FJ64MC510A) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710A) \
 || defined(DEVICE_33FJ128MC506A)
  #define QEI_COUNT 1
#elif defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC802) \
 || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608) \
 || defined(DEVICE_33FJ32GS610) || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) \
 || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608) || defined(DEVICE_33FJ64GS610) \
 || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) \
 || defined(DEVICE_33FJ64MC804)
  #define QEI_COUNT 2
#else
  #define QEI_COUNT 0
#endif

#define QEI_16B

#endif // QEI_PIC24F_DSPIC33F_H
