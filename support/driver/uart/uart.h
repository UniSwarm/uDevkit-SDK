/**
 * @file uart.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2025
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
#define uart(d) MKDEV(DEV_CLASS_UART, (d) - 1)
rt_dev_t uart_getFreeDevice(void);
int uart_open(rt_dev_t device);
int uart_close(rt_dev_t device);
bool uart_isOpened(rt_dev_t device);

// ==== device enable/disable =====
int uart_enable(rt_dev_t device);
int uart_disable(rt_dev_t device);
bool uart_isEnabled(rt_dev_t device);

// ======== device settings =======
int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(rt_dev_t device);
uint32_t uart_effectiveBaudSpeed(rt_dev_t device);

typedef enum
{
    UART_BIT_PARITY_NONE = 0x0,  ///< No parity bit check
    UART_BIT_PARITY_EVEN = 0x1,  ///< Parity bit even
    UART_BIT_PARITY_ODD = 0x2,   ///< Parity bit odd
} UART_BIT_PARITY;
int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop);
uint8_t uart_bitLength(rt_dev_t device);
uint8_t uart_bitParity(rt_dev_t device);
uint8_t uart_bitStop(rt_dev_t device);

typedef enum
{
    UART_LINE_TX_REVERSED = 0x1,  ///< TX bit polarity reversed
    UART_LINE_RX_REVERSED = 0x2,  ///< RX bit polarity reversed
    UART_LINE_TX_DISABLED = 0x4,  ///< TX bit output disabled
    UART_LINE_RX_DISABLED = 0x8,  ///< RX bit output disabled
} UART_LINE;
int uart_setLineConfig(rt_dev_t device, uint8_t lineConfig);
uint8_t uart_lineConfig(rt_dev_t device);

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
