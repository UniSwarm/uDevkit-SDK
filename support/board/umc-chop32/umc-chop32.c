/**
 * @file umc-chop32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date August 22, 2022, 10:00 AM
 *
 * @brief Board support package for UMC-CHOP32 board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc-chop32
 */

#include "umc-chop32.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFFFF;
    ANSELB = 0x0000;
    ANSELC = 0x0000;

    LATBbits.LATB14 = 0;  // Mofet out
    TRISBbits.TRISB14 = 0;
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTB, 11);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTB, 12);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTB, 13);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    board_setLed(0, 1);
    board_setLed(1, 1);
    board_setLed(2, 1);

    return 0;
}

int board_init(void)
{
    // sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
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
    UDK_UNUSED(button);
    return -1;
}
