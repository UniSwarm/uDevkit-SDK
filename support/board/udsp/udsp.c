/**
 * @file curiosity_dsPIC33AK128MC106.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date September 13, 2026, 02:51 PM
 *
 * @brief Board support package for uDSP board
 */

#include "udsp.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0000;  // all analog inputs of port A as digital buffer
    ANSELB = 0x0000;  // all analog inputs of port B as digital buffer

    // CODEC_PDN = 0;
    TRISBbits.TRISB7 = 0;  // CODEC_PDN

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
    _U1RXR = 8;           // RX1 ==> RPA7
    _RP1R = _RPOUT_U1TX;  // TX1 ==> RPA0

    _U2RXR = 50;           // RX2 ==> RPD1
    _RP49R = _RPOUT_U2TX;  // TX2 ==> RPD0

    _RP4R = _RPOUT_REFO1;  // REFO1 ==>RPA3

    _RP5R = _RPOUT_SCK1;   // BICK ==> RPA4
    _RP6R = _RPOUT_SS1;    // LRCK ==> RPA5
    _RP22R = _RPOUT_SDO1;  // SDIN1 ==> RPB5
    lockIoConfig();
#endif

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 8000000);  // 8MHz
    // external osc configuration : EC with IO for OSCO
    OSCCFGbits.POSCIOFNC = 0b0;  // CLKO output disabled
    OSCCFGbits.POSCMD = 1;       // OSCI for EC in, OSCO for clk out
    archi_init();

    _board_init_io();

    return 0;
}
