/**
 * @file gpio_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date March 20, 2017, 18:39 AM
 *
 * @brief GPIO support driver for dsPIC30F, dsPIC33CH, dsPIC33CK, dsPIC33FJ,
 * dsPIC33EP, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70058D, DS70193D and DS70000598C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70058D.pdf (dsPIC30F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70193D.pdf (PIC24F/dsPIC33F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70000598c.pdf (PIC24E/dsPIC33E)
 */

#include "gpio.h"

#include <archi.h>

/**
 * @brief Set a bit of a GPIO to 1 (HIGH)
 * @param device GPIO pin
 */
void gpio_setBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    __builtin_disi(0x3FFF);
    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATA |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATB |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATC |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATD |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATE |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATF |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATG |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATH |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATI |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJ |= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATK |= bit;
            break;
#endif
    }
    __builtin_disi(0);
}

/**
 * @brief Set a bit of a GPIO to 0 (LOW)
 * @param device GPIO pin
 */
void gpio_clearBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = ~(1 << (device & GPIO_MAX_PORTWIDTHMASK));

    __builtin_disi(0x3FFF);
    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATA &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATB &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATC &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATD &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATE &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATF &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATG &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATH &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATI &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJ &= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATK &= bit;
            break;
#endif
    }
    __builtin_disi(0);
}

/**
 * @brief Toggle (invert) a bit of a GPIO from 1 to 0 or from 0 to 1
 * @param device GPIO pin
 */
void gpio_toggleBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    __builtin_disi(0x3FFF);
    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATA ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATB ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATC ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATD ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATE ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATF ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATG ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATH ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATI ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJ ^= bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATK ^= bit;
            break;
#endif
    }
    __builtin_disi(0);
}

/**
 * @brief Write a specific value of a bit of a GPIO
 * @param device GPIO pin
 * @param value value to set (GPIO_LOW / GPIO_HIGH / GPIO_TOGGLE)
 */
void gpio_writeBit(rt_dev_t device, GPIO_VALUE value)
{
    switch (value)
    {
        case GPIO_LOW:
            gpio_clearBit(device);
            break;

        case GPIO_HIGH:
            gpio_setBit(device);
            break;

        case GPIO_TOGGLE:
            gpio_toggleBit(device);
            break;
    }
}

/**
 * @brief Read a bit of a GPIO
 * @param device GPIO pin
 * @return current value of the bit(GPIO_LOW / GPIO_HIGH)
 */
GPIO_VALUE gpio_readBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t mbit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);
    uint16_t value = 0;

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            value = PORTA;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            value = PORTB;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            value = PORTC;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            value = PORTD;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            value = PORTE;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            value = PORTF;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            value = PORTG;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            value = PORTH;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            value = PORTI;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            value = PORTJ;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            value = PORTK;
            break;
#endif
    }

    if ((value & mbit) == 0)
    {
        return GPIO_LOW;
    }
    else
    {
        return GPIO_HIGH;
    }
}

/**
 * @brief Set GPIO bit configuration (input / output)
 * @param device GPIO pin
 * @param config pin configuration to set (GPIO_OUTPUT / GPIO_INPUT)
 * @return 0 if ok, -1 in case of error
 */
int gpio_setBitConfig(rt_dev_t device, uint16_t config)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            if (config & GPIO_OUTPUT)
            {
                TRISA &= ~bit;  // set as output
            }
            else
            {
                TRISA |= bit;  // set as input
            }

#    ifdef ODCA
            if (config & GPIO_OPENDRAIN)
            {
                ODCA |= bit;  // enable open drain
            }
            else
            {
                ODCA &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUA
            if (config & GPIO_PULLUP)
            {
                CNPUA |= bit;  // enable pull-up
            }
            else
            {
                CNPUA &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDA
            if (config & GPIO_PULLDOWN)
            {
                CNPDA |= bit;  // enable pull-down
            }
            else
            {
                CNPDA &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            if (config & GPIO_OUTPUT)
            {
                TRISB &= ~bit;  // set as output
            }
            else
            {
                TRISB |= bit;  // set as input;
            }

#    ifdef ODCB
            if (config & GPIO_OPENDRAIN)
            {
                ODCB |= bit;  // enable open drain
            }
            else
            {
                ODCB &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUB
            if (config & GPIO_PULLUP)
            {
                CNPUB |= bit;  // enable pull-up
            }
            else
            {
                CNPUB &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDB
            if (config & GPIO_PULLDOWN)
            {
                CNPDB |= bit;  // enable pull-down
            }
            else
            {
                CNPDB &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            if (config & GPIO_OUTPUT)
            {
                TRISC &= ~bit;  // set as output
            }
            else
            {
                TRISC |= bit;  // set as input;
            }

#    ifdef ODCC
            if (config & GPIO_OPENDRAIN)
            {
                ODCC |= bit;  // enable open drain
            }
            else
            {
                ODCC &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUC
            if (config & GPIO_PULLUP)
            {
                CNPUC |= bit;  // enable pull-up
            }
            else
            {
                CNPUC &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDC
            if (config & GPIO_PULLDOWN)
            {
                CNPDC |= bit;  // enable pull-down
            }
            else
            {
                CNPDC &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            if (config & GPIO_OUTPUT)
            {
                TRISD &= ~bit;  // set as output
            }
            else
            {
                TRISD |= bit;  // set as input;
            }

#    ifdef ODCD
            if (config & GPIO_OPENDRAIN)
            {
                ODCD |= bit;  // enable open drain
            }
            else
            {
                ODCD &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUD
            if (config & GPIO_PULLUP)
            {
                CNPUD |= bit;  // enable pull-up
            }
            else
            {
                CNPUD &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDD
            if (config & GPIO_PULLDOWN)
            {
                CNPDD |= bit;  // enable pull-down
            }
            else
            {
                CNPDD &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            if (config & GPIO_OUTPUT)
            {
                TRISE &= ~bit;  // set as output
            }
            else
            {
                TRISE |= bit;  // set as input;
            }

#    ifdef ODCE
            if (config & GPIO_OPENDRAIN)
            {
                ODCE |= bit;  // enable open drain
            }
            else
            {
                ODCE &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUE
            if (config & GPIO_PULLUP)
            {
                CNPUE |= bit;  // enable pull-up
            }
            else
            {
                CNPUE &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDE
            if (config & GPIO_PULLDOWN)
            {
                CNPDE |= bit;  // enable pull-down
            }
            else
            {
                CNPDE &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            if (config & GPIO_OUTPUT)
            {
                TRISF &= ~bit;  // set as output
            }
            else
            {
                TRISF |= bit;  // set as input;
            }

#    ifdef ODCF
            if (config & GPIO_OPENDRAIN)
            {
                ODCF |= bit;  // enable open drain
            }
            else
            {
                ODCF &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUF
            if (config & GPIO_PULLUP)
            {
                CNPUF |= bit;  // enable pull-up
            }
            else
            {
                CNPUF &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDF
            if (config & GPIO_PULLDOWN)
            {
                CNPDF |= bit;  // enable pull-down
            }
            else
            {
                CNPDF &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            if (config & GPIO_OUTPUT)
            {
                TRISG &= ~bit;  // set as output
            }
            else
            {
                TRISG |= bit;  // set as input;
            }

#    ifdef ODCG
            if (config & GPIO_OPENDRAIN)
            {
                ODCG |= bit;  // enable open drain
            }
            else
            {
                ODCG &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUG
            if (config & GPIO_PULLUP)
            {
                CNPUG |= bit;  // enable pull-up
            }
            else
            {
                CNPUG &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDG
            if (config & GPIO_PULLDOWN)
            {
                CNPDG |= bit;  // enable pull-down
            }
            else
            {
                CNPDG &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            if (config & GPIO_OUTPUT)
            {
                TRISH &= ~bit;  // set as output
            }
            else
            {
                TRISH |= bit;  // set as input;
            }

#    ifdef ODCH
            if (config & GPIO_OPENDRAIN)
            {
                ODCH |= bit;  // enable open drain
            }
            else
            {
                ODCH &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUH
            if (config & GPIO_PULLUP)
            {
                CNPUH |= bit;  // enable pull-up
            }
            else
            {
                CNPUH &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDH
            if (config & GPIO_PULLDOWN)
            {
                CNPDH |= bit;  // enable pull-down
            }
            else
            {
                CNPDH &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            if (config & GPIO_OUTPUT)
            {
                TRISI &= ~bit;  // set as output
            }
            else
            {
                TRISI |= bit;  // set as input;
            }

#    ifdef ODCI
            if (config & GPIO_OPENDRAIN)
            {
                ODCI |= bit;  // enable open drain
            }
            else
            {
                ODCI &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUI
            if (config & GPIO_PULLUP)
            {
                CNPUI |= bit;  // enable pull-up
            }
            else
            {
                CNPUI &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDI
            if (config & GPIO_PULLDOWN)
            {
                CNPDI |= bit;  // enable pull-down
            }
            else
            {
                CNPDI &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            if (config & GPIO_OUTPUT)
            {
                TRISJ &= ~bit;  // set as output
            }
            else
            {
                TRISJ |= bit;  // set as input;
            }

#    ifdef ODCJ
            if (config & GPIO_OPENDRAIN)
            {
                ODCJ |= bit;  // enable open drain
            }
            else
            {
                ODCJ &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUJ
            if (config & GPIO_PULLUP)
            {
                CNPUJ |= bit;  // enable pull-up
            }
            else
            {
                CNPUJ &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDJ
            if (config & GPIO_PULLDOWN)
            {
                CNPDJ |= bit;  // enable pull-down
            }
            else
            {
                CNPDJ &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            if (config & GPIO_OUTPUT)
            {
                TRISK &= ~bit;  // set as output
            }
            else
            {
                TRISK |= bit;  // set as input;
            }

#    ifdef ODCK
            if (config & GPIO_OPENDRAIN)
            {
                ODCK |= bit;  // enable open drain
            }
            else
            {
                ODCK &= ~bit;  // disable open drain
            }
#    endif
#    ifdef CNPUK
            if (config & GPIO_PULLUP)
            {
                CNPUK |= bit;  // enable pull-up
            }
            else
            {
                CNPUK &= ~bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDK
            if (config & GPIO_PULLDOWN)
            {
                CNPDK |= bit;  // enable pull-down
            }
            else
            {
                CNPDK &= ~bit;  // disable pull-down
            }
#    endif
            break;
#endif
        default:
            return -1;
    }

    return 0;
}

/**
 * @brief Set GPIO port value (complete port)
 * @param device GPIO port
 * @param value to set
 */
void gpio_writePort(rt_dev_t device, port_type value)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATA = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATB = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATC = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATD = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATE = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATF = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATG = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATH = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATI = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJ = value;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATK = value;
            break;
#endif
    }
}

/**
 * @brief Read GPIO port value (complete port)
 * @param device GPIO port
 * @return current value of port
 */
port_type gpio_readPort(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            return PORTA;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            return PORTB;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            return PORTC;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            return PORTD;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            return PORTE;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            return PORTF;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            return PORTG;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            return PORTH;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            return PORTI;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            return PORTJ;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            return PORTK;
#endif
    }

    return 0;
}

/**
 * @brief Set GPIO port configuration (input / output)
 * @param device GPIO port
 * @param config port configuration to set (GPIO_OUTPUT / GPIO_INPUT)
 * @return 0 if ok, -1 in case of error
 */
int gpio_setPortConfig(rt_dev_t device, uint16_t config)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    uint16_t trisValue;
    if (config & GPIO_OUTPUT)
    {
        trisValue = 0x0000;
    }
    else
    {
        trisValue = 0xFFFF;
    }

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            TRISA = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            TRISB = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            TRISC = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            TRISD = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            TRISE = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            TRISF = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            TRISG = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            TRISH = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            TRISI = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            TRISJ = trisValue;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            TRISK = trisValue;
            break;
#endif
        default:
            return -1;
    }

    return 0;
}
