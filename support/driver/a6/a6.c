/**
 * @file a6.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 25, 2016, 15:30 PM 
 * 
 * @brief A6 communication support
 */

#include <xc.h>

#include "a6.h"

#include "driver/uart.h"
#include "board.h"

rt_dev_t a6_uart;

int a6_init()
{
	a6_uart = uart_getFreeDevice();
	uart_setBaudSpeed(a6_uart, 1000000);
	uart_setBitConfig(a6_uart, 8, UART_BIT_PARITY_NONE, 1);

    A6_RW = A6_READ;

	uart_enable(a6_uart);
	return 0;
}

ssize_t a6_write(const char *data, size_t size)
{
    ssize_t byte;
    A6_RW = A6_WRITE;
    byte = uart_write(a6_uart, data, size);
    uart_flush(a6_uart);
    A6_RW = A6_READ;
    return byte;
}

ssize_t a6_read(char *data, size_t size_max)
{
    return uart_read(a6_uart, data, size_max);
}
