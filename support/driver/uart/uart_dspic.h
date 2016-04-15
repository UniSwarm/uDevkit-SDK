/**
 * @file uart_dspic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM 
 * 
 * @brief Uart support for rtprog
 */

#ifndef UART_DSPIC_H
#define UART_DSPIC_H

#include <xc.h>

// calculate UART count on the device
#ifdef U1MODE
 #ifdef U2MODE
  #ifdef U3MODE
   #ifdef U4MODE
    #define UART_COUNT 4
   #else
    #define UART_COUNT 3
   #endif
  #else
   #define UART_COUNT 2
  #endif
 #else
  #define UART_COUNT 1
 #endif
#else
 #define UART_COUNT 0
 #warning No uart on the current device
#endif

#endif // UART_DSPIC_H
