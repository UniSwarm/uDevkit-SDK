/**
 * @file umc1bds32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2021
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32
 */

#include "umc1bds32.h"

#include "driver/ccp.h"
#include "driver/gpio.h"
#include "driver/sysclock.h"

/****************************************************************************************/
/*          Privates functions                                                          */
int board_init_io(void);

/****************************************************************************************/
/*          External variable                                                           */

/****************************************************************************************/
/*          Local variable                                                              */
rt_dev_t _board_leds[LED_COUNT];

#ifdef SIMULATOR
int _board_sim_bridgesEnable = 0;
#endif

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x001F;  // all analog inputs of port A as analog
#    if BOARD_VERSION < 110
    ANSELB = 0x0006;  // all analog inputs of port B as digital buffer
#    else
    ANSELB = 0x008E;        // all analog inputs of port B as digital buffer
#    endif
    ANSELC = 0x00C8;  // all analog inputs of port C as digital buffer
#    if BOARD_VERSION < 110
    ANSELD = 0xF000;  // all analog inputs of port D as digital buffer
#    else
    ANSELD = 0x1C00;        // all analog inputs of port D as digital buffer
#    endif

#    if BOARD_VERSION < 110
    CNPUDbits.CNPUD10 = 1;  // pullup STO in1
    CNPUDbits.CNPUD11 = 1;  // pullup STO in2
#    else
    CNPUDbits.CNPUD14 = 1;  // pullup reset button
#    endif

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (RS485)
    _U1RXR = 70;           // RX1 ==> RP70
    _RP57R = _RPOUT_U1TX;  // TX1 ==> RP57

    // CAN fd 1
    _CAN1RXR = 69;           // CAN1RX ==> RP69
    _RP71R = _RPOUT_CAN1TX;  // CAN1TX ==> RP71

#    if BOARD_VERSION < 110
    _QEIA1R = 47;
    _QEIB1R = 46;
    _QEINDX1R = 60;
#    else
    _QEIA1R = 49;           // same pins as slaves for the moment
    _QEIB1R = 50;
    _QEINDX1R = 48;
#    endif

    TRISCbits.TRISC8 = 0;  // RS485 DE
#    if BOARD_VERSION < 110
    TRISBbits.TRISB4 = 0;  // RS485 RE
#    endif
    LATCbits.LATC8 = 0;
#endif

    // init leds
#if BOARD_VERSION < 110
    _board_leds[0] = gpio_pin(GPIO_PORTC, 14);
    gpio_setBitConfig(_board_leds[0], GPIO_OUTPUT);
    _board_leds[1] = gpio_pin(GPIO_PORTC, 13);
    gpio_setBitConfig(_board_leds[1], GPIO_OUTPUT);
    _board_leds[2] = gpio_pin(GPIO_PORTD, 8);
    gpio_setBitConfig(_board_leds[2], GPIO_OUTPUT);
    _board_leds[3] = gpio_pin(GPIO_PORTD, 9);
    gpio_setBitConfig(_board_leds[3], GPIO_OUTPUT);
#else
#    ifndef SIMULATOR
    _RP43R = _RPOUT_OCM3;  // led1R = RP43
    _RP42R = _RPOUT_OCM4;  // led1G = RP42
    _RP44R = _RPOUT_OCM5;  // led1B = RP44
    _RP47R = _RPOUT_OCM6;  // led2R = RP47
    _RP45R = _RPOUT_OCM7;  // led2G = RP45
    _RP46R = _RPOUT_OCM8;  // led2B = RP46
#    endif
    for (uint8_t led = 0; led < LED_COUNT; led++)
    {
        _board_leds[led] = ccp(led + 3);
        ccp_open(_board_leds[led]);
        ccp_setMode(_board_leds[led], CCP_MODE_PWM);
        ccp_setPeriod(_board_leds[led], 0x7F8);
        ccp_setCompare(_board_leds[led], 0, 0x7FF);
        ccp_enable(_board_leds[led]);
    }
#endif

#ifndef SIMULATOR
#    if BOARD_VERSION >= 110
    // ==== power
    LATEbits.LATE2 = 0;    // 12Ven disable
    TRISEbits.TRISE2 = 0;  // 12Ven in out mode

    LATCbits.LATC12 = 0;    // poweren disable
    TRISCbits.TRISC12 = 0;  // poweren in out mode

    LATDbits.LATD14 = 1;    // bridgedis
    TRISDbits.TRISD14 = 0;  // bridgeen in out mode

    // ==== sensor 1
    LATEbits.LATE11 = 0;    // QEI1A_Rxen disable
    TRISEbits.TRISE11 = 0;  // QEI1A_Rxen
    LATEbits.LATE10 = 0;    // QEI1A_Txen disable // TODO SSI
    TRISEbits.TRISE10 = 0;  // QEI1A_Txen

    LATDbits.LATD8 = 0;    // QEI1B_Rxen disable
    TRISDbits.TRISD8 = 0;  // QEI1B_Rxen
    LATDbits.LATD9 = 0;    // QEI1B_Txen disable
    TRISDbits.TRISD9 = 0;  // QEI1B_Txen

    LATEbits.LATE9 = 0;    // QEI1I_Rxen disable
    TRISEbits.TRISE9 = 0;  // QEI1I_Rxen

    // SSI, channel 2
    _SDI1R = 63;  // coder_data = QEI1I_RX_DATA
    _SCK1R = 41;  // coder_clk = QEI1A_TX_DATA
#    endif
#endif

    // Lock configuration pin
    lockIoConfig();

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
        return gpio_setBit(_board_leds[led]);
    }
    else
    {
        return gpio_clearBit(_board_leds[led]);
    }

#else
    return ccp_setCompare(_board_leds[led], 0, 0x7FF - ((uint16_t)state << 3));
#endif
}

int board_toggleLed(uint8_t led)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

#if BOARD_VERSION < 110
    gpio_toggleBit(_board_leds[led]);
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
    return gpio_readBit(_board_leds[led]);
#else
    return 0;
#endif
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

int8_t board_getIo(uint8_t io)
{
#ifndef SIMULATOR
    switch (io)
    {
#    ifdef IO_1_IN
        case 1:
            return IO_1_IN;
            break;
#    endif
#    ifdef IO_2_IN
        case 2:
            return IO_2_IN;
            break;
#    endif
#    ifdef IO_3_IN
        case 3:
            return IO_3_IN;
            break;
#    endif
#    ifdef IO_4_IN
        case 4:
            return IO_4_IN;
            break;
#    endif
#    ifdef IO_5_IN
        case 5:
            return IO_5_IN;
            break;
#    endif
#    ifdef IO_6_IN
        case 6:
            return IO_6_IN;
            break;
#    endif
#    ifdef IO_7_IN
        case 7:
            return IO_7_IN;
            break;
#    endif
#    ifdef IO_8_IN
        case 8:
            return IO_8_IN;
            break;
#    endif
        default:
            return -1;
            break;
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

int board_bridgesEnabled(void)
{
#ifndef SIMULATOR
    return (BRIDGE_DISABLED_IN == 0 && STO_STATUS_OK_IN == 1) ? 1 : 0;
#else
    return (_board_sim_bridgesEnable == 1) ? 1 : 0;
#endif
}
