/**
 * @file curiosity_32MZ_EF.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Code for Curiosity 32MZ EF board (DM320103)
 *
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320104
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005282B.pdf
 */

#include "curiosity_32MZ_EF.h"

#include "driver/gpio.h"
#include "driver/sysclock.h"

rt_dev_t board_leds[LED_COUNT];
rt_dev_t board_buttons[BUTTON_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0000;  // all analog inputs of port A as digital buffer
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer
    ANSELE = 0x0000;  // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;  // all analog inputs of port G as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    U1RXR = 0b0011;   // RX1 ==> RPD10
    RPD15R = 0b0001;  // TX1 ==> RPD15

    U2RXR = 0b1100;  // RX2 ==> RPC3
    RPC2R = 0b0010;  // TX2 ==> RPC2

    RPD14R = 0b1101;  // REFCLKO4 ==> RPD14
    lockIoConfig();
#endif

    board_leds[0] = gpio_pin(GPIO_PORTE, 3);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTE, 4);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);
    board_leds[2] = gpio_pin(GPIO_PORTE, 6);
    gpio_setBitConfig(board_leds[2], GPIO_OUTPUT);

    board_buttons[0] = gpio_pin(GPIO_PORTG, 12);
    gpio_setBitConfig(board_buttons[0], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 24000000);  // 24MHz
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
    GPIO_VALUE value;
    if (button >= BUTTON_COUNT)
    {
        return -1;
    }

    value = gpio_readBit(board_buttons[button]);
    if (value == GPIO_HIGH)
    {
        return 0;
    }
    return 1;
}
