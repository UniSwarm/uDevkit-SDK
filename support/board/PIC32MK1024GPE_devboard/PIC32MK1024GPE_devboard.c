/**
 * @file PIC32MK1024GPE_devboard.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date October 25, 2017, 17:13 AM
 *
 * @brief Code for PIC32MK1024GPE dev board board (DM320106)
 *
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320106
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005316A.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002568B.pdf
 */

#include "PIC32MK1024GPE_devboard.h"

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
    ANSELE = 0x0000;  // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;  // all analog inputs of port G as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    U3RXR = 0b0101;   // RX3 ==> RPC7
    RPC6R = 0b00001;  // TX3 ==> RPC6

    U4RXR = 0b1101;    // RX4 ==> RPD3
    RPA12R = 0b00010;  // TX4 ==> RPA12

    C1RXR = 0b1000;   // CAN1RX ==> RE14
    RPE0R = 0b01100;  // CAN1TX ==> RE0

    C2RXR = 0b1100;    // CAN2RX ==> RE1
    RPE15R = 0b01100;  // CAN2TX ==> RE15

    C3RXR = 0b1010;    // CAN3RX ==> RG6
    RPC15R = 0b01100;  // CAN3TX ==> RC15

    C4RXR = 0b0110;   // CAN4RX ==> RC2
    RPB1R = 0b01100;  // CAN4TX ==> RB1
    lockIoConfig();
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTG, 12);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTG, 13);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTG, 14);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTG, 11);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT);
    _board_buttons[1] = gpio_pin(GPIO_PORTF, 13);
    gpio_setBitConfig(_board_buttons[1], GPIO_INPUT);
    _board_buttons[2] = gpio_pin(GPIO_PORTF, 12);
    gpio_setBitConfig(_board_buttons[2], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 12000000);  // 12MHz
    sysclock_setSourceFreq(SYSCLOCK_SRC_SOSC, 32768);     // 12MHz
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
