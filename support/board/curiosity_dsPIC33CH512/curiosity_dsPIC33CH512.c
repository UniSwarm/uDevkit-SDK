/**
 * @file curiosity_dsPIC33CH512.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2022
 *
 * @date September 23, 2019, 20:05 PM
 *
 * @brief Code for Curiosity dsPIC33CH512 board (DM330028-2)
 *
 * product page:
 *  https://www.microchip.com/developmenttools/ProductDetails/DM330028-2
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/DS50002801%20-%20dsPIC33CH%20Curiosity%20Development%20Board%20Users%20Guide.pdf
 */

#include "curiosity_dsPIC33CH512.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_buttons[BUTTON_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0001;  // all analog inputs of port A as digital buffer unless RA0 for pot
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (micro bus A)
    _U1RXR = 64;           // RX1 ==> RP64
    _RP65R = _RPOUT_U1TX;  // TX1 ==> RP65

    // UART2 pins (micro bus B)
    _U2RXR = 58;           // RX2 ==> RP58
    _RP59R = _RPOUT_U2TX;  // TX2 ==> RP59

    // Lock configuration pin
    lockIoConfig();
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTE, 0);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTE, 1);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTE, 7);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT);
    _board_buttons[1] = gpio_pin(GPIO_PORTE, 8);
    gpio_setBitConfig(_board_buttons[1], GPIO_INPUT);
    _board_buttons[2] = gpio_pin(GPIO_PORTE, 9);
    gpio_setBitConfig(_board_buttons[2], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
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
