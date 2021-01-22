/**
 * @file umc1bds32fr.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2020
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
rt_dev_t board_leds[LED_COUNT];

int board_init_io()
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
    ANSELD = 0x1000;        // all analog inputs of port D as digital buffer
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
    board_leds[0] = gpio_pin(GPIO_PORTC, 14);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[1] = gpio_pin(GPIO_PORTC, 13);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);
    board_leds[2] = gpio_pin(GPIO_PORTD, 8);
    gpio_setBitConfig(board_leds[2], GPIO_OUTPUT);
    board_leds[3] = gpio_pin(GPIO_PORTD, 9);
    gpio_setBitConfig(board_leds[3], GPIO_OUTPUT);
#else
#    ifndef SIMULATOR
    _RP43R = _RPOUT_OCM3;  // led1R = RP43
    _RP42R = _RPOUT_OCM4;  // led1G = RP42
    _RP44R = _RPOUT_OCM5;  // led1B = RP44
    _RP47R = _RPOUT_OCM6;  // led2R = RP47
    _RP45R = _RPOUT_OCM7;  // led2G = RP45
    _RP46R = _RPOUT_OCM8;  // led2B = RP46
#    endif
    uint8_t led;
    for (led = 0; led < LED_COUNT; led++)
    {
        board_leds[led] = ccp(led + 3);
        ccp_open(board_leds[led]);
        ccp_setMode(board_leds[led], CCP_MODE_PWM);
        ccp_setPeriod(board_leds[led], 0x7F8);
        ccp_setCompare(board_leds[led], 0, 0x7FF);
        ccp_enable(board_leds[led]);
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
    LATEbits.LATE10 = 0;    // QEI1A_Txen disable
    TRISEbits.TRISE10 = 0;  // QEI1A_Txen

    LATDbits.LATD8 = 0;    // QEI1B_Rxen disable
    TRISDbits.TRISD8 = 0;  // QEI1B_Rxen
    LATDbits.LATD9 = 0;    // QEI1B_Txen disable
    TRISDbits.TRISD9 = 0;  // QEI1B_Txen

    LATEbits.LATE9 = 0;    // QEI1I_Rxen disable
    TRISEbits.TRISE9 = 0;  // QEI1I_Rxen
#    endif
#endif

    // Lock configuration pin
    lockIoConfig();

    return 0;
}

int board_init()
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
        return gpio_setBit(board_leds[led]);
    }
    else
    {
        return gpio_clearBit(board_leds[led]);
    }

#else
    return ccp_setCompare(board_leds[led], 0, 0x7FF - (state << 3));
#endif
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
