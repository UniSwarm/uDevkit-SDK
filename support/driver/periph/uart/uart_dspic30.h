/**
 * @file uart_dspic30.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date August 09, 2016, 11:44 AM
 *
 * @brief Uart support for rtprog (dspic30 family)
 */

#ifndef UART_DSPIC30_H
#define UART_DSPIC30_H

// calculate UART count on the device
#if defined (DEVICE_30F1010) || defined (DEVICE_30F2010) || defined (DEVICE_30F2011) \
 || defined (DEVICE_30F2012) || defined (DEVICE_30F2020) || defined (DEVICE_30F2023) \
 || defined (DEVICE_30F3010) || defined (DEVICE_30F3012) || defined (DEVICE_30F4012) \
 || defined (DEVICE_30F5015) || defined (DEVICE_30F5016)
  #define UART_COUNT 1
#elif defined (DEVICE_30F3011) || defined (DEVICE_30F3013) || defined (DEVICE_30F3014) \
 || defined (DEVICE_30F4011) || defined (DEVICE_30F4013) || defined (DEVICE_30F5011) \
 || defined (DEVICE_30F5013) || defined (DEVICE_30F6010A) || defined (DEVICE_30F6011A) \
 || defined (DEVICE_30F6012A) || defined (DEVICE_30F6013A) || defined (DEVICE_30F6014A) \
 || defined (DEVICE_30F6015)
  #define UART_COUNT 2
#else
  #define UART_COUNT 0
#endif

#if UART_COUNT>=1
int uart_1_putw(uint16_t word);
int uart_1_putc(char c);
char uart_1_getc();	
uint16_t uart_1_getw();
#endif

#if UART_COUNT>=2
int uart_2_putw(uint16_t word);
int uart_2_putc(char c);
char uart_2_getc();
uint16_t uart_2_getw();
#endif

#endif // UART_DSPIC30_H
