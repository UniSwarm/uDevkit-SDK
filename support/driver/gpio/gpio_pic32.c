/**
 * @file gpio_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
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
#include <driver/int.h>

struct gpio_dev
{
    void (*handler)(uint32_t);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#ifndef INT_MODE
#    define INT_MODE INT_DEFAULT_MODE
#endif
#ifndef GPIO_INTERRUPT_PRIORITY
#    define GPIO_INTERRUPT_PRIORITY 5
#endif
#ifndef GPIOA_INT_PRIORITY
#    define GPIOA_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOB_INT_PRIORITY
#    define GPIOB_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOC_INT_PRIORITY
#    define GPIOC_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOD_INT_PRIORITY
#    define GPIOD_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOE_INT_PRIORITY
#    define GPIOE_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOF_INT_PRIORITY
#    define GPIOF_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOG_INT_PRIORITY
#    define GPIOG_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOH_INT_PRIORITY
#    define GPIOH_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOI_INT_PRIORITY
#    define GPIOI_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOJ_INT_PRIORITY
#    define GPIOJ_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif
#ifndef GPIOK_INT_PRIORITY
#    define GPIOK_INT_PRIORITY GPIO_INTERRUPT_PRIORITY
#endif

static struct gpio_dev _gpios[] = {
#if GPIO_PORT_MAX >= 1
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 2
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 3
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 4
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 5
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 6
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 7
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 8
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 9
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 10
    {.handler = NULL},
#endif
#if GPIO_PORT_MAX >= 11
    {.handler = NULL},
#endif
};

#if defined(GPIO_HAVE_PORTA) && !defined(GPIOA_DISABLE)
void CNAInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTB) && !defined(GPIOB_DISABLE)
void CNBInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTC) && !defined(GPIOC_DISABLE)
void CNCInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTD) && !defined(GPIOD_DISABLE)
void CNDInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTE) && !defined(GPIOE_DISABLE)
void CNEInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTF) && !defined(GPIOF_DISABLE)
void CNFInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTG) && !defined(GPIOG_DISABLE)
void CNGInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTH) && !defined(GPIOH_DISABLE)
void CNHInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTI) && !defined(GPIOI_DISABLE)
void CNIInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTJ) && !defined(GPIOJ_DISABLE)
void CNJInterrupt(void);
#endif
#if defined(GPIO_HAVE_PORTK) && !defined(GPIOK_DISABLE)
void CNKInterrupt(void);
#endif

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

    return GPIO_HIGH;
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
#    ifdef CNENA
            if (config & GPIO_CNPOSITIVE)
            {
                CNENASET = bit;  // enable positive edge detection
            }
            else
            {
                CNENACLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEA
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEASET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEACLR = bit;  // disable negative edge detection
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
#    ifdef CNENB
            if (config & GPIO_CNPOSITIVE)
            {
                CNENBSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENBCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEB
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEBSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEBCLR = bit;  // disable negative edge detection
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
#    ifdef CNENC
            if (config & GPIO_CNPOSITIVE)
            {
                CNENCSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENCCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEC
            if (config & GPIO_CNNEGATIVE)
            {
                CNNECSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNECCLR = bit;  // disable negative edge detection
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
#    ifdef CNEND
            if (config & GPIO_CNPOSITIVE)
            {
                CNENDSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENDCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNED
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEDSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEDCLR = bit;  // disable negative edge detection
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
#    ifdef CNENE
            if (config & GPIO_CNPOSITIVE)
            {
                CNENESET = bit;  // enable positive edge detection
            }
            else
            {
                CNENECLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEE
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEESET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEECLR = bit;  // disable negative edge detection
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
#    ifdef CNENF
            if (config & GPIO_CNPOSITIVE)
            {
                CNENFSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENFCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEF
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEFSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEFCLR = bit;  // disable negative edge detection
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
#    ifdef CNENG
            if (config & GPIO_CNPOSITIVE)
            {
                CNENGSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENGCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEG
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEGSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEGCLR = bit;  // disable negative edge detection
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
#    ifdef CNENH
            if (config & GPIO_CNPOSITIVE)
            {
                CNENHSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENHCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEH
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEHSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEHCLR = bit;  // disable negative edge detection
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
#    ifdef CNENI
            if (config & GPIO_CNPOSITIVE)
            {
                CNENISET = bit;  // enable positive edge detection
            }
            else
            {
                CNENICLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEI
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEISET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEICLR = bit;  // disable negative edge detection
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
#    ifdef CNENJ
            if (config & GPIO_CNPOSITIVE)
            {
                CNENJSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENJCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEJ
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEJSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEJCLR = bit;  // disable negative edge detection
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
#    ifdef CNENK
            if (config & GPIO_CNPOSITIVE)
            {
                CNENKSET = bit;  // enable positive edge detection
            }
            else
            {
                CNENKCLR = bit;  // disable positive edge detection
            }
#    endif
#    ifdef CNNEK
            if (config & GPIO_CNNEGATIVE)
            {
                CNNEKSET = bit;  // enable negative edge detection
            }
            else
            {
                CNNEKCLR = bit;  // disable negative edge detection
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

int gpio_setChangeHandler(rt_dev_t device, void (*handler)(GPIO_VALUE))
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    _gpios[port].handler = handler;

    int on = 0;
    if (handler != NULL)
    {
        on = 1;
    }

    switch (port)
    {
#ifdef GPIO_HAVE_PORTA
        case 0:
            CNCONAbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONAbits.EDGEDETECT = 1;
            CNFA = 0;
#    endif
            _CNAIF = 0;
            _CNAIP = GPIOA_INT_PRIORITY;
            _CNAIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTB
        case 1:
            CNCONBbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONBbits.EDGEDETECT = 1;
            CNFB = 0;
#    endif
            _CNBIF = 0;
            _CNBIP = GPIOB_INT_PRIORITY;
            _CNBIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTC
        case 2:
            CNCONCbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONCbits.EDGEDETECT = 1;
            CNFC = 0;
#    endif
            _CNCIF = 0;
            _CNCIP = GPIOC_INT_PRIORITY;
            _CNCIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTD
        case 3:
            CNCONDbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONDbits.EDGEDETECT = 1;
            CNFD = 0;
#    endif
            _CNDIF = 0;
            _CNDIP = GPIOD_INT_PRIORITY;
            _CNDIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTE
        case 4:
            CNCONEbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONEbits.EDGEDETECT = 1;
            CNFE = 0;
#    endif
            _CNEIF = 0;
            _CNEIP = GPIOE_INT_PRIORITY;
            _CNEIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTF
        case 5:
            CNCONFbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONFbits.EDGEDETECT = 1;
            CNFF = 0;
#    endif
            _CNFIF = 0;
            _CNFIP = GPIOF_INT_PRIORITY;
            _CNFIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTG
        case 6:
            CNCONGbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONGbits.EDGEDETECT = 1;
            CNFG = 0;
#    endif
            _CNGIF = 0;
            _CNGIP = GPIOG_INT_PRIORITY;
            _CNGIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTH
        case 7:
            CNCONHbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONHbits.EDGEDETECT = 1;
            CNFH = 0;
#    endif
            _CNHIF = 0;
            _CNHIP = GPIOH_INT_PRIORITY;
            _CNHIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTI
        case 8:
            CNCONIbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONIbits.EDGEDETECT = 1;
            CNFI = 0;
#    endif
            _CNIIF = 0;
            _CNIIP = GPIOI_INT_PRIORITY;
            _CNIIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTJ
        case 9:
            CNCONJbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONJbits.EDGEDETECT = 1;
            CNFJ = 0;
#    endif
            _CNJIF = 0;
            _CNJIP = GPIOJ_INT_PRIORITY;
            _CNJIE = on;
            break;
#endif
#ifdef GPIO_HAVE_PORTK
        case 10:
            CNCONKbits.ON = on;
#    ifndef GPIO_CN_NOEDGEDETECT
            CNCONKbits.EDGEDETECT = 1;
            CNFK = 0;
#    endif
            _CNKIF = 0;
            _CNKIP = GPIOK_INT_PRIORITY;
            _CNKIE = on;
            break;
#endif
        default:
            return -1;
    }
    return 0;
}

#if defined(GPIO_HAVE_PORTA) && !defined(GPIOA_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_A_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNAInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATA;
#    else
    uint32_t change_mask = CNFA;
#    endif

    if (_gpios[GPIO_PORTA].handler != NULL)
    {
        (*_gpios[GPIO_PORTA].handler)(change_mask);
    }

    PORTA;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFA = 0;
#    endif
    _CNAIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTB) && !defined(GPIOB_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_B_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNBInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATB;
#    else
    uint32_t change_mask = CNFB;
#    endif

    if (_gpios[GPIO_PORTB].handler != NULL)
    {
        (*_gpios[GPIO_PORTB].handler)(change_mask);
    }

    PORTB;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFB = 0;
#    endif
    _CNBIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTC) && !defined(GPIOC_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_C_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNCInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATC;
#    else
    uint32_t change_mask = CNFC;
#    endif

    if (_gpios[GPIO_PORTC].handler != NULL)
    {
        (*_gpios[GPIO_PORTC].handler)(change_mask);
    }

    PORTC;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFC = 0;
#    endif
    _CNCIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTD) && !defined(GPIOD_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_D_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNDInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATD;
#    else
    uint32_t change_mask = CNFD;
#    endif

    if (_gpios[GPIO_PORTD].handler != NULL)
    {
        (*_gpios[GPIO_PORTD].handler)(change_mask);
    }

    PORTD;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFD = 0;
#    endif
    _CNDIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTE) && !defined(GPIOE_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_E_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNEInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATE;
#    else
    uint32_t change_mask = CNFE;
#    endif

    if (_gpios[GPIO_PORTE].handler != NULL)
    {
        (*_gpios[GPIO_PORTE].handler)(change_mask);
    }

    PORTE;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFE = 0;
#    endif
    _CNEIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTF) && !defined(GPIOF_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_F_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNFInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATF;
#    else
    uint32_t change_mask = CNFF;
#    endif

    if (_gpios[GPIO_PORTF].handler != NULL)
    {
        (*_gpios[GPIO_PORTF].handler)(change_mask);
    }

    PORTF;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFF = 0;
#    endif
    _CNFIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTG) && !defined(GPIOG_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_G_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNGInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATG;
#    else
    uint32_t change_mask = CNFG;
#    endif

    if (_gpios[GPIO_PORTG].handler != NULL)
    {
        (*_gpios[GPIO_PORTG].handler)(change_mask);
    }

    PORTG;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFG = 0;
#    endif
    _CNGIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTH) && !defined(GPIOH_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_H_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNHInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATH;
#    else
    uint32_t change_mask = CNFH;
#    endif

    if (_gpios[GPIO_PORTH].handler != NULL)
    {
        (*_gpios[GPIO_PORTH].handler)(change_mask);
    }

    PORTH;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFH = 0;
#    endif
    _CNHIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTI) && !defined(GPIOI_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_I_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNIInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATI;
#    else
    uint32_t change_mask = CNFI;
#    endif

    if (_gpios[GPIO_PORTI].handler != NULL)
    {
        (*_gpios[GPIO_PORTI].handler)(change_mask);
    }

    PORTI;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFI = 0;
#    endif
    _CNIIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTJ) && !defined(GPIOJ_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_J_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNJInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATJ;
#    else
    uint32_t change_mask = CNFJ;
#    endif

    if (_gpios[GPIO_PORTJ].handler != NULL)
    {
        (*_gpios[GPIO_PORTJ].handler)(change_mask);
    }

    PORTJ;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFJ = 0;
#    endif
    _CNJIF = 0;
}
#endif

#if defined(GPIO_HAVE_PORTK) && !defined(GPIOK_DISABLE) && !defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_K_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNKInterrupt(void)
{
#    ifdef GPIO_CN_NOEDGEDETECT
    uint32_t change_mask = CNSTATK;
#    else
    uint32_t change_mask = CNFK;
#    endif

    if (_gpios[GPIO_PORTK].handler != NULL)
    {
        (*_gpios[GPIO_PORTK].handler)(change_mask);
    }

    PORTK;
#    ifndef GPIO_CN_NOEDGEDETECT
    CNFK = 0;
#    endif
    _CNKIF = 0;
}
#endif

#if defined(GPIO_CN_SINGLEINTERRUPT)
void INT_ISR(_CHANGE_NOTICE_VECTOR, GPIOI_INT_PRIORITY, INT_MODE) __attribute__((weak)) CNInterrupt(void)
{
    // TODO
}
#endif
