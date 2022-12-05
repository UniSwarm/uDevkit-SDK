/**
 * @file udt1cr-i.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2022
 *
 * @date November 26, 2018, 18:00 PM
 *
 * @brief Code for UDT1FR from UniSwarm
 *
 * product page:
 *  https://uniswarm.fr/uboards/udt/udt1fr
 */

#include "udt1cr-i.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _iso_en_gpio;
static rt_dev_t _iso_rs485_re_gpio;
static rt_dev_t _iso_rs485_de_gpio;

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELE = 0x0000;  // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;  // all analog inputs of port G as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    C2RXR = 0b0001;  // CAN2RX ==> RG6
    RPG9R = 0b1111;  // CAN2TX ==> RG9

    U3RXR = 0b0001;  // U3RX ==> RG7
    RPG8R = 0b0001;  // U3TX ==> RG8

    // UART 1 dbg
    RPB3R = 0b0001;  // U1TX ==> RB3
    lockIoConfig();
#endif

#if BOARD_VERSION < 110
    _iso_en_gpio = gpio_pin(GPIO_PORTE, 4);
#else
    _iso_en_gpio = gpio_pin(GPIO_PORTC, 13);
#endif
    gpio_clearBit(_iso_en_gpio);
    gpio_setBitConfig(_iso_en_gpio, GPIO_OUTPUT);

    _iso_rs485_re_gpio = gpio_pin(GPIO_PORTB, 7);
    gpio_setBit(_iso_rs485_re_gpio);
    gpio_setBitConfig(_iso_rs485_re_gpio, GPIO_OUTPUT);

    _iso_rs485_de_gpio = gpio_pin(GPIO_PORTB, 2);
    gpio_clearBit(_iso_rs485_de_gpio);
    gpio_setBitConfig(_iso_rs485_de_gpio, GPIO_OUTPUT);

    _board_leds[0] = gpio_pin(GPIO_PORTD, 9);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTD, 10);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTD, 11);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    _board_leds[3] = gpio_pin(GPIO_PORTB, 6);
    gpio_setBitConfig(_board_leds[3], GPIO_OUTPUT);
    _board_leds[4] = gpio_pin(GPIO_PORTB, 8);
    gpio_setBitConfig(_board_leds[4], GPIO_OUTPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 24000000);  // 24MHz
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
    return 0;
}

rt_dev_t board__iso_en_gpio(void)
{
    return _iso_en_gpio;
}

rt_dev_t board__iso_rs485_re_gpio(void)
{
    return _iso_rs485_re_gpio;
}

rt_dev_t board__iso_rs485_de_gpio(void)
{
    return _iso_rs485_de_gpio;
}
