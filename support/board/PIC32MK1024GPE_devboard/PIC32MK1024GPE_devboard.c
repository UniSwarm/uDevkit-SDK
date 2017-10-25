/**
 * @file PIC32MK1024GPE_devboard.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date October 25, 2017, 17:13 AM
 *
 * @brief Code for PIC32MK1024GPE dev board board (DM320106)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320106
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005316A.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002568B.pdf
 */

#include "PIC32MK1024GPE_devboard.h"

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

    TRISGbits.TRISG12 = 0;    // LED1
    TRISGbits.TRISG13 = 0;    // LED2
    TRISGbits.TRISG14 = 0;    // LED3

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
        U6RXR = 0b1101;        // RX6 ==> RPA15
        RPA4R = 0b01011;       // TX6 ==> RPA4
    lockIoConfig();
#endif
    return 0;
}

int board_init()
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 12000000); // 12MHz
    sysclock_setSourceFreq(SYSCLOCK_SRC_SOSC, 32768); // 12MHz
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
