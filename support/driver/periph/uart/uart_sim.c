/**
 * @file uart_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart simulator support for rtprog
 */

#include "uart.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#if !defined (UART_COUNT) || UART_COUNT==0
    #error No device
#endif

#include <stdio.h>

#define UART_BUFFRX_SIZE 64

struct uart_dev
{
    uint32_t baudSpeed;

    STATIC_FIFO(buffRx, UART_BUFFRX_SIZE);
};

struct uart_dev uarts[] = {
    {.baudSpeed=0},
#if UART_COUNT>=2
    {.baudSpeed=0},
#endif
#if UART_COUNT>=3
    {.baudSpeed=0},
#endif
#if UART_COUNT>=4
    {.baudSpeed=0},
#endif
};

rt_dev_t uart_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < UART_COUNT; i++)
        if (uarts[i].baudSpeed == 0)
            break;

    if (i == UART_COUNT)
        return NULLDEV;

    uarts[i].baudSpeed = 1;
    STATIC_FIFO_INIT(uarts[i].buffRx, UART_BUFFRX_SIZE);

    return MKDEV(DEV_CLASS_UART, i);
}

void uart_releaseDevice(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return;

    uarts[uart].baudSpeed = 0;
}

int uart_enable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    return 0;
}

int uart_disable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    return 0;
}

int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;
    
    uarts[uart].baudSpeed = baudSpeed;

    return 0;
}

uint32_t uart_baudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;

    return 0;
}

uint32_t uart_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;

    return uarts[uart].baudSpeed;
}

int uart_setBitConfig(rt_dev_t device, uint8_t bitLenght,
                      uint8_t bitParity, uint8_t bitStop)
{
    return 0;
}

uint8_t uart_bitLenght(rt_dev_t device)
{
    uint8_t lenght = 8;

    return lenght;
}

uint8_t uart_bitParity(rt_dev_t device)
{
    uint8_t parity = UART_BIT_PARITY_NONE;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    return parity;
}

uint8_t uart_bitStop(rt_dev_t device)
{
    uint8_t stop;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    return stop << 1;
}

ssize_t uart_write(rt_dev_t device, const char *data, size_t size)
{
    size_t i;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    // TODO
    printf("%s", data); fflush(stdout);

    return 0;
}

ssize_t uart_read(rt_dev_t device, char *data, size_t size_max)
{
	size_t size_read;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;
    
    size_read = fifo_pop(&uarts[uart].buffRx, data, size_max);
    
    return size_read;
}
