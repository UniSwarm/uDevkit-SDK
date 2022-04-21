/**
 * @file gpio_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date June 6, 2017, 11:02 AM
 *
 * @brief GPIO support driver for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS60001120F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001120F.pdf
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

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATASET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATBSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATCSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATDSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATESET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATFSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATGSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATHSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATISET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJSET = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATKSET = bit;
            break;
#endif
    }
}

/**
 * @brief Set a bit of a GPIO to 0 (LOW)
 * @param device GPIO pin
 */
void gpio_clearBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATACLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATBCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATCCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATDCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATECLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATFCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATGCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATHCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATICLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJCLR = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATKCLR = bit;
            break;
#endif
    }
}

/**
 * @brief Toggle (invert) a bit of a GPIO from 1 to 0 or from 0 to 1
 * @param device GPIO pin
 */
void gpio_toggleBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            LATAINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            LATBINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            LATCINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            LATDINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            LATEINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            LATFINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            LATGINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            LATHINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            LATIINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            LATJINV = bit;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            LATKINV = bit;
            break;
#endif
    }
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
 * @brief Set GPIO bit configuration (input / output / open-drain / pull-up / pull-down)
 * @param device GPIO pin
 * @param config pin configuration to set (GPIO_OUTPUT / GPIO_INPUT / GPIO_OPENDRAIN
 * / GPIO_PULLUP / GPIO_PULLDOWN)
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
                TRISACLR = bit;  // set as output
            }
            else
            {
                TRISASET = bit;  // set as input
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCASET = bit;  // enable open drain
            }
            else
            {
                ODCACLR = bit;  // disable open drain
            }
#    ifdef CNPUA
            if (config & GPIO_PULLUP)
            {
                CNPUASET = bit;  // enable pull-up
            }
            else
            {
                CNPUACLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDA
            if (config & GPIO_PULLDOWN)
            {
                CNPDASET = bit;  // enable pull-down
            }
            else
            {
                CNPDACLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            if (config & GPIO_OUTPUT)
            {
                TRISBCLR = bit;  // set as output
            }
            else
            {
                TRISBSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCBSET = bit;  // enable open drain
            }
            else
            {
                ODCBCLR = bit;  // disable open drain
            }
#    ifdef CNPUB
            if (config & GPIO_PULLUP)
            {
                CNPUBSET = bit;  // enable pull-up
            }
            else
            {
                CNPUBCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDB
            if (config & GPIO_PULLDOWN)
            {
                CNPDBSET = bit;  // enable pull-down
            }
            else
            {
                CNPDBCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            if (config & GPIO_OUTPUT)
            {
                TRISCCLR = bit;  // set as output
            }
            else
            {
                TRISCSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCCSET = bit;  // enable open drain
            }
            else
            {
                ODCCCLR = bit;  // disable open drain
            }
#    ifdef CNPUC
            if (config & GPIO_PULLUP)
            {
                CNPUCSET = bit;  // enable pull-up
            }
            else
            {
                CNPUCCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDC
            if (config & GPIO_PULLDOWN)
            {
                CNPDCSET = bit;  // enable pull-down
            }
            else
            {
                CNPDCCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            if (config & GPIO_OUTPUT)
            {
                TRISDCLR = bit;  // set as output
            }
            else
            {
                TRISDSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCDSET = bit;  // enable open drain
            }
            else
            {
                ODCDCLR = bit;  // disable open drain
            }
#    ifdef CNPUD
            if (config & GPIO_PULLUP)
            {
                CNPUDSET = bit;  // enable pull-up
            }
            else
            {
                CNPUDCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDD
            if (config & GPIO_PULLDOWN)
            {
                CNPDDSET = bit;  // enable pull-down
            }
            else
            {
                CNPDDCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            if (config & GPIO_OUTPUT)
            {
                TRISECLR = bit;  // set as output
            }
            else
            {
                TRISESET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCESET = bit;  // enable open drain
            }
            else
            {
                ODCECLR = bit;  // disable open drain
            }
#    ifdef CNPUE
            if (config & GPIO_PULLUP)
            {
                CNPUESET = bit;  // enable pull-up
            }
            else
            {
                CNPUECLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDE
            if (config & GPIO_PULLDOWN)
            {
                CNPDESET = bit;  // enable pull-down
            }
            else
            {
                CNPDECLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            if (config & GPIO_OUTPUT)
            {
                TRISFCLR = bit;  // set as output
            }
            else
            {
                TRISFSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCFSET = bit;  // enable open drain
            }
            else
            {
                ODCFCLR = bit;  // disable open drain
            }
#    ifdef CNPUF
            if (config & GPIO_PULLUP)
            {
                CNPUFSET = bit;  // enable pull-up
            }
            else
            {
                CNPUFCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDF
            if (config & GPIO_PULLDOWN)
            {
                CNPDFSET = bit;  // enable pull-down
            }
            else
            {
                CNPDFCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            if (config & GPIO_OUTPUT)
            {
                TRISGCLR = bit;  // set as output
            }
            else
            {
                TRISGSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCGSET = bit;  // enable open drain
            }
            else
            {
                ODCGCLR = bit;  // disable open drain
            }
#    ifdef CNPUG
            if (config & GPIO_PULLUP)
            {
                CNPUGSET = bit;  // enable pull-up
            }
            else
            {
                CNPUGCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDG
            if (config & GPIO_PULLDOWN)
            {
                CNPDGSET = bit;  // enable pull-down
            }
            else
            {
                CNPDGCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            if (config & GPIO_OUTPUT)
            {
                TRISHCLR = bit;  // set as output
            }
            else
            {
                TRISHSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCHSET = bit;  // enable open drain
            }
            else
            {
                ODCHCLR = bit;  // disable open drain
            }
#    ifdef CNPUH
            if (config & GPIO_PULLUP)
            {
                CNPUHSET = bit;  // enable pull-up
            }
            else
            {
                CNPUHCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDH
            if (config & GPIO_PULLDOWN)
            {
                CNPDHSET = bit;  // enable pull-down
            }
            else
            {
                CNPDHCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            if (config & GPIO_OUTPUT)
            {
                TRISICLR = bit;  // set as output
            }
            else
            {
                TRISISET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCISET = bit;  // enable open drain
            }
            else
            {
                ODCICLR = bit;  // disable open drain
            }
#    ifdef CNPUI
            if (config & GPIO_PULLUP)
            {
                CNPUISET = bit;  // enable pull-up
            }
            else
            {
                CNPUICLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDI
            if (config & GPIO_PULLDOWN)
            {
                CNPDISET = bit;  // enable pull-down
            }
            else
            {
                CNPDICLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            if (config & GPIO_OUTPUT)
            {
                TRISJCLR = bit;  // set as output
            }
            else
            {
                TRISJSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCJSET = bit;  // enable open drain
            }
            else
            {
                ODCJCLR = bit;  // disable open drain
            }
#    ifdef CNPUJ
            if (config & GPIO_PULLUP)
            {
                CNPUJSET = bit;  // enable pull-up
            }
            else
            {
                CNPUJCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDJ
            if (config & GPIO_PULLDOWN)
            {
                CNPDJSET = bit;  // enable pull-down
            }
            else
            {
                CNPDJCLR = bit;  // disable pull-down
            }
#    endif
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            if (config & GPIO_OUTPUT)
            {
                TRISKCLR = bit;  // set as output
            }
            else
            {
                TRISKSET = bit;  // set as input;
            }

            if (config & GPIO_OPENDRAIN)
            {
                ODCKSET = bit;  // enable open drain
            }
            else
            {
                ODCKCLR = bit;  // disable open drain
            }
#    ifdef CNPUK
            if (config & GPIO_PULLUP)
            {
                CNPUKSET = bit;  // enable pull-up
            }
            else
            {
                CNPUKCLR = bit;  // disable pull-up
            }
#    endif
#    ifdef CNPDK
            if (config & GPIO_PULLDOWN)
            {
                CNPDKSET = bit;  // enable pull-down
            }
            else
            {
                CNPDKCLR = bit;  // disable pull-down
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
