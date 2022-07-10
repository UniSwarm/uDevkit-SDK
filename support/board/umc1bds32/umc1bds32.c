/**
 * @file umc1bds32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2022
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32
 */

#include "umc1bds32.h"

#include <driver/ccp.h>
#include <driver/gpio.h>
#include <driver/sysclock.h>

int _board_init_io(void);

rt_dev_t _board_leds[LED_COUNT];

#ifdef SIMULATOR
int _board_sim_bridgesEnable = 0;
#endif

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;
    ANSELB = 0x008F;
    ANSELC = 0x00C8;  // or 0x00CF when sensor is used as analog
    ANSELD = 0x1C00;

    CNPUDbits.CNPUD14 = 1;  // pullup reset button

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (RS485)
    _U1RXR = 70;           // RX1 ==> RP70
    _RP57R = _RPOUT_U1TX;  // TX1 ==> RP57

    // CAN fd 1
    _CAN1RXR = 69;           // CAN1RX ==> RP69
    _RP71R = _RPOUT_CAN1TX;  // CAN1TX ==> RP71

    _QEIA1R = 49;
    _QEIB1R = 50;
    _QEINDX1R = 48;

    TRISCbits.TRISC8 = 0;  // RS485 DE
    LATCbits.LATC8 = 1;

    TRISBbits.TRISB4 = 0;   // DBG1
    TRISEbits.TRISE13 = 0;  // DBG2
#endif

    // init leds
#ifndef SIMULATOR
    _RP43R = _RPOUT_OCM3;  // led1R = RP43
    _RP42R = _RPOUT_OCM4;  // led1G = RP42
    _RP44R = _RPOUT_OCM5;  // led1B = RP44
    _RP47R = _RPOUT_OCM6;  // led2R = RP47
    _RP45R = _RPOUT_OCM7;  // led2G = RP45
    _RP46R = _RPOUT_OCM8;  // led2B = RP46
#endif
    for (uint8_t led = 0; led < LED_COUNT; led++)
    {
        _board_leds[led] = ccp(led + 3);
        ccp_open(_board_leds[led]);
        ccp_setMode(_board_leds[led], CCP_MODE_PWM);
        ccp_setPeriod(_board_leds[led], 0x7F8);
        ccp_setCompare(_board_leds[led], 0, 0x7FF);
        ccp_enable(_board_leds[led]);
    }

#ifndef SIMULATOR
    // ==== power
    LATEbits.LATE2 = 0;    // 12Ven disable
    TRISEbits.TRISE2 = 0;  // 12Ven in out mode

    LATCbits.LATC12 = 0;    // poweren disable
    TRISCbits.TRISC12 = 0;  // poweren in out mode

    LATDbits.LATD14 = 1;    // bridgedis
    TRISDbits.TRISD14 = 0;  // bridgeen in out mode

    // ==== sensor 1
    LATEbits.LATE11 = 0;    // QEI1A_Rxen disable // TODO disable when not used in receive
    TRISEbits.TRISE11 = 0;  // QEI1A_Rxen
    LATEbits.LATE10 = 0;    // QEI1A_Txen disable // TODO SSI
    TRISEbits.TRISE10 = 0;  // QEI1A_Txen

    LATDbits.LATD8 = 0;    // QEI1B_Rxen disable // TODO disable when not used in receive
    TRISDbits.TRISD8 = 0;  // QEI1B_Rxen
    LATDbits.LATD9 = 0;    // QEI1B_Txen disable
    TRISDbits.TRISD9 = 0;  // QEI1B_Txen

    LATEbits.LATE9 = 0;    // QEI1I_Rxen disable // TODO disable when not used in receive
    TRISEbits.TRISE9 = 0;  // QEI1I_Rxen

    // SSI, channel 2
    _SDI1R = 63;  // coder_data = QEI1I_RX_DATA
    _SCK1R = 41;  // coder_clk = QEI1A_TX_DATA
#endif

    // Lock configuration pin
    lockIoConfig();

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

    return ccp_setCompare(_board_leds[led], 0, 0x7FF - ((uint16_t)state << 3));
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
#ifndef SIMULATOR
    if (button == 0)
    {
        return BUTTON_RESET;
    }
#endif
    return -1;
}

void board_setBridgesEnabled(int enable)
{
    if (enable == 1)
    {
#ifndef SIMULATOR
        BRIDGE_DISABLED_OUT = 0;
#endif
    }
    else
    {
#ifndef SIMULATOR
        BRIDGE_DISABLED_OUT = 1;
#endif
    }

#ifdef SIMULATOR
    _board_sim_bridgesEnable = enable;
#endif
}
