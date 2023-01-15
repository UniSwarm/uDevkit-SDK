/**
 * @file curiosity_dsPIC33CK.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 15, 2022, 07:42 PM
 *
 * @brief Code for Curiosity dsPIC33CK board (DM330030)
 *
 * product page:
 *  http://www.microchip.com/developmenttools/ProductDetails/PartNO/DM330030
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/dsPIC33CK-Curiosity-Development-Board-User%27s-Guide-DS50002859A.pdf
 */

#include "curiosity_dsPIC33CK.h"

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
    ANSELC = 0x0080;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer
    ANSELE = 0x0080;  // all analog inputs of port E as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (micro bus A)
    _U1RXR = 79;           // RX1 ==> RP79
    _RP78R = _RPOUT_U1TX;  // TX1 ==> RP78

    // UART2 pins (micro bus B)
    _U2RXR = 76;           // RX2 ==> RP76
    _RP73R = _RPOUT_U2TX;  // TX2 ==> RP73

    // UART3 pins debug
    _U3RXR = 67;           // RX3 ==> RP67
    _RP68R = _RPOUT_U3TX;  // TX3 ==> RP68

    // Lock configuration pin
    lockIoConfig();
#endif

    _board_leds[0] = gpio_pin(GPIO_PORTE, 6);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTE, 5);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTE, 15);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    _board_leds[3] = gpio_pin(GPIO_PORTE, 14);
    gpio_setBitConfig(_board_leds[3], GPIO_OUTPUT);
    _board_leds[4] = gpio_pin(GPIO_PORTE, 13);
    gpio_setBitConfig(_board_leds[4], GPIO_OUTPUT);

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
