/**
 * @file uart.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart support for rtprog
 */

#ifndef UART_H
#define UART_H

#include <driver/device.h>

#define UART_BIT_PARITY_NONE 0
#define UART_BIT_PARITY_EVEN 1
#define UART_BIT_PARITY_ODD 2

// ====== device assignation ======
#define uart(d) MKDEV(DEV_CLASS_UART, (d)-1)
rt_dev_t uart_getFreeDevice();
int uart_open(rt_dev_t device);
int uart_close(rt_dev_t device);

// ==== device enable/disable =====
int uart_enable(rt_dev_t device);
int uart_disable(rt_dev_t device);

// ======== device settings =======
int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
uint32_t uart_baudSpeed(rt_dev_t device);
uint32_t uart_effectiveBaudSpeed(rt_dev_t device);

int uart_setBitConfig(rt_dev_t device, uint8_t bitLenght,
                                      uint8_t bitParity,
                                      uint8_t bitStop);
uint8_t uart_bitLenght(rt_dev_t device);
uint8_t uart_bitParity(rt_dev_t device);
uint8_t uart_bitStop(rt_dev_t device);

// ========= device write ========
ssize_t uart_write(rt_dev_t device, const char *data, size_t size);

// ========= device read =========
ssize_t uart_read(rt_dev_t device, char *data, size_t size_max);
size_t uart_datardy(rt_dev_t device);

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev)
  #include "uart_pic24_dspic33.h"
#elif defined(ARCHI_dspic30f)
  #include "uart_dspic30f.h"
#elif defined(ARCHI_pic32mx)
 #include "uart_pic32mx.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) \
 || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "uart_pic32mz_mm_mk.h"
#endif

#endif // UART_H
