/**
 * @file uart_dspic30.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date August 09, 2016, 11:44 AM
 *
 * @brief Uart support for rtprog (dsPIC30F family)
 */

#include "uart.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#include <xc.h>

#if !defined (UART_COUNT) || UART_COUNT==0
  #warning "No uart on the current device or unknow device"
#endif

#define UART_BUFFRX_SIZE 64

#define UART_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
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
};

struct uart_dev uarts[] = {
    {
        .baudSpeed = 0,
        .flags = {{.val = UART_FLAG_UNUSED}}
    },
#if UART_COUNT>=2
    {
        .baudSpeed = 0,
        .flags = {{.val = UART_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free uart device number
 * @return uart device number
 */
rt_dev_t uart_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < UART_COUNT; i++)
        if (uarts[i].baudSpeed == 0)
            break;

    if (i == UART_COUNT)
        return NULLDEV;

    uarts[i].flags.used = 1;
    STATIC_FIFO_INIT(uarts[i].buffRx, UART_BUFFRX_SIZE);

    return MKDEV(DEV_CLASS_UART, i);
}

/**
 * @brief Release an uart
 * @param device uart device number
 */
void uart_releaseDevice(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return;

    uarts[uart].flags.val = UART_FLAG_UNUSED;
}

/**
 * @brief Enable the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_enable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    uarts[uart].flags.enabled = 1;

    switch (uart)
    {
    case 0:
        IPC2bits.U1RXIP = 6;    // interrupt priority for receptor
        IFS0bits.U1RXIF = 0;    // clear receive Flag
        IEC0bits.U1RXIE = 1;    // enable receive interrupt

        IPC2bits.U1TXIP = 5;    // interrupt priority for transmitor
        IFS0bits.U1TXIF = 0;    // clear transmit Flag
        IEC0bits.U1TXIE = 0;    // disable transmit interrupt

        U1MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U1STAbits.URXEN = 1;    // enable receiver
    #endif
        U1STAbits.UTXEN = 1;    // enable transmiter
        break;
#if UART_COUNT>=2
    case 1:
        IPC6bits.U2RXIP = 6;    // interrupt priority for receptor
        IFS1bits.U2RXIF = 0;    // clear receive Flag
        IEC1bits.U2RXIE = 1;    // enable receive interrupt

        IPC6bits.U2TXIP = 5;    // interrupt priority for transmitor
        IFS1bits.U2TXIF = 0;    // clear transmit Flag
        IEC1bits.U2TXIE = 0;    // disable transmit interrupt

        U2MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U2STAbits.URXEN = 1;    // enable receiver
    #endif
        U2STAbits.UTXEN = 1;    // enable transmiter
        break;
#endif
    }

    return 0;
}

/**
 * @brief Disable the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_disable(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    uarts[uart].flags.enabled = 0;

    switch (uart)
    {
    case 0:
        IEC0bits.U1RXIE = 0;    // disable receive interrupt
        IEC0bits.U1TXIE = 0;    // disable transmit interrupt
        U1MODEbits.UARTEN = 0;  // disable uart
        break;
#if UART_COUNT>=2
    case 1:
        IEC1bits.U2RXIE = 0;    // disable receive interrupt
        IEC1bits.U2TXIE = 0;    // disable transmit interrupt
        U2MODEbits.UARTEN = 0;  // disable uart
        break;
#endif
    }

    return 0;
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
    uint16_t uBrg;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    if (baudSpeed == 0)
        return -1;

    uarts[uart].baudSpeed = baudSpeed;

    systemClockPeriph = getSystemClockPeriph();
    uBrg = systemClockPeriph / baudSpeed;

    uBrg = uBrg >> 4;

    switch (uart)
    {
    case 0:
        U1BRG = uBrg - 1;
        break;
#if UART_COUNT>=2
    case 1:
        U2BRG = uBrg - 1;
        break;
#endif
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

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;

    switch (uart)
    {
    case 0:
        uBrg = U1BRG + 1;
        break;
#if UART_COUNT>=2
    case 1:
        uBrg = U2BRG + 1;
        break;
#endif
    }

    baudSpeed = getSystemClockPeriph() / uBrg;
    baudSpeed = baudSpeed >> 4;

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
        return 0;

    return uarts[uart].baudSpeed;
}

/**
 * @brief Sets the config bit (bit lenght, stop bits, parity) of the specified
 * uart device
 * @param device uart device number
 * @param bitLenght
 * @param bitParity
 * @param bitStop
 * @return 0 if ok, -1 in case of error
 */
int uart_setBitConfig(rt_dev_t device, uint8_t bitLenght,
                      uint8_t bitParity, uint8_t bitStop)
{
    uint8_t bit = 0, stop = 0;
    uart_status flags;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    flags = uarts[uart].flags;
    if (bitLenght == 9)
    {
        flags.bit9 = 1;
        flags.parity = UART_BIT_PARITY_NONE;
        bit = 0b11;
    }
    else
    {
        flags.bit9 = 0;
        if (bitParity == UART_BIT_PARITY_EVEN)
            flags.parity = UART_BIT_PARITY_EVEN;
        if (bitParity == UART_BIT_PARITY_ODD)
            flags.parity = UART_BIT_PARITY_ODD;
        if (bitParity != UART_BIT_PARITY_NONE)
            bit = bitParity;
    }

    if (bitStop == 2)
    {
        stop = 1;
        flags.stop = 1;
    }
    else
        flags.stop = 0;

    // update flags
    uarts[uart].flags = flags;

    switch (uart)
    {
    case 0:
        U1MODEbits.STSEL = stop;
        U1MODEbits.PDSEL = bit;
        break;
#if UART_COUNT>=2
    case 1:
        U2MODEbits.STSEL = stop;
        U2MODEbits.PDSEL = bit;
        break;
#endif
    }
    return 0;
}

/**
 * @brief Gets the bit lenght of the device
 * @param device uart device number
 * @return lenght of bytes in bits
 */
uint8_t uart_bitLenght(rt_dev_t device)
{
    uint8_t lenght = 8;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;

    if (uarts[uart].flags.bit9 == 1)
        return 9;
    return 8;
}

/**
 * @brief Gets the uart parity mode of the specified uart device
 * @param device uart device number
 * @return parity mode
 */
uint8_t uart_bitParity(rt_dev_t device)
{
    uint8_t parity = UART_BIT_PARITY_NONE;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    return uarts[uart].flags.parity;
}

/**
 * @brief Gets number of stop bit of the specified uart device
 * @param device uart device number
 * @return number of stop bit
 */
uint8_t uart_bitStop(rt_dev_t device)
{
    uint8_t stop;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    if (uarts[uart].flags.stop == 1)
        return 2;
    return 1;
}

int uart_1_putw(uint16_t word)
{
    while (U1STAbits.UTXBF);
    U1TXREG = word;
    return 0;
}

int uart_1_putc(char c)
{
    while (U1STAbits.UTXBF);
    U1TXREG = c;
    return 0;
}
char uart_1_getc();
uint16_t uart_1_getw();

#if UART_COUNT>=2

int uart_2_putw(uint16_t word)
{
    while (U2STAbits.UTXBF);
    U2TXREG = word;
    return 0;
}

int uart_2_putc(char c)
{
    while (U2STAbits.UTXBF);
    U2TXREG = c;
    return 0;
}
uint16_t uart_2_getw(uint16_t word);
#endif

ssize_t uart_write(rt_dev_t device, const char *data, size_t size)
{
    size_t i;
    int (*uart_putc_fn)(const char);

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    switch (uart)
    {
    case 0:
        uart_putc_fn = &uart_1_putc;
        break;
#if UART_COUNT>=2
    case 1:
        uart_putc_fn = &uart_2_putc;
        break;
#endif
    }

    for (i = 0; i < size; i++)
        uart_putc_fn(data[i]);

    return size;
}

int uart_flush(rt_dev_t device)
{
    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    switch (uart)
    {
    case 0:
        while (U1STAbits.TRMT);
        break;
#if UART_COUNT>=2
    case 1:
        while (U2STAbits.TRMT);
        break;
#endif
    }

    return 0;
}

/**
 *
 * @param device
 * @return
 */
uint8_t uart_datardy(rt_dev_t device)
{
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

#if UART_COUNT>=1
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    //
    IFS0bits.U1TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    char rec[4];
    rec[0] = U1RXREG;

    fifo_push(&uarts[0].buffRx, rec, 1);

    IFS0bits.U1RXIF = 0;
}
#endif

#if UART_COUNT>=2
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{
    //
    IFS1bits.U2TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{
    char rec[4];
    rec[0] = U2RXREG;

    fifo_push(&uarts[1].buffRx, rec, 1);

    IFS1bits.U2RXIF = 0;
}
#endif
