/**
 * @file uio32test.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date January 21, 2024, 10:30 AM
 *
 * @brief Board support package for UIO32TEST board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio32test
 */

#include "uio32test.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
uint8_t _board_analogin[ANALOGIN_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFFFF;  // all analog inputs of port A as analog inputs
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer
    ANSELC = 0x0080;  // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // CAN fd 1
    _CAN1RXR = 40;           // CAN1RX ==> RP40
    _RP39R = _RPOUT_CAN1TX;  // CAN1TX ==> RP39

    LED_LAT = 1;
    TRISBbits.TRISB2 = 0;  // LED_LAT

    // Lock configuration pin
    lockIoConfig();
#endif

    _board_leds[LEDOUT1] = GPIO_PD10;
    gpio_setBitConfig(_board_leds[LEDOUT1], GPIO_OUTPUT);

    _board_analogin[0] = BOARD_IN0_ADC_CHAN;
    _board_analogin[1] = BOARD_IN1_ADC_CHAN;
    _board_analogin[2] = BOARD_IN2_ADC_CHAN;
    _board_analogin[3] = BOARD_IN3_ADC_CHAN;

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
    (void)button;
    return 0;
}

uint8_t board_analogin(uint8_t io)
{
    if (io >= ANALOGIN_COUNT)
    {
        return 0;
    }
    return _board_analogin[io];
}

uint8_t board_dipId(void)
{
    return (~((DIP1 << 0) + (DIP2 << 1) + (DIP3 << 2) + (DIP4 << 3)) & 0x0F) + 1;
}
