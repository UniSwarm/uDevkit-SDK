/**
 * @file swarmtips2.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 15, 2017, 01:16 AM
 *
 * @brief Code for swarmtips2 from Robotips
 */

#include "swarmtips2.h"

#include <archi.h>

#ifdef SIMULATOR
uint8_t board_led_state = 0;
#include <stdio.h>
#endif

int board_init_io()
{
#ifndef SIMULATOR
    int i;

    // analog inputs
    ANSELB = 0x0000;    // all analog inputs of port B as digital buffer
    ANSELE = 0x0000;    // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;    // all analog inputs of port G as digital buffer

    ANSELBbits.ANSB15 = 1;       // BOARD_VOLT_IN as analog

    TRISCbits.TRISC15 = 0;       // OSC_EN pin as output
    OSC_EN = 1;

    // digitals outputs
    TRISBbits.TRISB7 = 0;       // LED1 pin as output
    TRISBbits.TRISB6 = 0;       // LED2 pin as output
    TRISBbits.TRISB3 = 0;       // LED3 pin as output

    TRISBbits.TRISB11 = 0;      // CHARGER_CE pin as output
    //TRISBbits.TRISB14 = 0;      // CHARGER_SYS pin as output

    TRISCbits.TRISC14 = 0;      // M1DIR pin as output
    TRISCbits.TRISC13 = 0;      // M2DIR pin as output
    TRISBbits.TRISB8 = 0;       // BOOST_SLEEP pin as output

    TRISEbits.TRISE5 = 0;       // ESP8266_RST pin as output
    TRISEbits.TRISE7 = 0;       // ESP8266_FLASH pin as output
    ESP8266_FLASH = 1;
    ESP8266_RST   = 0;

    for(i=0;i<65000;i++);
    ESP8266_RST   = 1;

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

        // UART2 pins (esp8266 wifi)
        U2RXR = 0b0001;         // RX2 ==> RPG6
        RPG9R = 0b0010;         // TX2 ==> RPG9

        // OC PWM motors and buzzer
        RPB2R = 0b1100;  // OC1             // buzzer pwm tone
        RPF4R = 0b1011;  // OC3             // M1 pwm speed
        RPF5R = 0b1011;  // OC4             // M2 pwm speed

    // Lock configuration pin
    lockIoConfig();
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
    switch(led)
    {
    case 0:
        LED1 = state;
        break;
    case 1:
        LED2 = state;
        break;
    case 2:
        LED3 = state;
        break;
    }
#else
    if(state & 0x01)
    {
        //printf("LED %d on\n", led);
        board_led_state |= (1 << led);
    }
    else
    {
        //printf("LED %d off\n", led);
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
    switch(led)
    {
    case 0:
        return LED1;
    case 1:
        return LED2;
    case 2:
        return LED3;
    }
    return 0;
#else
    return board_led_state & (!(1 << led));
#endif
}
