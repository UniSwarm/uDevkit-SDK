/**
 * @file uio44.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date November 28, 2018, 09:30 AM
 *
 * @brief Code for UIO44(FR) / UIO44(FR)-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio44
 */

#include "uio44.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
static rt_dev_t _board_outs[OUT_COUNT];
static uint8_t _board_analogin[ANALOGIN_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFFFF;  // all analog inputs of port A as digital buffer unless RA0-3
    ANSELB = 0xE200;  // all analog inputs of port B as digital buffer
    ANSELC = 0x4B4F;  // all analog inputs of port C as digital buffer
    ANSELD = 0xF4FD;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (RS485)
    _U1RXR = 52;           // RX1 ==> RP52
    _RP58R = _RPOUT_U1TX;  // TX1 ==> RP58

    // UART2 pins (dbg out only)
    //_RP61R = _RPOUT_U2TX;  // TX2 ==> RP61

    // CAN fd 1
    _CAN1RXR = 53;           // CAN1RX ==> RP53
    _RP59R = _RPOUT_CAN1TX;  // CAN1TX ==> RP59

    TRISDbits.TRISD1 = 0;   // DE
    TRISBbits.TRISB10 = 0;  // RE
    LATDbits.LATD1 = 1;

    // Lock configuration pin
    lockIoConfig();
#endif
    _board_analogin[0] = BOARD_IN0_ADC_CHAN;
    _board_analogin[1] = BOARD_IN1_ADC_CHAN;
    _board_analogin[2] = BOARD_IN2_ADC_CHAN;
    _board_analogin[3] = BOARD_IN3_ADC_CHAN;

    _board_leds[0] = gpio_pin(GPIO_PORTB, 8);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTB, 7);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTC, 8);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    _board_leds[3] = gpio_pin(GPIO_PORTB, 4);
    gpio_setBitConfig(_board_leds[3], GPIO_OUTPUT);
    _board_leds[4] = gpio_pin(GPIO_PORTB, 11);
    gpio_setBitConfig(_board_leds[4], GPIO_OUTPUT);
    _board_leds[5] = gpio_pin(GPIO_PORTB, 12);
    gpio_setBitConfig(_board_leds[5], GPIO_OUTPUT);

    _board_outs[0] = gpio_pin(GPIO_PORTB, 1);
    gpio_setBitConfig(_board_outs[0], GPIO_OUTPUT);
    _board_outs[1] = gpio_pin(GPIO_PORTD, 10);
    gpio_setBitConfig(_board_outs[1], GPIO_OUTPUT);
    _board_outs[2] = gpio_pin(GPIO_PORTC, 7);
    gpio_setBitConfig(_board_outs[2], GPIO_OUTPUT);
    _board_outs[3] = gpio_pin(GPIO_PORTB, 2);
    gpio_setBitConfig(_board_outs[3], GPIO_OUTPUT);

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

int board_setIO(uint8_t io, uint16_t state)
{
    if (io >= OUT_COUNT)
    {
        return -1;
    }

    if (state & 1)
    {
        gpio_setBit(_board_outs[io]);
    }
    else
    {
        gpio_clearBit(_board_outs[io]);
    }
    return 0;
}

int board_setIOMode(uint8_t io, DO_MODE mode)
{
    if (io >= OUT_COUNT)
    {
        return -1;
    }

    if (mode != DO_OPEN_DRAIN)
    {
        return -2;
    }

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
