/**
 * @file a6.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date June 25, 2016, 15:30 PM
 *
 * @brief A6 communication support
 */

#include <archi.h>

#include "a6.h"

#include "board.h"
#include "driver/gpio.h"
#include "driver/uart.h"

rt_dev_t a6_uart;
rt_dev_t a6_txen;
uint8_t a6_inverted;

int a6_init(rt_dev_t uart, rt_dev_t txen, uint8_t inverted)
{
    a6_uart = uart;
    uart_open(a6_uart);
    uart_setBaudSpeed(a6_uart, 1000000);
    uart_setBitConfig(a6_uart, 8, UART_BIT_PARITY_NONE, 1);

    a6_txen = txen;
    a6_inverted = inverted;
    if (a6_txen != NULLDEV)
        gpio_setBitConfig(a6_txen, GPIO_OUTPUT);

    uart_enable(a6_uart);
    return 0;
}

ssize_t a6_write(const char *data, size_t size)
{
    ssize_t byte;
    if (a6_txen != NULLDEV)
    {
        if (a6_inverted == 0)
            gpio_setBit(a6_txen);
        else
            gpio_clearBit(a6_txen);
    }
    byte = uart_write(a6_uart, data, size);

    // TODO passe in read mode after

    return byte;
}

ssize_t a6_read(char *data, size_t size_max)
{
    return uart_read(a6_uart, data, size_max);
}

void a6_writeShort(uint16_t channel, uint16_t value)
{
    char data[6];
    data[0] = 0xA6;
    data[1] = (char)(channel >> 8);
    data[2] = (char)(channel & 0x00FF);
    data[3] = (char)(value >> 8);
    data[4] = (char)(value & 0x00FF);
    data[5] = 0x6A;
}

void a6_task(void)
{
}
