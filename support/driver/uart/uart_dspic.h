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

#define uart_enable(d) \
 U1MODEbits.UARTEN=1

#endif // UART_DSPIC_H
