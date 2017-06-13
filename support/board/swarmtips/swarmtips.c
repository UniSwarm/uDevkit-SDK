/**
 * @file swarmtips.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 13, 2016, 12:04 PM
 *
 * @brief Definitions for Swarmtips platform from Robotips
 */

#include "swarmtips.h"

#include <driver/adc.h>
#include <driver/i2c.h>

#include <module/sensor.h>

#ifdef SIMULATOR
uint8_t board_led_state = 0;
#include <stdio.h>
#endif

rt_dev_t swarmtips_i2c_tof;

int board_init_io()
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;    // all analog inputs of port B as digital buffer
    ANSELD = 0x0000;    // all analog inputs of port D as digital buffer
    ANSELE = 0x0000;    // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;    // all analog inputs of port G as digital buffer

    ANSELBbits.ANSB8 = 1;       // BOARD_VOLT_IN as analog

    // digitals outputs
    TRISBbits.TRISB3 = 0;       // LED pin as output
    TRISDbits.TRISD11 = 0;      // LED2 pin as output

    TRISEbits.TRISE4 = 0;       // M1A pin as output
    TRISEbits.TRISE6 = 0;       // M1B pin as output

    TRISEbits.TRISE1 = 0;       // M2A pin as output
    TRISEbits.TRISE3 = 0;       // M2B pin as output

    // remappable pins
    // Unlock configuration pin
    OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;

        // UART1 pins (wifi)
        _U1RXR = 47; // RX1 ==> RPI47
        _RP68R = _RPOUT_U1TX; // TX1 ==> RP68

        // UART2 pins (LEDs RGB) TX only
        _RP102R = _RPOUT_U2TX; // TX2 ==> RP102

        // OC PWM motors (motor 1-4)
        _RP85R = _RPOUT_OC1; // OC1 ==> RP85
        _RP87R = _RPOUT_OC2; // OC2 ==> RP87
        _RP80R = _RPOUT_OC3; // OC3 ==> RP80
        _RP82R = _RPOUT_OC4; // OC4 ==> RP82

    // Lock configuration pin
    OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
#endif
    return 0;
}

int board_init()
{
    uint16_t i, j;
    init_archi();

    board_init_io();

    swarmtips_i2c_tof = i2c_getFreeDevice();
    i2c_setBaudSpeed(swarmtips_i2c_tof, I2C_BAUD_400K);
    i2c_enable(swarmtips_i2c_tof);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

    VL6180X_init(swarmtips_i2c_tof, 0x52);

    return 0;
}

rt_dev_t board_i2c_tof()
{
    return swarmtips_i2c_tof;
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
    return LED1;
#else
    return board_led_state & (!(1 << led));
#endif
}
