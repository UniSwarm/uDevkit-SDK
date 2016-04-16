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
#include "uart.h"

// calculate UART count on the device
#ifdef U1MODE
#ifdef U2MODE
#ifdef U4MODE
#define UART_COUNT 4
#else
#define UART_COUNT 2
#endif
#else
#define UART_COUNT 1
#endif
#else
#define UART_COUNT 0
#warning "No uart on the current device"
#endif

int uart_1_putw(uint16_t word);
int uart_1_putc(char c);
char uart_1_getc();
uint16_t uart_1_getw();

#if UART_COUNT>=2
int uart_2_putw(uint16_t word);
int uart_2_putc(char c);
char uart_2_getc();
uint16_t uart_2_getw();
#endif

#if UART_COUNT>=3
int uart_3_putw(uint16_t word);
int uart_3_putc(char c);
char uart_3_getc();
uint16_t uart_3_getw();
#endif

#if UART_COUNT>=4
int uart_4_putw(uint16_t word);
int uart_4_putc(char c);
char uart_4_getc();
uint16_t uart_4_getw();
#endif

#endif // UART_DSPIC_H
