/**
 * @file umc1bds32_secondary.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2022
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board, secondary core
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32
 */

#include "umc1bds32.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
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

    // UART1 dbg
    _RP66R = _RPOUT_S1U1TX;  // TX1 ==> RP66

    // Lock configuration pin
    lockIoConfig();

    TRISDbits.TRISD2 = 0;   // DBG1
    TRISEbits.TRISE12 = 0;  // DBG2
#endif

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
