/**
 * @file curiosity_PIC24F.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 28, 2017, 15:34 PM
 *
 * @brief Code for Curiosity 32MM USB board (DM320107)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM240004
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002534a.pdf
 */

#include "curiosity_PIC24F.h"

#include "driver/sysclock.h"
#include "driver/gpio.h"

rt_dev_t board_leds[LED_COUNT];
rt_dev_t board_buttons[BUTTON_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSA = 0x0000;         // all analog inputs of port A as digital buffer
    ANSB = 0x0000;         // all analog inputs of port B as digital buffer
    ANSC = 0x0001;         // all analog inputs of port C as digital buffer unless RC0 for pot
#endif

    board_leds[0] = gpio_pin(GPIO_PORTA, 9);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTA, 10);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);

    board_buttons[0] = gpio_pin(GPIO_PORTC, 9);
    gpio_setBitConfig(board_buttons[0], GPIO_INPUT);
    board_buttons[1] = gpio_pin(GPIO_PORTC, 8);
    gpio_setBitConfig(board_buttons[1], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_SOSC, 32768); // 32kHz
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
