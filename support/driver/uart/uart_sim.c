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

static void _uart_sendconfig(uint8_t uart);

static uart_dev _uarts[] = {
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

void _uart_sendconfig(uint8_t uart)
{
    simulator_send(UART_SIM_MODULE, uart, UART_SIM_CONFIG, (char *)&_uarts[uart], sizeof(uart_dev));
}

rt_dev_t uart_getFreeDevice(void)
{
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < UART_COUNT; i++)
    {
        if (_uarts[i].used == 0)
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

    _uarts[uart].baudSpeed = 115200;
    _uarts[uart].bitLength = 8;
    _uarts[uart].bitStop = 1;
    _uarts[uart].bitParity = UART_BIT_PARITY_NONE;
    _uarts[uart].used = 1;
    _uarts[uart].enabled = 0;
    _uart_sendconfig(uart);

    return 0;
}

int uart_close(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].used = 0;
    _uart_sendconfig(uart);

    return 0;
}

/**
 * @brief UART sdk state
 * @param device uart device number
 * @return true if uart was openned by uart_open function
 */
bool uart_isOpened(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return (_uarts[uart].used == 1);
}

int uart_enable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].enabled = 1;
    _uart_sendconfig(uart);

    return 0;
}

int uart_disable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].enabled = 0;
    _uart_sendconfig(uart);

    return 0;
}

/**
 * @brief UART sdk enabled state
 * @param device uart device number
 * @return true if uart was enabled by uart_enable function
 */
bool uart_isEnabled(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return (_uarts[uart].enabled == 1);
}

int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    _uarts[uart].baudSpeed = baudSpeed;
    _uart_sendconfig(uart);

    return 0;
}

uint32_t uart_baudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return _uarts[uart].baudSpeed;
}

uint32_t uart_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return _uarts[uart].baudSpeed;
}

int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].bitLength = bitLength;
    _uarts[uart].bitStop = bitStop;
    _uarts[uart].bitParity = bitParity;
    _uart_sendconfig(uart);

    return 0;
}

uint8_t uart_bitLength(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return _uarts[uart].bitLength;
}

uint8_t uart_bitParity(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return _uarts[uart].bitParity;
}

uint8_t uart_bitStop(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return _uarts[uart].bitStop;
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

ssize_t uart_datardy(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

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

void uart_reconfig(void)
{
}
