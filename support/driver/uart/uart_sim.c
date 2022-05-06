/**
 * @file uart_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart simulator support for udevkit for simulation purpose
 */

#include "uart_sim.h"
#include "simulator.h"
#include "uart.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#if !defined(UART_COUNT) || UART_COUNT == 0
#    warning No device
#endif

#include <stdio.h>

/****************************************************************************************/
/*          Privates functions                                                          */
void uart_sendconfig(uint8_t uart);

/****************************************************************************************/
/*          External variable                                                           */

/****************************************************************************************/
/*          Local variable                                                              */

uart_dev uarts[] = {
    {.baudSpeed = 0},
#if UART_COUNT >= 2
    {.baudSpeed = 0},
#endif
#if UART_COUNT >= 3
    {.baudSpeed = 0},
#endif
#if UART_COUNT >= 4
    {.baudSpeed = 0},
#endif
#if UART_COUNT >= 5
    {.baudSpeed = 0},
#endif
#if UART_COUNT >= 6
    {.baudSpeed = 0},
#endif
};

void uart_sendconfig(uint8_t uart)
{
    simulator_send(UART_SIM_MODULE, uart, UART_SIM_CONFIG, (char *)&uarts[uart], sizeof(uart_dev));
}

rt_dev_t uart_getFreeDevice(void)
{
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < UART_COUNT; i++)
    {
        if (uarts[i].baudSpeed == 0)
        {
            break;
        }
    }

    if (i == UART_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_UART, i);

    uart_open(i);

    return device;
}

int uart_open(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    uarts[uart].baudSpeed = 115200;
    uarts[uart].bitLength = 8;
    uarts[uart].bitStop = 1;
    uarts[uart].bitParity = UART_BIT_PARITY_NONE;
    uart_sendconfig(uart);

    return 0;
}

void uart_close(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return;
    }

    uarts[uart].baudSpeed = 0;
    uart_sendconfig(uart);
}

int uart_enable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    uarts[uart].enabled = 1;
    uart_sendconfig(uart);

    return 0;
}

int uart_disable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    uarts[uart].enabled = 0;
    uart_sendconfig(uart);

    return 0;
}

int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    uarts[uart].baudSpeed = baudSpeed;
    uart_sendconfig(uart);

    return 0;
}

uint32_t uart_baudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return uarts[uart].baudSpeed;
}

uint32_t uart_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return uarts[uart].baudSpeed;
}

int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    uarts[uart].bitLength = bitLength;
    uarts[uart].bitStop = bitStop;
    uarts[uart].bitParity = bitParity;
    uart_sendconfig(uart);

    return 0;
}

uint8_t uart_bitLength(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return uarts[uart].bitLength;
}

uint8_t uart_bitParity(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return uarts[uart].bitParity;
}

uint8_t uart_bitStop(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return uarts[uart].bitStop;
}

int uart_transmitFinished(rt_dev_t device)
{
    int transmitFinished = -1;

    UDK_UNUSED(transmitFinished);

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return 1;
}

ssize_t uart_write(rt_dev_t device, const char *data, size_t size)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    simulator_send(UART_SIM_MODULE, uart, UART_SIM_WRITE, data, size);

    return 0;
}

ssize_t uart_read(rt_dev_t device, char *data, size_t size_max)
{
    ssize_t size_read;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    // TODO
    simulator_rec_task();
    size_read = simulator_recv(UART_SIM_MODULE, uart, UART_SIM_READ, data, size_max);
    if (size_read < 0)
    {
        size_read = 0;
    }

    return size_read;
}
