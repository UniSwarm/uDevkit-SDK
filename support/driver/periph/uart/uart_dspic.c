/**
 * @file uart_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart support for rtprog
 */

#include "uart.h"

#include "driver/sysclock.h"
#include "sys/fifo.h"

#include <xc.h>

#if !defined (UART_COUNT) || UART_COUNT==0
  #warning "No uart on the current device or unknow device"
#endif

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
#if UART_COUNT>=5
    {.baudSpeed=0},
#endif
#if UART_COUNT>=6
    {.baudSpeed=0},
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

    uarts[i].baudSpeed = 1;
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

    uarts[uart].baudSpeed = 0;
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

    switch (uart)
    {
    case 0:
        IPC2bits.U1RXIP = 6;    // interrupt priority for receptor
        IFS0bits.U1RXIF = 0;    // clear receive Flag
        IEC0bits.U1RXIE = 1;    // enable receive interrupt

        IPC3bits.U1TXIP = 5;    // interrupt priority for transmitor
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
        IPC7bits.U2RXIP = 6;    // interrupt priority for receptor
        IFS1bits.U2RXIF = 0;    // clear receive Flag
        IEC1bits.U2RXIE = 1;    // enable receive interrupt

        IPC7bits.U2TXIP = 5;    // interrupt priority for transmitor
        IFS1bits.U2TXIF = 0;    // clear transmit Flag
        IEC1bits.U2TXIE = 0;    // disable transmit interrupt

        U2MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U2STAbits.URXEN = 1;    // enable receiver
    #endif
        U2STAbits.UTXEN = 1;    // enable transmiter
        break;
#endif
#if UART_COUNT>=3
    case 2:
        IPC20bits.U3RXIP = 6;   // interrupt priority for receptor
        IFS5bits.U3RXIF = 0;    // clear receive Flag
        IEC5bits.U3RXIE = 1;    // enable receive interrupt

        IPC20bits.U3TXIP = 5;   // interrupt priority for transmitor
        IFS5bits.U3TXIF = 0;    // clear transmit Flag
        IEC5bits.U3TXIE = 0;    // disable transmit interrupt

        U3MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U3STAbits.URXEN = 1;    // enable receiver
    #endif
        U3STAbits.UTXEN = 1;    // enable transmiter
        break;
#endif
#if UART_COUNT>=4
    case 3:
        IPC22bits.U4RXIP = 6;   // interrupt priority for receptor
        IFS5bits.U4RXIF = 0;    // clear receive Flag
        IEC5bits.U4RXIE = 1;    // enable receive interrupt

        IPC22bits.U4TXIP = 5;   // interrupt priority for transmitor
        IFS5bits.U4TXIF = 0;    // clear transmit Flag
        IEC5bits.U4TXIE = 0;    // disable transmit interrupt

        U4MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U4STAbits.URXEN = 1;    // enable receiver
    #endif
        U4STAbits.UTXEN = 1;    // enable transmiter
        break;
#endif
#if UART_COUNT>=5
    case 4:
        IPC27bits.U5RXIP = 6;   // interrupt priority for receptor
        IFS6bits.U5RXIF = 0;    // clear receive Flag
        IEC6bits.U5RXIE = 1;    // enable receive interrupt

        IPC28bits.U5TXIP = 5;   // interrupt priority for transmitor
        IFS7bits.U5TXIF = 0;    // clear transmit Flag
        IEC7bits.U5TXIE = 0;    // disable transmit interrupt

        U5MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U5STAbits.URXEN = 1;    // enable receiver
    #endif
        U5STAbits.UTXEN = 1;    // enable transmiter
        break;
#endif
#if UART_COUNT>=6
    case 5:
        IPC28bits.U6RXIP = 6;   // interrupt priority for receptor
        IFS7bits.U6RXIF = 0;    // clear receive Flag
        IEC7bits.U6RXIE = 1;    // enable receive interrupt

        IPC28bits.U6TXIP = 5;   // interrupt priority for transmitor
        IFS7bits.U6TXIF = 0;    // clear transmit Flag
        IEC7bits.U6TXIE = 0;    // disable transmit interrupt

        U6MODEbits.UARTEN = 1;  // enable uart module
    #ifdef UART_RXEN
        U6STAbits.URXEN = 1;    // enable receiver
    #endif
        U6STAbits.UTXEN = 1;    // enable transmiter
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
#if UART_COUNT>=3
    case 2:
        IEC5bits.U3RXIE = 0;    // disable receive interrupt
        IEC5bits.U3TXIE = 0;    // disable transmit interrupt
        U3MODEbits.UARTEN = 0;  // disable uart
        break;
#endif
#if UART_COUNT>=4
    case 3:
        IEC5bits.U4RXIE = 0;    // disable receive interrupt
        IEC5bits.U4TXIE = 0;    // disable transmit interrupt
        U4MODEbits.UARTEN = 0;  // disable uart
        break;
#endif
#if UART_COUNT>=5
    case 4:
        IEC6bits.U5RXIE = 0;    // disable receive interrupt
        IEC7bits.U5TXIE = 0;    // disable transmit interrupt
        U5MODEbits.UARTEN = 0;  // disable uart
        break;
#endif
#if UART_COUNT>=6
    case 5:
        IEC7bits.U6RXIE = 0;    // disable receive interrupt
        IEC7bits.U6TXIE = 0;    // disable transmit interrupt
        U6MODEbits.UARTEN = 0;  // disable uart
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
    uint8_t hs = 0;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    if (baudSpeed == 0)
        return -1;

    uarts[uart].baudSpeed = baudSpeed;

    systemClockPeriph = getSystemClockPeriph();
    uBrg = systemClockPeriph / baudSpeed;

    if ((uBrg & 0x0F) == 0)
    {
        hs = 0;
        uBrg = uBrg >> 4;
    }
    else
    {
        hs = 1;
        uBrg = uBrg >> 2;
    }

    switch (uart)
    {
    case 0:
        U1MODEbits.BRGH = hs;
        U1BRG = uBrg - 1;
        break;
#if UART_COUNT>=2
    case 1:
        U2MODEbits.BRGH = hs;
        U2BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=3
    case 2:
        U3MODEbits.BRGH = hs;
        U3BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        U4MODEbits.BRGH = hs;
        U4BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        U5MODEbits.BRGH = hs;
        U5BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        U6MODEbits.BRGH = hs;
        U6BRG = uBrg - 1;
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
    uint8_t hs;

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return 0;

    switch (uart)
    {
    case 0:
        hs = U1MODEbits.BRGH;
        uBrg = U1BRG + 1;
        break;
#if UART_COUNT>=2
    case 1:
        hs = U2MODEbits.BRGH;
        uBrg = U2BRG + 1;
        break;
#endif
#if UART_COUNT>=3
    case 2:
        hs = U3MODEbits.BRGH;
        uBrg = U3BRG + 1;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        hs = U4MODEbits.BRGH;
        uBrg = U4BRG + 1;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        hs = U5MODEbits.BRGH;
        uBrg = U5BRG + 1;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        hs = U6MODEbits.BRGH;
        uBrg = U6BRG + 1;
        break;
#endif
    }

    baudSpeed = getSystemClockPeriph() / uBrg;
    if (hs == 1)
        baudSpeed = baudSpeed >> 2;
    else
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

    uint8_t uart = MINOR(device);
    if (uart >= UART_COUNT)
        return -1;

    if (bitLenght == 9)
        bit = 0b11;
    else
    {
        if (bitParity != UART_BIT_PARITY_NONE)
            bit = bitParity;
    }

    if (bitStop == 2)
        stop = 1;

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
#if UART_COUNT>=3
    case 2:
        U3MODEbits.STSEL = stop;
        U3MODEbits.PDSEL = bit;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        U4MODEbits.STSEL = stop;
        U4MODEbits.PDSEL = bit;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        U5MODEbits.STSEL = stop;
        U5MODEbits.PDSEL = bit;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        U6MODEbits.STSEL = stop;
        U6MODEbits.PDSEL = bit;
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
        return -1;

    switch (uart)
    {
    case 0:
        if (U1MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#if UART_COUNT>=2
    case 1:
        if (U2MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=3
    case 2:
        if (U3MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        if (U4MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        if (U5MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        if (U6MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
    }

    return lenght;
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

    switch (uart)
    {
    case 0:
        if (U1MODEbits.PDSEL != 0b11)
            parity = U1MODEbits.PDSEL;
        break;
#if UART_COUNT>=2
    case 1:
        if (U2MODEbits.PDSEL != 0b11)
            parity = U2MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=3
    case 2:
        if (U3MODEbits.PDSEL != 0b11)
            parity = U3MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        if (U4MODEbits.PDSEL != 0b11)
            parity = U4MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        if (U5MODEbits.PDSEL != 0b11)
            parity = U5MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        if (U6MODEbits.PDSEL != 0b11)
            parity = U6MODEbits.PDSEL;
        break;
#endif
    }

    return parity;
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

    switch (uart)
    {
    case 0:
        stop = U1MODEbits.STSEL;
        break;
#if UART_COUNT>=2
    case 1:
        stop = U2MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=3
    case 2:
        stop = U3MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        stop = U4MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        stop = U5MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        stop = U6MODEbits.STSEL;
        break;
#endif
    }

    return stop << 1;
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

#if UART_COUNT>=3

int uart_3_putw(uint16_t word)
{
    while (U3STAbits.UTXBF);
    U3TXREG = word;
    return 0;
}

int uart_3_putc(char c)
{
    while (U3STAbits.UTXBF);
    U3TXREG = c;
    return 0;
}
uint16_t uart_3_getw(uint16_t word);
#endif

#if UART_COUNT>=4

int uart_4_putw(uint16_t word)
{
    while (U4STAbits.UTXBF);
    U4TXREG = word;
    return 0;
}

int uart_4_putc(char c)
{
    while (U4STAbits.UTXBF);
    U4TXREG = c;
    return 0;
}
uint16_t uart_4_getw(uint16_t word);
#endif

#if UART_COUNT>=5

int uart_5_putw(uint16_t word)
{
    while (U5STAbits.UTXBF);
    U5TXREG = word;
    return 0;
}

int uart_5_putc(char c)
{
    while (U5STAbits.UTXBF);
    U5TXREG = c;
    return 0;
}
uint16_t uart_5_getw(uint16_t word);
#endif

#if UART_COUNT>=6

int uart_6_putw(uint16_t word)
{
    while (U6STAbits.UTXBF);
    U6TXREG = word;
    return 0;
}

int uart_6_putc(char c)
{
    while (U6STAbits.UTXBF);
    U6TXREG = c;
    return 0;
}
uint16_t uart_6_getw(uint16_t word);
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
#if UART_COUNT>=3
    case 2:
        uart_putc_fn = &uart_3_putc;
        break;
#endif
#if UART_COUNT>=4
    case 3:
        uart_putc_fn = &uart_4_putc;
        break;
#endif
#if UART_COUNT>=5
    case 4:
        uart_putc_fn = &uart_5_putc;
        break;
#endif
#if UART_COUNT>=6
    case 5:
        uart_putc_fn = &uart_6_putc;
        break;
#endif
    }

    for (i = 0; i < size; i++)
    {
        uart_putc_fn(data[i]);
    }

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
#if UART_COUNT>=3
    case 2:
        while (U3STAbits.TRMT);
        break;
#endif
#if UART_COUNT>=4
    case 3:
        while (U4STAbits.TRMT);
        break;
#endif
#if UART_COUNT>=5
    case 4:
        while (U5STAbits.TRMT);
        break;
#endif
#if UART_COUNT>=6
    case 5:
        while (U6STAbits.TRMT);
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

#if UART_COUNT>=3
void __attribute__((interrupt, no_auto_psv)) _U3TXInterrupt(void)
{
    //
    IFS5bits.U3TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void)
{
    char rec[4];
    rec[0] = U3RXREG;

    fifo_push(&uarts[2].buffRx, rec, 1);

    IFS5bits.U3RXIF = 0;
}
#endif

#if UART_COUNT>=4
void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt(void)
{
    //
    IFS5bits.U4TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt(void)
{
    char rec[4];
    rec[0] = U4RXREG;

    fifo_push(&uarts[3].buffRx, rec, 1);

    IFS5bits.U4RXIF = 0;
}
#endif

#if UART_COUNT>=5
void __attribute__((interrupt, no_auto_psv)) _U5TXInterrupt(void)
{
    //
    IFS7bits.U5TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U5RXInterrupt(void)
{
    char rec[4];
    rec[0] = U5RXREG;

    fifo_push(&uarts[4].buffRx, rec, 1);

    IFS6bits.U5RXIF = 0;
}
#endif

#if UART_COUNT>=6
void __attribute__((interrupt, no_auto_psv)) _U6TXInterrupt(void)
{
    //
    IFS7bits.U6TXIF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U6RXInterrupt(void)
{
    char rec[4];
    rec[0] = U6RXREG;

    fifo_push(&uarts[5].buffRx, rec, 1);

    IFS7bits.U6RXIF = 0;
}
#endif
