/**
 * @file curiosity_32MM_USB.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
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

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_buttons[BUTTON_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0000;  // all analog inputs of port A as digital buffer
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTD, 3);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTC, 13);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTB, 9);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT);
    _board_buttons[1] = gpio_pin(GPIO_PORTC, 10);
    gpio_setBitConfig(_board_buttons[1], GPIO_INPUT);
    _board_buttons[2] = gpio_pin(GPIO_PORTC, 4);
    gpio_setBitConfig(_board_buttons[2], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_SOSC, 32768);  // 32kHz
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
