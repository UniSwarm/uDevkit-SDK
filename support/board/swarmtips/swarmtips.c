/**
 * @file swarmtips.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date August 13, 2016, 12:04 PM
 *
 * @brief Definitions for Swarmtips platform from Robotips
 */

#include "swarmtips.h"

#include <driver/sysclock.h>
#include <driver/gpio.h>
#include <driver/i2c.h>

rt_dev_t board_leds[LED_COUNT];

#include "modules.h"
#ifdef USE_MODULE_sensor
 #include <module/sensor.h>
#endif

rt_dev_t swarmtips_i2c_tof;

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;    // all analog inputs of port B as digital buffer
    ANSELD = 0x0000;    // all analog inputs of port D as digital buffer
    ANSELE = 0x0000;    // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;    // all analog inputs of port G as digital buffer

    ANSELBbits.ANSB8 = 1;       // BOARD_VOLT_IN as analog

    // digitals outputs
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

    board_leds[0] = gpio_pin(GPIO_PORTB, 3);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTD, 11);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);

    return 0;
}

int board_init(void)
{
    uint16_t i, j;
    archi_init();

    board_init_io();

    swarmtips_i2c_tof = i2c_getFreeDevice();
    //i2c_open(swarmtips_i2c_tof);
    i2c_setBaudSpeed(swarmtips_i2c_tof, I2C_BAUD_400K);
    i2c_enable(swarmtips_i2c_tof);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

#ifdef USE_MODULE_sensor
    VL6180X_init(swarmtips_i2c_tof, 0x52);
#endif

    return 0;
}

rt_dev_t board_i2c_tof(void)
{
    return swarmtips_i2c_tof;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if(led >= LED_COUNT)
        return -1;

    if (state & 1)
        gpio_setBit(board_leds[led]);
    else
        gpio_clearBit(board_leds[led]);
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    gpio_toggleBit(board_leds[led]);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    return gpio_readBit(board_leds[led]);
}

int8_t board_getButton(uint8_t button)
{
    return -1;
}
