/**
 * @file uart_pic32mz_mm_mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief Uart support for udevkit for PIC32MM, PIC32MK, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61107G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf
 */

#include "uart.h"

#include <archi.h>
#include <driver/int.h>
#include <driver/sysclock.h>
#include <sys/fifo.h>

#if !defined(UART_COUNT) || UART_COUNT == 0
#    error "No uart on the current device or unknow device"
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

#ifndef INT_MODE
#    define INT_MODE INT_DEFAULT_MODE
#endif
#ifndef UART_INTERRUPT_PRIORITY
#    define UART_INTERRUPT_PRIORITY 3
#endif
#ifndef UART_INTERRUPT_TX_PRIORITY
#    define UART_INTERRUPT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART_INTERRUPT_RX_PRIORITY
#    define UART_INTERRUPT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART1_INT_TX_PRIORITY
#    define UART1_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART1_INT_RX_PRIORITY
#    define UART1_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART2_INT_TX_PRIORITY
#    define UART2_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART2_INT_RX_PRIORITY
#    define UART2_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART3_INT_TX_PRIORITY
#    define UART3_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART3_INT_RX_PRIORITY
#    define UART3_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART4_INT_TX_PRIORITY
#    define UART4_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART4_INT_RX_PRIORITY
#    define UART4_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART5_INT_TX_PRIORITY
#    define UART5_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART5_INT_RX_PRIORITY
#    define UART5_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART6_INT_TX_PRIORITY
#    define UART6_INT_TX_PRIORITY UART_INTERRUPT_PRIORITY
#endif
#ifndef UART6_INT_RX_PRIORITY
#    define UART6_INT_RX_PRIORITY UART_INTERRUPT_PRIORITY
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
#if UART_COUNT >= 3
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
#if UART_COUNT >= 4
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
#if UART_COUNT >= 5
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
#if UART_COUNT >= 6
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}},
#endif
};

#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
void U1RXInterrupt(void);
void U1TXInterrupt(void);
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
void U2RXInterrupt(void);
void U2TXInterrupt(void);
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
void U3RXInterrupt(void);
void U3TXInterrupt(void);
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
void U4RXInterrupt(void);
void U4TXInterrupt(void);
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
void U5RXInterrupt(void);
void U5TXInterrupt(void);
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
void U6RXInterrupt(void);
void U6TXInterrupt(void);
#endif

#if defined(ARCHI_pic32mk)
uint32_t uart_getClock(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 1;
    }

    if (uart < 2)
    {
        return sysclock_periphFreq(SYSCLOCK_CLOCK_UART1_2);
    }

    return sysclock_periphFreq(SYSCLOCK_CLOCK_UART3_6);
}
#endif  // ARCHI_pic32mk

/**
 * @brief Gives a free uart device number and open it
 * @return uart device number
 */
rt_dev_t uart_getFreeDevice(void)
{
#if UART_COUNT >= 1
    uint8_t uart_id;
    for (uart_id = 0; uart_id < UART_COUNT; uart_id++)
    {
        if (_uarts[uart_id].flags.used == 0)
        {
            break;
        }
    }

    if (uart_id == UART_COUNT)
    {
        return NULLDEV;
    }
    rt_dev_t device = MKDEV(DEV_CLASS_UART, uart_id);

    uart_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Opens an uart from his uart rt_dev_t
 * @param uart uart rt_dev_t id
 * @return 0 if ok, -1 in case of error
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
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].flags.enabled = 1;

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U1RXIF = 0;                        // clear receive Flag
            _U1RXIE = 1;                        // enable receive interrupt

            _U1TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U1TXIF = 0;                        // clear transmit Flag
            _U1TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U1STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U1MODEbits.UARTEN = 1;  // enable uart module
            U1STAbits.UTXEN = 1;    // enable transmiter
            U1STAbits.URXEN = 1;    // enable receiver
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U2RXIF = 0;                        // clear receive Flag
            _U2RXIE = 1;                        // enable receive interrupt

            _U2TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U2TXIF = 0;                        // clear transmit Flag
            _U2TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U2STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U2MODEbits.UARTEN = 1;  // enable uart module
            U2STAbits.UTXEN = 1;    // enable transmiter
            U2STAbits.URXEN = 1;    // enable receiver
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U3RXIF = 0;                        // clear receive Flag
            _U3RXIE = 1;                        // enable receive interrupt

            _U3TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U3TXIF = 0;                        // clear transmit Flag
            _U3TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U3STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U3MODEbits.UARTEN = 1;  // enable uart module
            U3STAbits.UTXEN = 1;    // enable transmiter
            U3STAbits.URXEN = 1;    // enable receiver
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            _U4RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U4RXIF = 0;                        // clear receive Flag
            _U4RXIE = 1;                        // enable receive interrupt

            _U4TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U4TXIF = 0;                        // clear transmit Flag
            _U4TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U4STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U4MODEbits.UARTEN = 1;  // enable uart module
            U4STAbits.UTXEN = 1;    // enable transmiter
            U4STAbits.URXEN = 1;    // enable receiver
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            _U5RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U5RXIF = 0;                        // clear receive Flag
            _U5RXIE = 1;                        // enable receive interrupt

            _U5TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U5TXIF = 0;                        // clear transmit Flag
            _U5TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U5STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U5MODEbits.UARTEN = 1;  // enable uart module
            U5STAbits.UTXEN = 1;    // enable transmiter
            U5STAbits.URXEN = 1;    // enable receiver
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            _U6RXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for receptor
            _U6RXIF = 0;                        // clear receive Flag
            _U6RXIE = 1;                        // enable receive interrupt

            _U6TXIP = UART_INTERRUPT_PRIORITY;  // interrupt priority for transmitor
            _U6TXIF = 0;                        // clear transmit Flag
            _U6TXIE = 0;                        // disable transmit interrupt
#    ifndef ARCHI_pic32mk
            U6STAbits.UTXISEL = 0b10;  // transmit interrupt generated when buffer is empty
#    endif

            U6MODEbits.UARTEN = 1;  // enable uart module
            U6STAbits.UTXEN = 1;    // enable transmiter
            U6STAbits.URXEN = 1;    // enable receiver
            break;
#endif
    }

    return 0;
}

/**
 * @brief Disables the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_disable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].flags.enabled = 0;

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1RXIE = 0;            // disable receive interrupt
            _U1TXIE = 0;            // disable transmit interrupt
            U1MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2RXIE = 0;            // disable receive interrupt
            _U2TXIE = 0;            // disable transmit interrupt
            U2MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3RXIE = 0;            // disable receive interrupt
            _U3TXIE = 0;            // disable transmit interrupt
            U3MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            _U4RXIE = 0;            // disable receive interrupt
            _U4TXIE = 0;            // disable transmit interrupt
            U4MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            _U5RXIE = 0;            // disable receive interrupt
            _U5TXIE = 0;            // disable transmit interrupt
            U5MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            _U6RXIE = 0;            // disable receive interrupt
            _U6TXIE = 0;            // disable transmit interrupt
            U6MODEbits.UARTEN = 0;  // disable uart
            break;
#endif
    }

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
    uint32_t systemClockPeriph;
    uint32_t uBrg;  // support for 20 bits BRG
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
    systemClockPeriph = uart_getClock(device);
    uBrg = systemClockPeriph / baudSpeed;
    if (uBrg >= UART_MAXBRG)
    {
        uBrg = UART_MAXBRG;
    }

    // high speed baud rate mode
    uint8_t hspeed;
    if ((uBrg & 0x0F) == 0)
    {
        hspeed = 0;
        uBrg = uBrg >> 4;
    }
    else
    {
        hspeed = 1;
        uBrg = uBrg >> 2;
    }

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1MODEbits.BRGH = hspeed;
            U1BRG = uBrg - 1;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEbits.BRGH = hspeed;
            U2BRG = uBrg - 1;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            U3MODEbits.BRGH = hspeed;
            U3BRG = uBrg - 1;
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            U4MODEbits.BRGH = hspeed;
            U4BRG = uBrg - 1;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            U5MODEbits.BRGH = hspeed;
            U5BRG = uBrg - 1;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            U6MODEbits.BRGH = hspeed;
            U6BRG = uBrg - 1;
            break;
#endif
    }

    if (enabled == 1)
    {
        uart_enable(device);
    }

    return 0;
}

/**
 * @brief Gets the true baud speed of the specified uart device
 * @param device uart device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t uart_baudSpeed(rt_dev_t device)
{
    uint32_t baudSpeed;
    uint16_t uBrg;
    uint8_t hspeed;

    uint8_t uart = MINOR(device);

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            hspeed = U1MODEbits.BRGH;
            uBrg = U1BRG + 1;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            hspeed = U2MODEbits.BRGH;
            uBrg = U2BRG + 1;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            hspeed = U3MODEbits.BRGH;
            uBrg = U3BRG + 1;
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            hspeed = U4MODEbits.BRGH;
            uBrg = U4BRG + 1;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            hspeed = U5MODEbits.BRGH;
            uBrg = U5BRG + 1;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            hspeed = U6MODEbits.BRGH;
            uBrg = U6BRG + 1;
            break;
#endif
        default:
            return 0;
    }

    baudSpeed = uart_getClock(device) / uBrg;
    if (hspeed == 1)
    {
        baudSpeed = baudSpeed >> 2;
    }
    else
    {
        baudSpeed = baudSpeed >> 4;
    }

    return baudSpeed;
}

/**
 * @brief Gets the effective baud speed of the specified uart device
 * @param device uart device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t uart_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    return _uarts[uart].baudSpeed;
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
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1MODEbits.STSEL = stop;
            U1MODEbits.PDSEL = bit;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEbits.STSEL = stop;
            U2MODEbits.PDSEL = bit;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            U3MODEbits.STSEL = stop;
            U3MODEbits.PDSEL = bit;
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            U4MODEbits.STSEL = stop;
            U4MODEbits.PDSEL = bit;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            U5MODEbits.STSEL = stop;
            U5MODEbits.PDSEL = bit;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            U6MODEbits.STSEL = stop;
            U6MODEbits.PDSEL = bit;
            break;
#endif
    }
    return 0;
}

/**
 * @brief Gets the bit length of the device
 * @param device uart device number
 * @return length of bytes in bits
 */
uint8_t uart_bitLength(rt_dev_t device)
{
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
}

/**
 * @brief Gets the uart parity mode of the specified uart device
 * @param device uart device number
 * @return parity mode
 */
uint8_t uart_bitParity(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return _uarts[uart].flags.parity;
}

/**
 * @brief Gets number of stop bit of the specified uart device
 * @param device uart device number
 * @return number of stop bit
 */
uint8_t uart_bitStop(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    if (_uarts[uart].flags.stop == 1)
    {
        return 2;
    }
    return 1;
}

#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
void INT_ISR(_UART1_TX_VECTOR, UART1_INT_TX_PRIORITY, INT_MODE) U1TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U1TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U1STAbits.UTXBF && fifo_pop(&_uarts[UART1_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U1TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART1_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U1TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART1_ID].buffTx) == 0)
    {
        _U1TXIE = 0;
    }
    _U1TXIF = 0;
}

void INT_ISR(_UART1_RX_VECTOR, UART1_INT_RX_PRIORITY, INT_MODE) U1RXInterrupt(void)
{
    char rec[4];
    while (U1STAbits.URXDA == 1)
    {
        rec[0] = U1RXREG;
        fifo_push(&_uarts[UART1_ID].buffRx, rec, 1);
    }

    _U1RXIF = 0;
}
#endif

#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
void INT_ISR(_UART2_TX_VECTOR, UART2_INT_TX_PRIORITY, INT_MODE) U2TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U2TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U2STAbits.UTXBF && fifo_pop(&_uarts[UART2_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U2TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART2_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U2TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART2_ID].buffTx) == 0)
    {
        _U2TXIE = 0;
    }
    _U2TXIF = 0;
}

void INT_ISR(_UART2_RX_VECTOR, UART2_INT_RX_PRIORITY, INT_MODE) U2RXInterrupt(void)
{
    char rec[4];
    while (U2STAbits.URXDA == 1)
    {
        rec[0] = U2RXREG;
        fifo_push(&_uarts[UART2_ID].buffRx, rec, 1);
    }

    _U2RXIF = 0;
}
#endif

#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
void INT_ISR(_UART3_TX_VECTOR, UART3_INT_TX_PRIORITY, INT_MODE) U3TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U3TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U3STAbits.UTXBF && fifo_pop(&_uarts[UART3_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U3TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART3_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U3TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART3_ID].buffTx) == 0)
    {
        _U3TXIE = 0;
    }
    _U3TXIF = 0;
}

void INT_ISR(_UART3_RX_VECTOR, UART3_INT_RX_PRIORITY, INT_MODE) U3RXInterrupt(void)
{
    char rec[4];
    while (U3STAbits.URXDA == 1)
    {
        rec[0] = U3RXREG;
        fifo_push(&_uarts[UART3_ID].buffRx, rec, 1);
    }

    _U3RXIF = 0;
}
#endif

#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
void INT_ISR(_UART4_TX_VECTOR, UART4_INT_TX_PRIORITY, INT_MODE) U4TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U4TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U4STAbits.UTXBF && fifo_pop(&_uarts[UART4_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U4TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART4_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U4TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART4_ID].buffTx) == 0)
    {
        _U4TXIE = 0;
    }
    _U4TXIF = 0;
}

void INT_ISR(_UART4_RX_VECTOR, UART4_INT_RX_PRIORITY, INT_MODE) U4RXInterrupt(void)
{
    char rec[4];
    while (U4STAbits.URXDA == 1)
    {
        rec[0] = U4RXREG;
        fifo_push(&_uarts[UART4_ID].buffRx, rec, 1);
    }

    _U4RXIF = 0;
}
#endif

#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
void INT_ISR(_UART5_TX_VECTOR, UART5_INT_TX_PRIORITY, INT_MODE) U5TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U5TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U5STAbits.UTXBF && fifo_pop(&_uarts[UART5_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U5TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART5_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U5TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART5_ID].buffTx) == 0)
    {
        _U5TXIE = 0;
    }
    _U5TXIF = 0;
}

void INT_ISR(_UART5_RX_VECTOR, UART5_INT_RX_PRIORITY, INT_MODE) U5RXInterrupt(void)
{
    char rec[4];
    while (U5STAbits.URXDA == 1)
    {
        rec[0] = U5RXREG;
        fifo_push(&_uarts[UART5_ID].buffRx, rec, 1);
    }

    _U5RXIF = 0;
}
#endif

#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
void INT_ISR(_UART6_TX_VECTOR, UART6_INT_TX_PRIORITY, INT_MODE) U6TXInterrupt(void)
{
#    if defined(ARCHI_pic32mk)
    _U6TXIF = 0;  // 32MK Work around (errata 41)
    char uart_tmpchar[1];
    while (!U6STAbits.UTXBF && fifo_pop(&_uarts[UART6_ID].buffTx, uart_tmpchar, 1) == 1)
    {
        U6TXREG = (unsigned char)uart_tmpchar[0];
    }
#    else
    size_t i;
    char uart_tmpchar[8];
    size_t readen = fifo_pop(&_uarts[UART6_ID].buffTx, uart_tmpchar, 8);
    for (i = 0; i < readen; i++)
    {
        U6TXREG = (unsigned char)uart_tmpchar[i];
    }
#    endif

    if (fifo_len(&_uarts[UART6_ID].buffTx) == 0)
    {
        _U6TXIE = 0;
    }
    _U6TXIF = 0;
}

void INT_ISR(_UART6_RX_VECTOR, UART6_INT_RX_PRIORITY, INT_MODE) U6RXInterrupt(void)
{
    char rec[4];
    while (U6STAbits.URXDA == 1)
    {
        rec[0] = U6RXREG;
        fifo_push(&_uarts[UART6_ID].buffRx, rec, 1);
    }

    _U6RXIF = 0;
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
    size_t fifoWritten;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }
    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1TXIE = 0;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2TXIE = 0;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3TXIE = 0;
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            _U4TXIE = 0;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            _U5TXIE = 0;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            _U6TXIE = 0;
            break;
#endif
    }

    fifoWritten = fifo_push(&_uarts[uart].buffTx, data, size);

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            _U1TXIE = 1;
            break;
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2TXIE = 1;
            break;
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3TXIE = 1;
            break;
#endif
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            _U4TXIE = 1;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            _U5TXIE = 1;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            _U6TXIE = 1;
            break;
#endif
    }
    return (ssize_t)fifoWritten;
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
#if (UART_COUNT >= 4) && !defined(UART4_DISABLE)
        case UART4_ID:
            transmitFinished = U4STAbits.TRMT;
            break;
#endif
#if (UART_COUNT >= 5) && !defined(UART5_DISABLE)
        case UART5_ID:
            transmitFinished = U5STAbits.TRMT;
            break;
#endif
#if (UART_COUNT >= 6) && !defined(UART6_DISABLE)
        case UART6_ID:
            transmitFinished = U6STAbits.TRMT;
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
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    return (ssize_t)fifo_len(&_uarts[uart].buffRx);
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
    ssize_t size_read;
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    size_read = (ssize_t)fifo_pop(&_uarts[uart].buffRx, data, size_max);

    return size_read;
}

/**
 * @brief Reconfigure clocks for all activated UARTs devices. Call this function on clock change.
 */
void uart_reconfig(void)
{
    for (uint8_t uart_id = 0; uart_id < UART_COUNT; uart_id++)
    {
        if (_uarts[uart_id].flags.used == 1 && _uarts[uart_id].baudSpeed != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_UART, uart_id);
            uart_setBaudSpeed(device, _uarts[uart_id].baudSpeed);
        }
    }
}
