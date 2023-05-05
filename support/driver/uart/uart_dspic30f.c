/**
 * @file uart_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 09, 2016, 11:44 AM
 *
 * @brief Uart support for udevkit (dsPIC30F family)
 *
 * Implementation based on Microchip document DS70000582E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70000582e.pdf
 */

#include "uart.h"

#include <archi.h>
#include <driver/sysclock.h>
#include <sys/fifo.h>

#if !defined(UART_COUNT) || UART_COUNT == 0
#    warning "No uart on the current device or unknow device"
#endif

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#ifndef UART_BUFFRX_SIZE
#    define UART_BUFFRX_SIZE 64
#endif
#ifndef UART_BUFFTX_SIZE
#    define UART_BUFFTX_SIZE 64
#endif

enum
{
    UART_FLAG_UNUSED = 0x00
};
typedef struct
{
    union
    {
        struct
        {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned bit9 : 1;
            unsigned parity : 2;
            unsigned stop : 1;
            unsigned : 2;
        };
        uint8_t val;
    };
} uart_status;

struct uart_dev
{
    uint32_t baudSpeed;
    uart_status flags;

    STATIC_FIFO(buffRx, UART_BUFFRX_SIZE);
    STATIC_FIFO(buffTx, UART_BUFFTX_SIZE);
};

static struct uart_dev _uarts[] = {
#if UART_COUNT >= 1
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
#if UART_COUNT >= 2
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
};

/**
 * @brief Gives a free uart device number and open it
 * @return uart device number
 */
rt_dev_t uart_getFreeDevice(void)
{
#if UART_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < UART_COUNT; i++)
    {
        if (_uarts[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == UART_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_UART, i);

    uart_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Opens an uart from his uart rt_dev_t
 * @param uart uart rt_dev_t id
 * @return uart device number
 */
int uart_open(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }
    if (_uarts[uart].flags.used == 1)
    {
        return -1;
    }

    _uarts[uart].flags.used = 1;
    STATIC_FIFO_INIT(_uarts[uart].buffRx, UART_BUFFRX_SIZE);
    STATIC_FIFO_INIT(_uarts[uart].buffTx, UART_BUFFTX_SIZE);

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Closes and release an uart
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_close(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    uart_disable(device);

    _uarts[uart].flags.val = UART_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
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
        return false;
    }

    return (_uarts[uart].flags.used == 1);
}

/**
 * @brief Enables the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_enable(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].flags.enabled = 1;

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1RXIP = 6;  // interrupt priority for receptor
            _U1RXIF = 0;  // clear receive Flag
            _U1RXIE = 1;  // enable receive interrupt

            _U1TXIP = 5;  // interrupt priority for transmitor
            _U1TXIF = 0;  // clear transmit Flag
            _U1TXIE = 1;  // enable transmit interrupt

            U1MODEbits.UARTEN = 1;  // enable uart module
#        ifdef UART_RXEN
            U1STAbits.URXEN = 1;  // enable receiver
#        endif
            U1STAbits.UTXEN = 1;  // enable transmiter
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2RXIP = 6;  // interrupt priority for receptor
            _U2RXIF = 0;  // clear receive Flag
            _U2RXIE = 1;  // enable receive interrupt

            _U2TXIP = 5;  // interrupt priority for transmitor
            _U2TXIF = 0;  // clear transmit Flag
            _U2TXIE = 1;  // enable transmit interrupt

            U2MODEbits.UARTEN = 1;  // enable uart module
#        ifdef UART_RXEN
            U2STAbits.URXEN = 1;  // enable receiver
#        endif
            U2STAbits.UTXEN = 1;  // enable transmiter
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disables the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_disable(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].flags.enabled = 0;

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1RXIE = 0;            // disable receive interrupt
            _U1TXIE = 0;            // disable transmit interrupt
            U1MODEbits.UARTEN = 0;  // disable uart
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2RXIE = 0;            // disable receive interrupt
            _U2TXIE = 0;            // disable transmit interrupt
            U2MODEbits.UARTEN = 0;  // disable uart
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
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
        return false;
    }

    return (_uarts[uart].flags.enabled == 1);
}

/**
 * @brief Sets the speed of receive and transmit of the specified uart device
 * @param device uart device number
 * @param baudSpeed speed of receive and transmit in bauds (bits / s)
 * @return 0 if ok, -1 in case of error
 */
int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
#if UART_COUNT >= 1
    uint32_t systemClockPeriph;
    uint16_t uBrg;
    uint8_t enabled = 0;

    // check parameters
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }
    if (baudSpeed == 0)
    {
        return -1;
    }

    // disable uart if it was already enabled
    if (_uarts[uart].flags.enabled == 1)
    {
        uart_disable(device);
        enabled = 1;
    }

    _uarts[uart].baudSpeed = baudSpeed;

    // baud rate computation
    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_UART);
    uBrg = systemClockPeriph / baudSpeed;
    uBrg = uBrg >> 4;
    if (uBrg >= UART_MAXBRG)
    {
        uBrg = UART_MAXBRG;
    }

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1BRG = uBrg - 1;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2BRG = uBrg - 1;
            break;
#    endif
    }

    if (enabled == 1)
    {
        uart_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gets the true baud speed of the specified uart device
 * @param device uart device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t uart_baudSpeed(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint32_t baudSpeed;
    uint16_t uBrg;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            uBrg = U1BRG + 1;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            uBrg = U2BRG + 1;
            break;
#    endif
    }

    baudSpeed = sysclock_periphFreq(SYSCLOCK_CLOCK_UART) / uBrg;
    baudSpeed = baudSpeed >> 4;

    return baudSpeed;
#else
    return 0;
#endif
}

/**
 * @brief Gets the effective baud speed of the specified uart device
 * @param device uart device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t uart_effectiveBaudSpeed(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return _uarts[uart].baudSpeed;
#else
    return 0;
#endif
}

/**
 * @brief Sets the config bit (bit length, stop bits, parity) of the specified
 * uart device
 * @param device uart device number
 * @param bitLength
 * @param bitParity
 * @param bitStop
 * @return 0 if ok, -1 in case of error
 */
int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop)
{
#if UART_COUNT >= 1
    uint8_t bit = 0, stop = 0;
    uart_status flags;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    flags = _uarts[uart].flags;
    if (bitLength == 9)
    {
        flags.bit9 = 1;
        flags.parity = UART_BIT_PARITY_NONE;
        bit = 0b11;
    }
    else
    {
        flags.bit9 = 0;
        if (bitParity == UART_BIT_PARITY_EVEN)
        {
            flags.parity = UART_BIT_PARITY_EVEN;
        }
        if (bitParity == UART_BIT_PARITY_ODD)
        {
            flags.parity = UART_BIT_PARITY_ODD;
        }
        if (bitParity != UART_BIT_PARITY_NONE)
        {
            bit = bitParity;
        }
    }

    if (bitStop == 2)
    {
        stop = 1;
        flags.stop = 1;
    }
    else
    {
        flags.stop = 0;
    }

    // update flags
    _uarts[uart].flags = flags;

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1MODEbits.STSEL = stop;
            U1MODEbits.PDSEL = bit;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEbits.STSEL = stop;
            U2MODEbits.PDSEL = bit;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gets the bit length of the device
 * @param device uart device number
 * @return length of bytes in bits
 */
uint8_t uart_bitLength(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    if (_uarts[uart].flags.bit9 == 1)
    {
        return 9;
    }
    return 8;
#else
    return 0;
#endif
}

/**
 * @brief Gets the uart parity mode of the specified uart device
 * @param device uart device number
 * @return parity mode
 */
uint8_t uart_bitParity(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return UART_BIT_PARITY_NONE;
    }

    return _uarts[uart].flags.parity;
#else
    return UART_BIT_PARITY_NONE;
#endif
}

/**
 * @brief Gets number of stop bit of the specified uart device
 * @param device uart device number
 * @return number of stop bit
 */
uint8_t uart_bitStop(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    if (_uarts[uart].flags.stop == 1)
    {
        return 2;
    }
    return 1;
#else
    return 0;
#endif
}

#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    char uart_tmpchar[1];
    while (!U1STAbits.UTXBF && fifo_pop(&_uarts[UART1_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U1TXREG = uart_tmpchar[0];
    }
    _U1TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    char rec[4];
    rec[0] = U1RXREG;

    fifo_push(&_uarts[UART1_ID].buffRx, rec, 1);

    _U1RXIF = 0;
}
#endif

#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{
    char uart_tmpchar[1];
    while (!U2STAbits.UTXBF && fifo_pop(&_uarts[UART2_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U2TXREG = uart_tmpchar[0];
    }
    _U2TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    char rec[4];
    rec[0] = U2RXREG;

    fifo_push(&_uarts[UART2_ID].buffRx, rec, 1);

    _U2RXIF = 0;
}
#endif

/**
 * @brief Writes data to uart device
 * @param device uart device number
 * @param data data to write
 * @param size number of data to write
 * @return number of data written (could be less than 'data' if sw buffer full)
 */
ssize_t uart_write(rt_dev_t device, const char *data, size_t size)
{
#if UART_COUNT >= 1
    size_t fifoWritten;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }
    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1TXIE = 0;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2TXIE = 0;
            break;
#    endif
    }

    fifoWritten = fifo_push(&_uarts[uart].buffTx, data, size);

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            if (U1STAbits.TRMT)
            {
                _U1TXInterrupt();
            }
            _U1TXIE = 1;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            if (U2STAbits.TRMT)
            {
                _U2TXInterrupt();
            }
            _U2TXIE = 1;
            break;
#    endif
    }
    return fifoWritten;
#else
    return -1;
#endif
}

/**
 * @brief Notice if transmit hardware buffer is empty
 * @param device uart device number
 * @return 0 if buffer is not empty, 1 if the buffer is empty, -1 if device is not valid
 */
int uart_transmitFinished(rt_dev_t device)
{
    int transmitFinished = -1;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            transmitFinished = U1STAbits.TRMT;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            transmitFinished = U2STAbits.TRMT;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            transmitFinished = U3STAbits.TRMT;
            break;
#endif
    }
    return transmitFinished;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param device uart device number
 * @return number of data ready to read
 */
ssize_t uart_datardy(rt_dev_t device)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return fifo_len(&_uarts[uart].buffRx);
#else
    return -1;
#endif
}

/**
 * @brief Reads `size_max` data received by uart device
 * @param device uart device number
 * @param data output buffer where data will be copy
 * @param size_max maximum number of data to read (size of the buffer 'data')
 * @return number data read
 */
ssize_t uart_read(rt_dev_t device, char *data, size_t size_max)
{
#if UART_COUNT >= 1
    ssize_t size_read;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    size_read = fifo_pop(&_uarts[uart].buffRx, data, size_max);

    return size_read;
#else
    return -1;
#endif
}

/**
 * @brief Reconfigure clocks for all activated UARTs devices. Call this function on clock change.
 */
void uart_reconfig(void)
{
    for (uint8_t i = 0; i < UART_COUNT; i++)
    {
        if (_uarts[i].flags.used == 1 && _uarts[i].baudSpeed != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_UART, i);
            uart_setBaudSpeed(device, _uarts[i].baudSpeed);
        }
    }
}
