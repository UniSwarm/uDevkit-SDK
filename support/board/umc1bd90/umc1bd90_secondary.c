/**
 * @file umc1bd90_secondary.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date April 25, 2022, 02:35 PM
 *
 * @brief Code for UMC1BD90FR / UMC1BD90FR-I board, secondary core
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bd90
 */

#include "umc1bd90.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

rt_dev_t board_leds[LED_COUNT];

int board_init_io(void);

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;
    ANSELB = 0x008F;
    ANSELC = 0x00C8;  // or 0x00CF when sensor is used as analog
    ANSELD = 0x1C00;

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    _QEIA1R = 61;
    _QEIB1R = 62;
    _QEINDX1R = 63;

    // SSI channel 1
    _SDI1R = 62;             // coder_data = QEI1B_RX_DATA, RC14
    _RP41R = _RPOUT_S1SCK1;  // coder_clk = QEI1A_TX_DATA, RB9

    // Lock configuration pin
    lockIoConfig();
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
    UDK_UNUSED(led);
    UDK_UNUSED(state);
    return 0;
}

int board_toggleLed(uint8_t led)
{
    UDK_UNUSED(led);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    UDK_UNUSED(led);
    return 0;
}

int8_t board_getButton(uint8_t button)
{
    UDK_UNUSED(button);
    return -1;
}
