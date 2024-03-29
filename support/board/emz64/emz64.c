/**
 * @file emz64.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 01, 2017, 06:09 PM
 *
 * @brief Code for pic32-emz64 from Olimex
 *
 * product page:
 *  https://www.olimex.com/Products/PIC/Development/PIC32-EMZ64/open-source-hardware
 *
 * datasheet:
 *  https://www.olimex.com/Products/PIC/Development/PIC32-EMZ64/resources/PIC32-EMZ64_user_manual.pdf
 */

#include "emz64.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_buttons[BUTTON_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELB = 0x0018;  // all analog inputs of port B as digital buffer, unless RB3/4 for audio in/out
    ANSELE = 0x0000;  // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;  // all analog inputs of port G as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    C1RXR = 0b0111;   // CAN1RX ==> RC13
    RPC14R = 0b1111;  // CAN1TX ==> RC14

    U4RXR = 0b0011;  // U4RX ==> RD0
    RPD4R = 0b0010;  // U4TX ==> RD4
    lockIoConfig();

    TRISFbits.TRISF1 = 0;  // OLED_RST

    TRISBbits.TRISB11 = 0;
    LATBbits.LATB11 = 1;  // eth nreset in active state
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTB, 8);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTB, 9);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTB, 10);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTB, 12);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT | GPIO_PULLUP);
    _board_buttons[1] = gpio_pin(GPIO_PORTB, 13);
    gpio_setBitConfig(_board_buttons[1], GPIO_INPUT | GPIO_PULLUP);
    _board_buttons[2] = gpio_pin(GPIO_PORTB, 14);
    gpio_setBitConfig(_board_buttons[2], GPIO_INPUT | GPIO_PULLUP);

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
