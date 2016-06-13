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

#include "driver/device.h"

#define UART_BIT_PARITY_NONE 0
#define UART_BIT_PARITY_EVEN 1
#define UART_BIT_PARITY_ODD 2

// ====== device assignation ======
dev_t uart_getFreeDevice();
void uart_releaseDevice(dev_t device);

// ==== device enable/disable =====
int uart_enable(dev_t device);
int uart_disable(dev_t device);

// ======== device settings =======
int uart_setBaudSpeed(dev_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(dev_t device);
uint32_t uart_effectiveBaudSpeed(dev_t device);

int uart_setBitConfig(dev_t device, uint8_t bitLenght,
                                      uint8_t bitParity,
                                      uint8_t bitStop);
uint8_t uart_bitLenght(dev_t device);
uint8_t uart_bitParity(dev_t device);
uint8_t uart_bitStop(dev_t device);

// ========= device write ========
int uart_putc(dev_t device, const char c);
int uart_putw(dev_t device, const uint16_t word);

int uart_write(dev_t device, const char *data, size_t size);
int uart_flush(dev_t device);

// ========= device read =========
char uart_getc(dev_t device);
uint16_t uart_getw(dev_t device);
uint8_t uart_datardy(dev_t device);
size_t uart_read(dev_t device, char *data, size_t size_max);

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
#include "uart_dspic.h"
#else
#error "Unsupported ARCHI"
#endif

#endif // UART_H
