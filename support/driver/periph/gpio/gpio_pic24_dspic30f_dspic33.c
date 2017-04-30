/**
 * @file gpio_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date March 20, 2017, 18:39 AM
 *
 * @brief GPIO support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70058D, DS70193D and DS70000598C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70058D.pdf (dsPIC30F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70193D.pdf (PIC24F/dsPIC33F)
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70000598c.pdf (PIC24E/dsPIC33E)
 */

#include "gpio.h"

#include <archi.h>

void gpio_setBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch(port)
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
}

void gpio_clearBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = ~(1 << (device & GPIO_MAX_PORTWIDTHMASK));

    switch(port)
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
}

void gpio_toggleBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch(port)
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
}

void gpio_writeBit(rt_dev_t device, GPIO_VALUE value)
{
    switch(value)
    {
    case GPIO_LOW:
        gpio_clearBit(device);
        break;
    case GPIO_HIGHT:
        gpio_setBit(device);
        break;
    case GPIO_TOGGLE:
        gpio_toggleBit(device);
        break;
    }
}

GPIO_VALUE gpio_readBit(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);
    uint16_t value = 0;

    switch(port)
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

    if((value & bit) == 1)
        return GPIO_HIGHT;
    else
        return GPIO_LOW;
}

int gpio_setBitConfig(rt_dev_t device, uint16_t config)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;
    uint16_t bit = 1 << (device & GPIO_MAX_PORTWIDTHMASK);

    switch(port)
    {
#ifdef GPIO_HAVE_PORTA
    case 0:
        if(config & GPIO_OUTPUT)
            TRISA &= ~bit; // set as output
        else
            TRISA |= bit;  // set as input
        break;
#endif
#ifdef GPIO_HAVE_PORTB
    case 1:
        if(config & GPIO_OUTPUT)
            TRISB &= ~bit; // set as output
        else
            TRISB |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTC
    case 2:
        if(config & GPIO_OUTPUT)
            TRISC &= ~bit; // set as output
        else
            TRISC |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTD
    case 3:
        if(config & GPIO_OUTPUT)
            TRISD &= ~bit; // set as output
        else
            TRISD |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTE
    case 4:
        if(config & GPIO_OUTPUT)
            TRISE &= ~bit; // set as output
        else
            TRISE |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTF
    case 5:
        if(config & GPIO_OUTPUT)
            TRISF &= ~bit; // set as output
        else
            TRISF |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTG
    case 6:
        if(config & GPIO_OUTPUT)
            TRISG &= ~bit; // set as output
        else
            TRISG |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTH
    case 7:
        if(config & GPIO_OUTPUT)
            TRISH &= ~bit; // set as output
        else
            TRISH |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTI
    case 8:
        if(config & GPIO_OUTPUT)
            TRISI &= ~bit; // set as output
        else
            TRISI |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTJ
    case 9:
        if(config & GPIO_OUTPUT)
            TRISJ &= ~bit; // set as output
        else
            TRISJ |= bit;  // set as input;
        break;
#endif
#ifdef GPIO_HAVE_PORTK
    case 10:
        if(config & GPIO_OUTPUT)
            TRISK &= ~bit; // set as output
        else
            TRISK |= bit;  // set as input;
        break;
#endif
    }

    return 0;
}

void gpio_writePort(rt_dev_t device, port_type value)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    switch(port)
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

port_type gpio_readPort(rt_dev_t device)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    switch(port)
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

int gpio_setPortConfig(rt_dev_t device, uint16_t config)
{
    uint8_t port = MINOR(device) >> GPIO_MAX_PORTWIDTHU;

    uint16_t trisValue;
    if(config & GPIO_OUTPUT)
        trisValue = 0x0000;
    else
        trisValue = 0xFFFF;

    switch(port)
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
    }

    return 0;
}