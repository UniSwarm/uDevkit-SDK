/**
 * @file curiosity_32MX470.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Code for Curiosity 32MX470 board (DM320103)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320103
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005283B.pdf
 */

#include "curiosity_32MX470.h"

#ifdef SIMULATOR
uint8_t board_led_state = 0;
#include <stdio.h>
#endif

int board_init_io()
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;         // all analog inputs of port B as digital buffer
    ANSELD = 0x0000;         // all analog inputs of port D as digital buffer
    ANSELE = 0x0000;         // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;         // all analog inputs of port G as digital buffer

    TRISEbits.TRISE4 = 0;    // LED1
    TRISEbits.TRISE6 = 0;    // LED2
    TRISEbits.TRISE7 = 0;    // LED3
#endif
    return 0;
}

int board_init()
{
    archi_init();

    board_init_io();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if(led >= LED_COUNT)
        return -1;
#ifndef SIMULATOR
    if(led == 0)
        LED1 = state;
    if(led == 1)
        LED2 = state;
    if(led == 2)
        LED3 = state;
#else
    if(state == 1)
    {
        printf("LED %d on\n", led);
        board_led_state |= (1 << led);
    }
    else
    {
        printf("LED %d off\n", led);
        board_led_state &= !(1 << led);
    }
#endif
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;
#ifndef SIMULATOR
    if(led == 0)
        return LED1;
    if(led == 1)
        return LED2;
    if(led == 2)
        return LED3;
#else
    return board_led_state & (!(1 << led));
#endif
    return 0;
}
