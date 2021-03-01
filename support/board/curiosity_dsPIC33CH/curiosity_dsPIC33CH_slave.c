/**
 * @file curiosity_dsPIC33CH.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date July 5, 2018, 09:30 AM
 *
 * @brief Code for Curiosity dsPIC33CH board (DM330028), slave part
 * 
 * product page:
 *  http://www.microchip.com/developmenttools/ProductDetails/PartNO/DM330028
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33CH%20Curiosity%20Development%20Board.pdf
 */

#include "curiosity_dsPIC33CH.h"

#include "driver/sysclock.h"
#include "driver/gpio.h"

rt_dev_t board_leds[LED_COUNT];
rt_dev_t board_buttons[BUTTON_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0001;         // all analog inputs of port A as digital buffer unless RA0 for pot
    ANSELB = 0x0000;         // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;         // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;         // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();


    // Lock configuration pin
    lockIoConfig();
#endif

    board_leds[0] = gpio_pin(GPIO_PORTE, 0);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTE, 1);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);

    board_buttons[0] = gpio_pin(GPIO_PORTE, 7);
    gpio_setBitConfig(board_buttons[0], GPIO_INPUT);
    board_buttons[1] = gpio_pin(GPIO_PORTE, 8);
    gpio_setBitConfig(board_buttons[1], GPIO_INPUT);
    board_buttons[2] = gpio_pin(GPIO_PORTE, 9);
    gpio_setBitConfig(board_buttons[2], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
    archi_init();

    board_init_io();

    return 0;
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
    GPIO_VALUE value;
    if(button >= BUTTON_COUNT)
        return -1;

    value = gpio_readBit(board_buttons[button]);
    if (value == GPIO_HIGH)
        return 0;
    return 1;
}
