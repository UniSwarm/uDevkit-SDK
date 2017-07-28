/**
 * @file curiosity_32MM_USB.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 28, 2017, 15:34 PM
 *
 * @brief Code for Curiosity 32MM USB board (DM320107)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320107
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002576a%20PIC32MM%20USB%20Curiosity%20Development%20Board%20Quick%20Start%20Guide.pdf
 */

#include "curiosity_32MM_USB.h"

#ifdef SIMULATOR
uint8_t board_led_state = 0;
#include <stdio.h>
#endif

int board_init_io()
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0000;         // all analog inputs of port A as digital buffer
    ANSELB = 0x0000;         // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;         // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;         // all analog inputs of port D as digital buffer

    TRISDbits.TRISD3 = 0;    // LED1
    TRISCbits.TRISC13 = 0;   // LED2
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
#else
    return board_led_state & (!(1 << led));
#endif
    return 0;
}
