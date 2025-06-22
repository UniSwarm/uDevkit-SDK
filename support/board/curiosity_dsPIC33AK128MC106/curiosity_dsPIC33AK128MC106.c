/**
 * @file curiosity_dsPIC33AK128MC106.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date June 22, 2025, 06:01 PM
 *
 * @brief Code for Curiosity dsPIC33AK128MC106 board (EV02G02A) plus Curiosity Platform Development Board (EV74H48A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/ev02g02a
 *  https://www.microchip.com/en-us/development-tool/EV74H48A
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/InformationSheet/dsPIC33AK128MC106-General-Purpose-DIM-Info-Sheet-DS70005556.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/Curiosity-Platform-Development-Board-Users-Guide-DS70005562.pdf
 */

#include "curiosity_dsPIC33AK128MC106.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_buttons[BUTTON_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0080;  // all analog inputs of port A as digital buffer unless RA7 potentiometer
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    _U1RXR = 52;           // RX1 ==> RPD10
    _RP50R = _RPOUT_U1TX;  // TX1 ==> RPD15

    _U2RXR = 59;           // RX2 ==> RPC3
    _RP58R = _RPOUT_U2TX;  // TX2 ==> RPC2
    lockIoConfig();
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTC, 3);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTC, 4);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTC, 5);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    _board_leds[3] = gpio_pin(GPIO_PORTC, 6);
    gpio_setBitConfig(_board_leds[3], GPIO_OUTPUT);
    _board_leds[4] = gpio_pin(GPIO_PORTC, 7);
    gpio_setBitConfig(_board_leds[4], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTA, 6);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT);
    _board_buttons[1] = gpio_pin(GPIO_PORTB, 4);
    gpio_setBitConfig(_board_buttons[1], GPIO_INPUT);
    _board_buttons[2] = gpio_pin(GPIO_PORTB, 5);
    gpio_setBitConfig(_board_buttons[2], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 8000000);  // 8MHz
    archi_init();

    _board_init_io();

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
        gpio_setBit(_board_leds[led]);
    }
    else
    {
        gpio_clearBit(_board_leds[led]);
    }
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    gpio_toggleBit(_board_leds[led]);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    return gpio_readBit(_board_leds[led]);
}

int8_t board_getButton(uint8_t button)
{
    GPIO_VALUE value;
    if (button >= BUTTON_COUNT)
    {
        return -1;
    }

    value = gpio_readBit(_board_buttons[button]);
    if (value == GPIO_HIGH)
    {
        return 0;
    }
    return 1;
}
