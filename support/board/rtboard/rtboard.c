/**
 * @file rtboard.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date April 11, 2016, 06:07 PM
 *
 * @brief Code for RTboard from Robotips
 *
 * product page:
 *  https://www.robotips.fr/fr/projet/RTboard
 *  https://hackaday.io/project/20901-rtboard-10
 * datasheet:
 *  https://www.robotips.fr/data/gpage/11/squaretips_mother-board_schematics.pdf
 */

#include "rtboard.h"

#include "driver/gpio.h"
#include "driver/sysclock.h"

rt_dev_t board_leds[LED_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer
    ANSELE = 0x0007;  // all analog inputs of port E as digital buffer, RE2-0 as analog
    ANSELG = 0x0000;  // all analog inputs of port G as digital buffer

    ANSELBbits.ANSB2 = 1;  // BOARD_VOLT_IN as analog
    ANSELBbits.ANSB1 = 1;  // M1I as analog
    ANSELBbits.ANSB0 = 1;  // M2I as analog
    ANSELBbits.ANSB6 = 1;  // M3I as analog
    ANSELBbits.ANSB7 = 1;  // M4I as analog

    // digitals outputs
    TRISBbits.TRISB15 = 0;  // M1A pin as output
    TRISBbits.TRISB14 = 0;  // M1B pin as output

    TRISBbits.TRISB12 = 0;  // M2A pin as output
    TRISBbits.TRISB13 = 0;  // M2B pin as output

    TRISBbits.TRISB10 = 0;  // M3A pin as output
    TRISBbits.TRISB11 = 0;  // M3B pin as output

    TRISBbits.TRISB8 = 0;  // M4A pin as output
    TRISBbits.TRISB9 = 0;  // M4B pin as output

    TRISBbits.TRISB3 = 0;  // AX12_TXEN pin as output
    TRISDbits.TRISD1 = 0;  // A6_RW pin as output

    // remappable pins
    // Unlock configuration pin
    OSCCONL = 0x46;
    OSCCONL = 0x57;
    OSCCONbits.IOLOCK = 0;

    // UART1 pins (wifi esp)
    _U1RXR = 71;           // RX1 ==> RP71
    _RP69R = _RPOUT_U1TX;  // TX1 ==> RP69

    // UART2 pins (A6)
    _U2RXR = 72;           // RX2 ==> RPI72 A6rx
    _RP66R = _RPOUT_U2TX;  // TX2 ==> RP66 A6tx

    // UART3 pins (AX12)
    _U3RXR = 97;            // RX3 ==> RP97 AXrx
    _RP120R = _RPOUT_U3TX;  // TX3 ==> RP120 AXtx

    // UART4 pins (debug)
    _U4RXR = 86;           // RX4 ==> RPI86 AS7
    _RP85R = _RPOUT_U4TX;  // TX4 ==> RP85 AS6

    // QEI1 pins (coder 1)
    _QEA1R = 119;  // C1A ==> RPI119
    _QEB1R = 118;  // C1B ==> RPI118

    // QEI2 pins (coder 2)
    _QEA2R = 37;   // C2A ==> RPI37
    _QEB2R = 121;  // C2B ==> RPI121

    // OC PWM motors (motor 1-4)
    _RP64R = _RPOUT_OC1;   // OC1 ==> RP64
    _RP99R = _RPOUT_OC2;   // OC2 ==> RP99
    _RP101R = _RPOUT_OC3;  // OC3 ==> RP101
    _RP100R = _RPOUT_OC4;  // OC4 ==> RP100

    // Lock configuration pin
    OSCCONL = 0x46;
    OSCCONL = 0x57;
    OSCCONbits.IOLOCK = 1;
#endif

    board_leds[0] = gpio_pin(GPIO_PORTD, 11);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 8000000);  // 8MHz
    archi_init();

    board_init_io();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    if (state & 1)
    {
        gpio_setBit(board_leds[led]);
    }
    else
    {
        gpio_clearBit(board_leds[led]);
    }
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    gpio_toggleBit(board_leds[led]);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    return gpio_readBit(board_leds[led]);
}

int8_t board_getButton(uint8_t button)
{
    return -1;
}
