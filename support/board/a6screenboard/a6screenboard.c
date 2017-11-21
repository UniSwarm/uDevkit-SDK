/**
 * @file a6screenboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 49, 2016, 08:49 AM
 *
 * @brief Code for A6screenboard from Robotips
 */

#include "a6screenboard.h"

int board_init_io()
{
#ifndef SIMULATOR
    ANSELB = 0x0000;            // all analog inputs of port B as digital buffer
    ANSELD = 0x0000;            // all analog inputs of port D as digital buffer
    ANSELE = 0x0000;            // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;            // all analog inputs of port G as digital buffer

    // screen pins
    TRISDbits.TRISD3 = 0;       // SCREEN_RD pin as output
    TRISDbits.TRISD2 = 0;       // SCREEN_RW pin as output
    TRISDbits.TRISD1 = 0;       // SCREEN_RS pin as output
    TRISDbits.TRISD0 = 0;       // SCREEN_CS pin as output
    TRISDbits.TRISD4 = 0;       // SCREEN_RST pin as output
    TRISEbits.TRISE4 = 0;       // SCREEN_LEDBL pin as output

    TRISFbits.TRISF1 = 0;       // A6_RW pin as output

    // Unlock configuration pin
    OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;

        // UART1 pins (A6)
        _U1RXR = 80; // RX ==> RP80 AXrx
        _RP96R = _RPOUT_U1TX; // TX ==> RP96 AXtx

        // SPI1 pins (AR1000)
        _SDI1R = 119;
        _RP120R = _RPOUT_SDO1;
        _RP118R = _RPOUT_SCK1;
        _RP85R = _RPOUT_SS1;

        _U2RXR = 118; // RX2 ==> RP118
        _RP120R = _RPOUT_U2TX; // TX2 ==> RP120

        // OC PWM luminosity
        _RP64R = _RPOUT_OC1; // OC1 ==> RP64

    // Lock configuration pin
    OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
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
    return -1;
}

int8_t board_getLed(uint8_t led)
{
    return -1;
}

int board_toggleLed(uint8_t led)
{
    return -1;
}

int8_t board_getButton(uint8_t button)
{
    return -1;
}
