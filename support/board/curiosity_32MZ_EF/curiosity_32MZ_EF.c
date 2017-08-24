/**
 * @file curiosity_32MZ_EF.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Code for Curiosity 32MZ EF board (DM320103)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320104
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005282B.pdf
 */

#include "curiosity_32MZ_EF.h"

#include "driver/sysclock.h"

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
    ANSELE = 0x0000;         // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;         // all analog inputs of port G as digital buffer

    TRISEbits.TRISE3 = 0;    // LED1
    TRISEbits.TRISE4 = 0;    // LED2
    TRISEbits.TRISE6 = 0;    // LED3

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
        U2RXR = 0b1100;         // RX2 ==> RPC3
        RPC2R = 0b0010;         // TX2 ==> RPC2
    lockIoConfig();
#endif
    return 0;
}

int board_init()
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 24000000); // 24MHz
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
