/**
 * @file emz64.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date March 01, 2017, 06:09 PM
 *
 * @brief Code for pic32-emz64 from Olimex
 */

#include "emz64.h"

#ifdef SIMULATOR
uint8_t board_led_state = 0;
#include <stdio.h>
#endif

int board_init_io()
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;         // all analog inputs of port B as digital buffer
    
    TRISBbits.TRISB8 = 0;    // LED1 
    TRISBbits.TRISB9 = 0;    // LED2 
    TRISBbits.TRISB10 = 0;   // LED3 
#endif
    return 0;
}

int board_init()
{
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
    return LED1;
#else
    return board_led_state & (!(1 << led));
#endif
}
