/**
 * @file uart.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM 
 * 
 * @brief Uart support for rtprog
 */
 
#ifndef UART_H
#define UART_H

#include <stdint.h>

#include "board.h"

uint8_t uart_getFreeDevice();
void uart_releaseDevice(uint8_t device);

int uart_enable(uint8_t device);
int uart_disable(uint8_t device);

int uart_setBaudSpeed(uint8_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(uint8_t device);

int uart_setBitConfig(uint8_t device, uint8_t bitLenght, uint8_t bitParity);
uint8_t uart_bitLenght(uint8_t device);
uint8_t uart_bitParity(uint8_t device);

int uart_put(uint8_t device, uint16_t word);
uint16_t uart_get(uint8_t device, uint16_t word);

#ifdef UART_RP
 int uart_setRxPin(uint8_t device, uint16_t rxPin);
 int uart_setTxPin(uint8_t device, uint16_t txPin);
 int uart_setCtsPin(uint8_t device, uint16_t ctsPin);
 int uart_setRtsPin(uint8_t device, uint16_t rtsPin);
#else
 #define uart_setRxPin(device, param) 0
 #define uart_setTxPin(device, param) 0
 #define uart_setCtsPin(device, param) 0
 #define uart_setRtsPin(device, param) 0
#endif

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
 #include "uart_dspic.h"
#else
 #error Unsuported ARCHI
#endif

#endif // UART_H
