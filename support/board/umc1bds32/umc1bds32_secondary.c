/**
 * @file umc1bds32_secondary.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2021
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board, secondary core
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32
 */

#include "umc1bds32.h"

#include "driver/gpio.h"
#include "driver/sysclock.h"

rt_dev_t board_leds[LED_COUNT];

int board_init_io(void);

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;
#    if BOARD_VERSION < 110
    ANSELB = 0x0007;
    ANSELC = 0x00CF;
    ANSELD = 0xF000;
#    else
    ANSELB = 0x008F;
    ANSELC = 0x00C8;  // or 0x00CF when sensor is used as analog
    ANSELD = 0x1C00;
#    endif

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
#    if BOARD_VERSION < 110
    _QEIA1R = 47;
    _QEIB1R = 46;
    _QEINDX1R = 60;
#    else
    _QEIA1R = 61;
    _QEIB1R = 62;
    _QEINDX1R = 63;
#    endif

    // SSI channel 1
    _SDI1R = 62;             // coder_data = QEI1B_RX_DATA, RC14
    _RP41R = _RPOUT_S1SCK1;  // coder_clk = QEI1A_TX_DATA, RB9

    // Lock configuration pin
    lockIoConfig();
#endif

#if BOARD_VERSION < 110
    board_leds[0] = gpio_pin(GPIO_PORTC, 14);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTC, 13);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);
#endif

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
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

#if BOARD_VERSION < 110
    if (state & 1)
    {
        gpio_setBit(board_leds[led]);
    }
    else
    {
        gpio_clearBit(board_leds[led]);
    }
#else
    UDK_UNUSED(state);
#endif
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

#if BOARD_VERSION < 110
    gpio_toggleBit(board_leds[led]);
#endif
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

#if BOARD_VERSION < 110
    return gpio_readBit(board_leds[led]);
#else
    return 0;
#endif
}

int8_t board_getButton(uint8_t button)
{
    UDK_UNUSED(button);
    return -1;
}

int board_bridgesEnabled(void)
{
#ifndef SIMULATOR
    return (BRIDGE_DISABLED_IN == 0 && STO_STATUS_OK_IN == 1) ? 1 : 0;
#else
    return (_board_sim_bridgesEnable == 1) ? 1 : 0;
#endif
}
