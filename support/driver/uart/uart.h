/**
 * @file uart.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart support for udevkit
 */

#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uart_device.h"

// ====== device assignation ======
#define uart(d) MKDEV(DEV_CLASS_UART, (d)-1)
rt_dev_t uart_getFreeDevice(void);
int uart_open(rt_dev_t device);
int uart_close(rt_dev_t device);

// ==== device enable/disable =====
int uart_enable(rt_dev_t device);
int uart_disable(rt_dev_t device);

// ======== device settings =======
int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(rt_dev_t device);
uint32_t uart_effectiveBaudSpeed(rt_dev_t device);

#define UART_BIT_PARITY_NONE 0
#define UART_BIT_PARITY_EVEN 1
#define UART_BIT_PARITY_ODD  2
int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop);
uint8_t uart_bitLength(rt_dev_t device);
uint8_t uart_bitParity(rt_dev_t device);
uint8_t uart_bitStop(rt_dev_t device);

// ========= device write ========
ssize_t uart_write(rt_dev_t device, const char *data, size_t size);
int uart_transmitFinished(rt_dev_t device);

// ========= device read =========
ssize_t uart_read(rt_dev_t device, char *data, size_t size_max);
ssize_t uart_datardy(rt_dev_t device);

// ======= dynamic clock =======
void uart_reconfig(void);

#ifdef __cplusplus
}
#endif

#endif  // UART_H
