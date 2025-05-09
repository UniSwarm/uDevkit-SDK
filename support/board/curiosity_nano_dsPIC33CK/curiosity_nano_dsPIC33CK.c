/**
 * @file curiosity_nano_dsPIC33CK.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2025
 *
 * @date February 11, 2025, 03:27 PM
 *
 * @brief Code for Curiosity dsPIC33CK nano board (EV88G73A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/EV88G73A
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/dsPIC33CK64MC105-Curiosity-Nano-Users-Guide-DS70005517.pdf
 */

#include "curiosity_nano_dsPIC33CK.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_buttons[BUTTON_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;  // all analog inputs of port A as analog
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0000;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // Lock configuration pin
    lockIoConfig();
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTD, 10);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);

    _board_buttons[0] = gpio_pin(GPIO_PORTD, 13);
    gpio_setBitConfig(_board_buttons[0], GPIO_INPUT);

    return 0;
}

int board_init(void)
{
    // sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
    archi_init();

    // UART1 pins (UART CDC debug)
    _U1RXR = 59;           // RX1 ==> RP59 C11
    _RP58R = _RPOUT_U1TX;  // TX1 ==> RP58 C10

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
