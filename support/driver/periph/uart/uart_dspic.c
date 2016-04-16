/**
 * @file uart_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM
 *
 * @brief Uart support for rtprog
 */

#include "uart_dspic.h"

#include "driver/sysclock.h"

#if !defined (UART_COUNT) || UART_COUNT==0
//#error No device
#endif

uint32_t baudSpeed[UART_COUNT] = {0};

/**
 * @brief Enable the specified uart device
 * @param device uart device number
 * @return 0 if ok, -1 in case of error
 */
int uart_enable(uint8_t device)
{
    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        U1MODEbits.UARTEN = 1;
        break;
#if UART_COUNT>=2
    case 2:
        U2MODEbits.UARTEN = 1;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        U3MODEbits.UARTEN = 1;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        U4MODEbits.UARTEN = 1;
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
int uart_disable(uint8_t device)
{
    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        U1MODEbits.UARTEN = 0;
        break;
#if UART_COUNT>=2
    case 2:
        U2MODEbits.UARTEN = 0;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        U3MODEbits.UARTEN = 0;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        U4MODEbits.UARTEN = 0;
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
int uart_setBaudSpeed(uint8_t device, uint32_t baudSpeed)
{
    uint32_t systemClockPeriph;
    uint16_t uBrg;
    uint8_t hs = 0;

    if (device > UART_COUNT)
        return -1;

    systemClockPeriph = getSystemClockPeriph();
    uBrg = systemClockPeriph / baudSpeed;

    if ((uBrg & 0x0F) == 0)
    {
        hs = 0;
        uBrg >> 4;
    }
    else
    {
        hs = 1;
        uBrg >> 2;
    }

    switch (device)
    {
    case 1:
        U1MODEbits.BRGH = hs;
        U1BRG = uBrg - 1;
        break;
#if UART_COUNT>=2
    case 2:
        U2MODEbits.BRGH = hs;
        U2BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        U3MODEbits.BRGH = hs;
        U3BRG = uBrg - 1;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        U4MODEbits.BRGH = hs;
        U4BRG = uBrg - 1;
        break;
#endif
    }

    return 0;
}

/**
 * @brief Gets the true baud speed of the specified uart device
 * @param device uart device number
 * @return
 */
uint32_t uart_baudSpeed(uint8_t device)
{
    uint32_t baudSpeed;
    uint16_t uBrg;
    uint8_t hs;

    if (device > UART_COUNT)
        return 0;

    switch (device)
    {
    case 1:
        hs = U1MODEbits.BRGH;
        uBrg = U1BRG + 1;
        break;
#if UART_COUNT>=2
    case 2:
        hs = U1MODEbits.BRGH;
        uBrg = U1BRG + 1;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        hs = U1MODEbits.BRGH;
        uBrg = U1BRG + 1;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        hs = U1MODEbits.BRGH;
        uBrg = U1BRG + 1;
        break;
#endif
    }

    baudSpeed = getSystemClockPeriph() / uBrg;
    if (hs == 1)
        baudSpeed >> 2;
    else
        baudSpeed >> 4;

    return baudSpeed;
}

/**
 * @brief Gets the effective baud speed of the specified uart device
 * @param device uart device number
 * @return
 */
uint32_t uart_effectiveBaudSpeed(uint8_t device)
{
    if (device > UART_COUNT)
        return 0;

    return baudSpeed[device];
}

/**
 * @brief
 * @param device uart device number
 * @param bitLenght
 * @param bitParity
 * @param bitStop
 * @return 0 if ok, -1 in case of error
 */
int uart_setBitConfig(uint8_t device, uint8_t bitLenght,
                      uint8_t bitParity, uint8_t bitStop)
{
    uint8_t bit = 0, stop = 0;

    if (device > UART_COUNT)
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

    switch (device)
    {
    case 1:
        U1MODEbits.STSEL = stop;
        U1MODEbits.PDSEL = bit;
        break;
#if UART_COUNT>=2
    case 2:
        U2MODEbits.STSEL = stop;
        U2MODEbits.PDSEL = bit;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        U3MODEbits.STSEL = stop;
        U3MODEbits.PDSEL = bit;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        U4MODEbits.STSEL = stop;
        U4MODEbits.PDSEL = bit;
        break;
#endif
    }
}

/**
 * @brief
 * @param device uart device number
 * @return
 */
uint8_t uart_bitLenght(uint8_t device)
{
    uint8_t lenght = 8;

    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        if (U1MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#if UART_COUNT>=2
    case 2:
        if (U2MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        if (U3MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        if (U4MODEbits.PDSEL == 0b11)
            lenght = 9;
        break;
#endif
    }

    return lenght;
}

/**
 * @brief
 * @param device uart device number
 * @return
 */
uint8_t uart_bitParity(uint8_t device)
{
    uint8_t parity = UART_BIT_PARITY_NONE;

    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        if (U1MODEbits.PDSEL != 0b11)
            parity = U1MODEbits.PDSEL;
        break;
#if UART_COUNT>=2
    case 2:
        if (U1MODEbits.PDSEL != 0b11)
            parity = U1MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        if (U1MODEbits.PDSEL != 0b11)
            parity = U1MODEbits.PDSEL;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        if (U1MODEbits.PDSEL != 0b11)
            parity = U1MODEbits.PDSEL;
        break;
#endif
    }

    return parity;
}

/**
 * @brief
 * @param device uart device number
 * @return
 */
uint8_t uart_bitStop(uint8_t device)
{
    uint8_t stop;

    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        stop = U1MODEbits.STSEL;
        break;
#if UART_COUNT>=2
    case 2:
        stop = U2MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=3
    case 3:
        stop = U3MODEbits.STSEL;
        break;
#endif
#if UART_COUNT>=4
    case 4:
        stop = U4MODEbits.STSEL;
        break;
#endif
    }

    return stop << 1;
}

int uart_1_putw(uint16_t word)
{
    while (U1STAbits.UTXBF);
    U1TXREG = word;
}

int uart_1_putc(char c)
{
    while (U1STAbits.UTXBF);
    U1TXREG = c;
}
char uart_1_getc();
uint16_t uart_1_getw();

#if UART_COUNT>=2

int uart_2_putw(uint16_t word)
{
    while (U2STAbits.UTXBF);
    U2TXREG = word;
}

int uart_2_putc(char c)
{
    while (U2STAbits.UTXBF);
    U2TXREG = c;
}
uint16_t uart_2_getw(uint16_t word);
#endif

#if UART_COUNT>=3

int uart_3_putw(uint16_t word)
{
    while (U3STAbits.UTXBF);
    U3TXREG = word;
}

int uart_3_putc(char c)
{
    while (U3STAbits.UTXBF);
    U3TXREG = c;
}
uint16_t uart_3_getw(uint16_t word);
#endif

#if UART_COUNT>=4

int uart_4_putw(uint16_t word)
{
    while (U4STAbits.UTXBF);
    U4TXREG = word;
}

int uart_4_putc(char c)
{
    while (U4STAbits.UTXBF);
    U4TXREG = c;
}
uint16_t uart_4_getw(uint16_t word);
#endif

/**
 * @brief
 * @param device uart device number
 * @param c
 * @return
 */
int uart_putc(uint8_t device, const char c)
{
    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        uart_1_putc(c);
        break;
#if UART_COUNT>=2
    case 2:
        uart_2_putc(c);
        break;
#endif
#if UART_COUNT>=3
    case 3:
        uart_3_putc(c);
        break;
#endif
#if UART_COUNT>=4
    case 4:
        uart_4_putc(c);
        break;
#endif
    }

    return 0;
}

/**
 * @brief
 * @param device uart device number
 * @param word
 * @return
 */
int uart_putw(uint8_t device, const uint16_t word)
{
    if (device > UART_COUNT)
        return -1;

    switch (device)
    {
    case 1:
        uart_1_putw(word);
        break;
#if UART_COUNT>=2
    case 2:
        uart_2_putw(word);
        break;
#endif
#if UART_COUNT>=3
    case 3:
        uart_3_putw(word);
        break;
#endif
#if UART_COUNT>=4
    case 4:
        uart_4_putw(word);
        break;
#endif
    }

    return 0;
}

/**
 * @brief
 * @param device
 * @return
 */
char uart_getc(uint8_t device);

/**
 * @brief
 * @param device uart device number
 * @return
 */
uint16_t uart_getw(uint8_t device)
{

}

/**
 *
 * @param device
 * @return
 */
uint8_t uart_datardy(uint8_t device)
{

}