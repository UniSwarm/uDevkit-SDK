/**
 * @file qei_dspic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 18, 2016, 22:33 PM 
 * 
 * @brief Quadrature Encoder Interface support driver
 */

#ifndef QEI_DSPIC_H
#define QEI_DSPIC_H

// calculate QEI count on the device
#ifdef QEI1CON
 #ifdef QEI2CON
  #define QEI_COUNT 2
 #else
  #define QEI_COUNT 1
 #endif
#else
 #define QEI_COUNT 0
 #warning "No qei on the current device"
#endif

#endif // QEI_DSPIC_H
