/**
 * @file uio1led.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021
 *
 * @date August 11, 2021, 07:42 PM
 *
 * @brief Board support package for UIO1LEDF board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio1led
 */

#include "uio1led.h"

#include <driver/ccp.h>
#include <driver/gpio.h>
#include <driver/sysclock.h>

int board_init_io(void);

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFF0F;  // all analog inputs of port A as analog inputs
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer unless RB2
    TRISAbits.TRISA4 = 0;

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // CAN fd 1
    _CAN1RXR = 37;           // CAN1RX ==> RP57
    _RP34R = _RPOUT_CAN1TX;  // CAN1TX ==> RP73

    _RP45R = _RPOUT_PWM4H;  // PWM4H ==> RP45
    // ODCBbits.ODCB13 = 1;    // RB13/RP45 in open drain mode

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
    return -1;
}

int board_toggleLed(uint8_t led)
{
    UDK_UNUSED(led);
    return -1;
}

int8_t board_getLed(uint8_t led)
{
    UDK_UNUSED(led);
    return -1;
}

int8_t board_getButton(uint8_t button)
{
    UDK_UNUSED(button);
    return 0;
}
