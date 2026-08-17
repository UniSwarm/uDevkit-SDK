/**
 * @file uart_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2025
 *
 * @date July 05, 2018, 13:24 PM
 *
 * @brief Uart communication support driver for dsPIC33CH and dsPIC33CK
 *
 * Implementation based on Microchip document DS70000582E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Multiprotocol-Universal-Asynchronous-Receiver-Transmitter-UART-Module-70005288b.pdf
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
    UART_FLAG_UNUSED = 0x0000
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
    uint8_t lineConfig;
};

#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _U1TXInterrupt(void);
void __attribute__((interrupt, auto_psv, weak)) _U1RXInterrupt(void);
Fifo _uart1_buffRx;
char __attribute__((noload, section(".uart1_buffRx"))) _uart1_buffRx_data[UART_BUFFRX_SIZE];
Fifo _uart1_buffTx;
char __attribute__((noload, section(".uart1_buffTx"))) _uart1_buffTx_data[UART_BUFFTX_SIZE];
#endif

#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _U2TXInterrupt(void);
void __attribute__((interrupt, auto_psv, weak)) _U2RXInterrupt(void);
Fifo _uart2_buffRx;
char __attribute__((noload, section(".uart2_buffRx"))) _uart2_buffRx_data[UART_BUFFRX_SIZE];
Fifo _uart2_buffTx;
char __attribute__((noload, section(".uart2_buffTx"))) _uart2_buffTx_data[UART_BUFFTX_SIZE];
#endif

#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _U3TXInterrupt(void);
void __attribute__((interrupt, auto_psv, weak)) _U3RXInterrupt(void);
Fifo _uart3_buffRx;
char __attribute__((noload, section(".uart3_buffRx"))) _uart3_buffRx_data[UART_BUFFRX_SIZE];
Fifo _uart3_buffTx;
char __attribute__((noload, section(".uart3_buffTx"))) _uart3_buffTx_data[UART_BUFFTX_SIZE];
#endif

static struct uart_dev _uarts[] = {
#if UART_COUNT >= 1
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}, .lineConfig = 0},
#endif
#if UART_COUNT >= 2
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}, .lineConfig = 0},
#endif
#if UART_COUNT >= 3
    {.baudSpeed = 0, .flags = {{.val = UART_FLAG_UNUSED}}, .lineConfig = 0},
#endif
};

/**
 * @brief Returns a free UART device number and opens it
 * @return UART device number, or NULLDEV if none available
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
 * @brief Opens a UART device
 * @param device UART device identifier
 * @return 0 on success, -1 on error
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
    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            STATIC_FIFO_INIT(_uart1_buffRx, UART_BUFFRX_SIZE);
            STATIC_FIFO_INIT(_uart1_buffTx, UART_BUFFTX_SIZE);
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            STATIC_FIFO_INIT(_uart2_buffRx, UART_BUFFRX_SIZE);
            STATIC_FIFO_INIT(_uart2_buffTx, UART_BUFFTX_SIZE);
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            STATIC_FIFO_INIT(_uart3_buffRx, UART_BUFFRX_SIZE);
            STATIC_FIFO_INIT(_uart3_buffTx, UART_BUFFTX_SIZE);
            break;
#    endif
    }

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
#        if !defined(UART1_DISABLE_INT)
            _U1RXIP = 6;  // interrupt priority for receptor
            _U1RXIF = 0;  // clear receive Flag
            _U1RXIE = 1;  // enable receive interrupt

            _U1TXIP = 5;  // interrupt priority for transmitor
            _U1TXIF = 0;  // clear transmit Flag
            _U1TXIE = 1;  // enable transmit interrupt

            U1STAHbits.UTXISEL = 0b001;  // only one byte in buffer or less
#        endif

            U1MODEbits.URXEN = ((_uarts[UART1_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);  // enable receiver
            U1MODEbits.UTXEN = ((_uarts[UART1_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);  // enable transmiter
            U1MODEbits.UARTEN = 1;                                                            // enable uart module
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
#        if !defined(UART2_DISABLE_INT)
            _U2RXIP = 6;  // interrupt priority for receptor
            _U2RXIF = 0;  // clear receive Flag
            _U2RXIE = 1;  // enable receive interrupt

            _U2TXIP = 5;  // interrupt priority for transmitor
            _U2TXIF = 0;  // clear transmit Flag
            _U2TXIE = 1;  // enable transmit interrupt

            U2STAHbits.UTXISEL = 0b001;  // only one byte in buffer or less
#        endif

            U2MODEbits.URXEN = ((_uarts[UART2_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);  // enable receiver
            U2MODEbits.UTXEN = ((_uarts[UART2_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);  // enable transmiter
            U2MODEbits.UARTEN = 1;                                                            // enable uart module
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
#        if !defined(UART3_DISABLE_INT)
            _U3RXIP = 6;  // interrupt priority for receptor
            _U3RXIF = 0;  // clear receive Flag
            _U3RXIE = 1;  // enable receive interrupt

            _U3TXIP = 5;  // interrupt priority for transmitor
            _U3TXIF = 0;  // clear transmit Flag
            _U3TXIE = 1;  // enable transmit interrupt

            U3STAHbits.UTXISEL = 0b001;  // only one byte in buffer or less
#        endif

            U3MODEbits.URXEN = ((_uarts[UART3_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);  // enable receiver
            U3MODEbits.UTXEN = ((_uarts[UART3_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);  // enable transmiter
            U3MODEbits.UARTEN = 1;                                                            // enable uart module
            break;
#    endif
    }
#endif
    return 0;
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
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3RXIE = 0;            // disable receive interrupt
            _U3TXIE = 0;            // disable transmit interrupt
            U3MODEbits.UARTEN = 0;  // disable uart
            break;
#    endif
    }
#endif
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
#if UART_COUNT >= 1
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
    uint8_t enabled = 0;
    if (_uarts[uart].flags.enabled == 1)
    {
        uart_disable(device);
        enabled = 1;
    }

    _uarts[uart].baudSpeed = baudSpeed;

    // baud rate computation
    uint32_t systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_FOSC);
    uint32_t uBrg = systemClockPeriph / baudSpeed;
    if (uBrg >= UART_MAXBRG)
    {
        uBrg = UART_MAXBRG;
    }

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1MODEHbits.BCLKSEL = 0b10;  // FOSC source
            U1MODEHbits.BCLKMOD = 1;     // fractional mode
            U1BRG = uBrg & 0xFFFF;
            U1BRGH = uBrg >> 16;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEHbits.BCLKSEL = 0b10;  // FOSC source
            U2MODEHbits.BCLKMOD = 1;     // fractional mode
            U2BRG = uBrg & 0xFFFF;
            U2BRGH = uBrg >> 16;
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            U3MODEHbits.BCLKSEL = 0b10;  // FOSC source
            U3MODEHbits.BCLKMOD = 1;     // fractional mode
            U3BRG = uBrg & 0xFFFF;
            U3BRGH = uBrg >> 16;
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
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    uint32_t uBrg = 0;
    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            uBrg = ((uint32_t)U1BRGH << 16) + U1BRG;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            uBrg = ((uint32_t)U2BRGH << 16) + U2BRG;
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            uBrg = ((uint32_t)U3BRGH << 16) + U3BRG;
            break;
#    endif
    }

    uint32_t baudSpeed = sysclock_periphFreq(SYSCLOCK_CLOCK_FOSC) / uBrg;

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
#if UART_COUNT >= 1
    uint8_t mode = 0, stop = 0;
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
        mode = 0b0100;  // 9 bits
    }
    else
    {
        flags.bit9 = 0;
        if (bitParity == UART_BIT_PARITY_EVEN)
        {
            flags.parity = UART_BIT_PARITY_EVEN;
            mode = 0b0011;  // 8 bits even
        }
        else if (bitParity == UART_BIT_PARITY_ODD)
        {
            flags.parity = UART_BIT_PARITY_ODD;
            mode = 0b0010;  // 8 bits odd
        }
        else
        {
            mode = 0b0000;  // 8 bits
        }
    }

    if (bitStop == 2)
    {
        stop = 0b10;
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
            U1MODEbits.MOD = mode;
            U1MODEHbits.STSEL = stop;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEbits.MOD = mode;
            U2MODEHbits.STSEL = stop;
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            U3MODEbits.MOD = mode;
            U3MODEHbits.STSEL = stop;
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

/**
 * @brief Sets the config line (rx and tx polarity, disable rx or tx line) of the specified
 * uart device
 * @param device uart device number
 * @param lineConfig line option configuration bit field
 * @return 0 if ok, -1 in case of error
 */
int uart_setLineConfig(rt_dev_t device, uint8_t lineConfig)
{
#if UART_COUNT >= 1
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    _uarts[uart].lineConfig = lineConfig;

    switch (uart)
    {
#    if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            U1MODEbits.URXEN = ((_uarts[UART1_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);    // enable receiver
            U1MODEbits.UTXEN = ((_uarts[UART1_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);    // enable transmiter
            U1MODEHbits.URXINV = ((_uarts[UART1_ID].lineConfig & UART_LINE_RX_REVERSED) != 0);  // reverse rx polarity
            U1MODEHbits.UTXINV = ((_uarts[UART1_ID].lineConfig & UART_LINE_TX_REVERSED) != 0);  // reverse tx polarity
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            U2MODEbits.URXEN = ((_uarts[UART2_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);    // enable receiver
            U2MODEbits.UTXEN = ((_uarts[UART2_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);    // enable transmiter
            U2MODEHbits.URXINV = ((_uarts[UART2_ID].lineConfig & UART_LINE_RX_REVERSED) != 0);  // reverse rx polarity
            U2MODEHbits.UTXINV = ((_uarts[UART2_ID].lineConfig & UART_LINE_TX_REVERSED) != 0);  // reverse tx polarity
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            U3MODEbits.URXEN = ((_uarts[UART3_ID].lineConfig & UART_LINE_RX_DISABLED) == 0);    // enable receiver
            U3MODEbits.UTXEN = ((_uarts[UART3_ID].lineConfig & UART_LINE_TX_DISABLED) == 0);    // enable transmiter
            U3MODEHbits.URXINV = ((_uarts[UART3_ID].lineConfig & UART_LINE_RX_REVERSED) != 0);  // reverse rx polarity
            U3MODEHbits.UTXINV = ((_uarts[UART3_ID].lineConfig & UART_LINE_TX_REVERSED) != 0);  // reverse tx polarity
            break;
#    endif
    }
#endif
    return 0;
}

/**
 * @brief Gets the config line (rx and tx polarity, disable rx or tx line) of the specified uart device
 * @param device uart device number
 * @return line option configuration bit field, 128 in case of error
 */
uint8_t uart_lineConfig(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 128;
    }

    return _uarts[uart].lineConfig;
}

#if (UART_COUNT >= 1) && !defined(UART1_DISABLE) && !defined(UART1_DISABLE_INT)
void __attribute__((interrupt, auto_psv, weak)) _U1TXInterrupt(void)
{
    char uart_tmpchar[1];
    while (!U1STAHbits.UTXBF && fifo_pop(&_uart1_buffTx, uart_tmpchar, 1) == 1)
    {
        U1TXREG = uart_tmpchar[0];
    }
    _U1TXIF = 0;
}

void __attribute__((interrupt, auto_psv, weak)) _U1RXInterrupt(void)
{
    char rec[4];
    rec[0] = U1RXREG;

    fifo_push(&_uart1_buffRx, rec, 1);

    _U1RXIF = 0;
}
#endif

#if (UART_COUNT >= 2) && !defined(UART2_DISABLE) && !defined(UART2_DISABLE_INT)
void __attribute__((interrupt, auto_psv, weak)) _U2TXInterrupt(void)
{
    char uart_tmpchar[1];
    while (!U2STAHbits.UTXBF && fifo_pop(&_uart2_buffTx, uart_tmpchar, 1) == 1)
    {
        U2TXREG = uart_tmpchar[0];
    }
    _U2TXIF = 0;
}

void __attribute__((interrupt, auto_psv, weak)) _U2RXInterrupt(void)
{
    char rec[4];
    rec[0] = U2RXREG;

    fifo_push(&_uart2_buffRx, rec, 1);

    _U2RXIF = 0;
}
#endif

#if (UART_COUNT >= 3) && !defined(UART3_DISABLE) && !defined(UART3_DISABLE_INT)
void __attribute__((interrupt, auto_psv, weak)) _U3TXInterrupt(void)
{
    char uart_tmpchar[1];
    while (!U3STAHbits.UTXBF && fifo_pop(&_uart3_buffTx, uart_tmpchar, 1) == 1)
    {
        U3TXREG = uart_tmpchar[0];
    }
    _U3TXIF = 0;
}

void __attribute__((interrupt, auto_psv, weak)) _U3RXInterrupt(void)
{
    char rec[4];
    rec[0] = U3RXREG;

    fifo_push(&_uart3_buffRx, rec, 1);

    _U3RXIF = 0;
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
    size_t fifoWritten = 0;
    char c;
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
            fifoWritten = fifo_push(&_uart1_buffTx, data, size);
            if (U1STAbits.TRMT)
            {
                while (!U1STAHbits.UTXBF && fifo_pop(&_uart1_buffTx, &c, 1) == 1)
                {
                    U1TXREG = c;
                }
            }
            _U1TXIE = 1;
            break;
#    endif
#    if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            _U2TXIE = 0;
            fifoWritten = fifo_push(&_uart2_buffTx, data, size);
            if (U2STAbits.TRMT)
            {
                while (!U2STAHbits.UTXBF && fifo_pop(&_uart2_buffTx, &c, 1) == 1)
                {
                    U2TXREG = c;
                }
            }
            _U2TXIE = 1;
            break;
#    endif
#    if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            _U3TXIE = 0;
            fifoWritten = fifo_push(&_uart3_buffTx, data, size);
            if (U3STAbits.TRMT)
            {
                while (!U3STAHbits.UTXBF && fifo_pop(&_uart3_buffTx, &c, 1) == 1)
                {
                    U3TXREG = c;
                }
            }
            _U3TXIE = 1;
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
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return -1;
    }

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            return fifo_len(&_uart1_buffRx);
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            return fifo_len(&_uart2_buffRx);
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            return fifo_len(&_uart3_buffRx);
#endif
    }
    return -1;
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
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
    {
        return 0;
    }

    switch (uart)
    {
#if (UART_COUNT >= 1) && !defined(UART1_DISABLE)
        case UART1_ID:
            return fifo_pop(&_uart1_buffRx, data, size_max);
#endif
#if (UART_COUNT >= 2) && !defined(UART2_DISABLE)
        case UART2_ID:
            return fifo_pop(&_uart2_buffRx, data, size_max);
#endif
#if (UART_COUNT >= 3) && !defined(UART3_DISABLE)
        case UART3_ID:
            return fifo_pop(&_uart3_buffRx, data, size_max);
#endif
    }

    return 0;
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
