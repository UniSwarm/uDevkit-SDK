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
#include <stdlib.h>

#define UART_BIT_PARITY_NONE 0
#define UART_BIT_PARITY_EVEN 1
#define UART_BIT_PARITY_ODD 2

// ====== device assignation ======
uint8_t uart_getFreeDevice();
void uart_releaseDevice(uint8_t device);

// ==== device enable/disable =====
int uart_enable(uint8_t device);
int uart_disable(uint8_t device);

// ======== device settings =======
int uart_setBaudSpeed(uint8_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(uint8_t device);
uint32_t uart_effectiveBaudSpeed(uint8_t device);

int uart_setBitConfig(uint8_t device, uint8_t bitLenght,
                                      uint8_t bitParity,
                                      uint8_t bitStop);
uint8_t uart_bitLenght(uint8_t device);
uint8_t uart_bitParity(uint8_t device);
uint8_t uart_bitStop(uint8_t device);

// ========= device write ========
int uart_putc(uint8_t device, const char c);
int uart_putw(uint8_t device, const uint16_t word);

int uart_write(uint8_t device, const char *data, size_t size);
int uart_flush(uint8_t device);

// ========= device read =========
char uart_getc(uint8_t device);
uint16_t uart_getw(uint8_t device);
uint8_t uart_datardy(uint8_t device);

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
#error "Unsupported ARCHI"
#endif

#endif // UART_H
