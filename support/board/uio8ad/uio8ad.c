/**
 * @file uio8ad.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020-2021
 *
 * @date August 31, 2020, 11:30 AM
 *
 * @brief Board support package for UIO8AD(FR) / UIO8AD(FR)-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio8ad
 */

#include "uio8ad.h"

#include <driver/ccp.h>
#include <driver/gpio.h>
#include <driver/sysclock.h>

#include "pwm.h"

rt_dev_t _board_leds[LED_COUNT];
rt_dev_t _board_outs_H[OUT_COUNT];
rt_dev_t _board_outs_L[OUT_COUNT];
rt_dev_t _board_out3h_en;
DO_MODE _board_outs_mode[OUT_COUNT];
uint8_t _board_analogin[ANALOGIN_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFFFF;  // all analog inputs of port A as analog inputs
    ANSELB = 0x0004;  // all analog inputs of port B as digital buffer unless RB2
    ANSELC = 0x000F;  // all analog inputs of port C as digital buffer unless RC3-0
    ANSELD = 0x0000;  // all analog inputs of port D as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // UART1 pins (RS485)
    _U1RXR = 35;           // RX1 ==> RP35
    _RP36R = _RPOUT_U1TX;  // TX1 ==> RP36

    // CAN fd 1
    _CAN1RXR = 57;           // CAN1RX ==> RP57
    _RP73R = _RPOUT_CAN1TX;  // CAN1TX ==> RP73

    _RP39R = _RPOUT_OCM1;  // led1R = RP39
    _RP69R = _RPOUT_OCM2;  // led1G = RP69
    _RP40R = _RPOUT_OCM3;  // led1B = RP40

    TRISCbits.TRISC8 = 0;  // DE
    LATCbits.LATC8 = 0;

    TRISCbits.TRISC4 = 0;   // out0H
    TRISCbits.TRISC5 = 0;   // out0L
    TRISCbits.TRISC10 = 0;  // out1H
    TRISCbits.TRISC11 = 0;  // out1L
    TRISDbits.TRISD1 = 0;   // out2H
    TRISDbits.TRISD0 = 0;   // out2L
    TRISBbits.TRISB10 = 0;  // out3H
    TRISBbits.TRISB11 = 0;  // out3L

    TRISBbits.TRISB12 = 0;  // out4H
    TRISBbits.TRISB13 = 0;  // out4L
    TRISBbits.TRISB14 = 0;  // out5H
    TRISBbits.TRISB15 = 0;  // out5L
    TRISCbits.TRISC12 = 0;  // out6H
    TRISCbits.TRISC13 = 0;  // out6L
    TRISCbits.TRISC14 = 0;  // out7H
    TRISCbits.TRISC15 = 0;  // out7L

    // Lock configuration pin
    lockIoConfig();
#endif

    _board_leds[LEDOUT1] = GPIO_PB09;
    gpio_setBitConfig(_board_leds[LEDOUT1], GPIO_OUTPUT);
    _board_leds[LEDOUT2] = GPIO_PD04;
    gpio_setBitConfig(_board_leds[LEDOUT2], GPIO_OUTPUT);
    _board_leds[LEDOUT3] = GPIO_PD02;
    gpio_setBitConfig(_board_leds[LEDOUT3], GPIO_OUTPUT);
    _board_leds[LEDOUT4] = GPIO_PD12;
    gpio_setBitConfig(_board_leds[LEDOUT4], GPIO_OUTPUT);
    _board_leds[LEDOUT5] = GPIO_PB01;
    gpio_setBitConfig(_board_leds[LEDOUT5], GPIO_OUTPUT);
    _board_leds[LEDOUT6] = GPIO_PD11;
    gpio_setBitConfig(_board_leds[LEDOUT6], GPIO_OUTPUT);
    _board_leds[LEDOUT7] = GPIO_PD10;
    gpio_setBitConfig(_board_leds[LEDOUT7], GPIO_OUTPUT);
    _board_leds[LEDOUT8] = GPIO_PC07;
    gpio_setBitConfig(_board_leds[LEDOUT8], GPIO_OUTPUT);

    _board_leds[LED1R] = ccp(1);
    ccp_open(_board_leds[LED1R]);
    ccp_setMode(_board_leds[LED1R], CCP_MODE_PWM);
    ccp_setPeriod(_board_leds[LED1R], 0x7F8);
    ccp_setCompare(_board_leds[LED1R], 0, 0x7F8);
    ccp_enable(_board_leds[LED1R]);

    _board_leds[LED1G] = ccp(2);
    ccp_open(_board_leds[LED1G]);
    ccp_setMode(_board_leds[LED1G], CCP_MODE_PWM);
    ccp_setPeriod(_board_leds[LED1G], 0x7F8);
    ccp_setCompare(_board_leds[LED1G], 0, 0x7F8);
    ccp_enable(_board_leds[LED1G]);

    _board_leds[LED1B] = ccp(3);
    ccp_open(_board_leds[LED1B]);
    ccp_setMode(_board_leds[LED1B], CCP_MODE_PWM);
    ccp_setPeriod(_board_leds[LED1B], 0x7F8);
    ccp_setCompare(_board_leds[LED1B], 0, 0x7F8);
    ccp_enable(_board_leds[LED1B]);

    _board_analogin[0] = BOARD_IN0_ADC_CHAN;
    _board_analogin[1] = BOARD_IN1_ADC_CHAN;
    _board_analogin[2] = BOARD_IN2_ADC_CHAN;
    _board_analogin[3] = BOARD_IN3_ADC_CHAN;
    _board_analogin[4] = BOARD_IN4_ADC_CHAN;
    _board_analogin[5] = BOARD_IN5_ADC_CHAN;
    _board_analogin[6] = BOARD_IN6_ADC_CHAN;
    _board_analogin[7] = BOARD_IN7_ADC_CHAN;

    // Low side output pins definition and configuration
    _board_outs_L[0] = GPIO_PC05;
    gpio_setBitConfig(_board_outs_L[0], GPIO_OUTPUT);
    _board_outs_L[1] = GPIO_PC11;
    gpio_setBitConfig(_board_outs_L[1], GPIO_OUTPUT);
    _board_outs_L[2] = GPIO_PD00;
    gpio_setBitConfig(_board_outs_L[2], GPIO_OUTPUT);
    _board_outs_L[3] = GPIO_PB11;
    gpio_setBitConfig(_board_outs_L[3], GPIO_OUTPUT);

    _board_outs_L[4] = GPIO_PB13;
    gpio_setBitConfig(_board_outs_L[4], GPIO_OUTPUT);
    _board_outs_L[5] = GPIO_PB15;
    gpio_setBitConfig(_board_outs_L[5], GPIO_OUTPUT);
    _board_outs_L[6] = GPIO_PC13;
    gpio_setBitConfig(_board_outs_L[6], GPIO_OUTPUT);
    _board_outs_L[7] = GPIO_PC15;
    gpio_setBitConfig(_board_outs_L[7], GPIO_OUTPUT);

    // High side output pins definition and configuration
    _board_outs_H[0] = GPIO_PC04;
    gpio_setBitConfig(_board_outs_H[0], GPIO_OUTPUT);
    _board_outs_H[1] = GPIO_PC10;
    gpio_setBitConfig(_board_outs_H[1], GPIO_OUTPUT);
    _board_outs_H[2] = GPIO_PD01;
    gpio_setBitConfig(_board_outs_H[2], GPIO_OUTPUT);
    _board_outs_H[3] = GPIO_PB10;
    gpio_setBitConfig(_board_outs_H[3], GPIO_OUTPUT);

    _board_outs_H[4] = GPIO_PB12;
    gpio_setBitConfig(_board_outs_H[4], GPIO_OUTPUT);
    _board_outs_H[5] = GPIO_PB14;
    gpio_setBitConfig(_board_outs_H[5], GPIO_OUTPUT);
    _board_outs_H[6] = GPIO_PC12;
    gpio_setBitConfig(_board_outs_H[6], GPIO_OUTPUT);
    _board_outs_H[7] = GPIO_PC14;
    gpio_setBitConfig(_board_outs_H[7], GPIO_OUTPUT);

    _board_out3h_en = GPIO_PD03;
    gpio_setBitConfig(_board_out3h_en, GPIO_OUTPUT);  // out3h active on low output
    gpio_clearBit(_board_out3h_en);

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, SYSCLOCK_POSC);
    archi_init();

    board_init_io();

    // Set PWM generators
    pwm_init();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if (led >= LED_COUNT)
    {
        return -1;
    }

    if (led <= LEDOUT8)
    {
        if (state & 1)
        {
            gpio_setBit(_board_leds[led]);
        }
        else
        {
            gpio_clearBit(_board_leds[led]);
        }
    }
    else
    {
        ccp_setCompare(_board_leds[led], 0, (uint16_t)state << 3);
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

    pwm_write(io, state);

    return 0;
}

// IO mode modification will only be changed at the next write on the IO
int board_setIOMode(uint8_t io, DO_MODE mode)
{
    if (io >= OUT_COUNT)
    {
        return -1;
    }

    pwm_setIOMode(io, mode);

    return 0;
}

int board_setIOPWMFrequency(uint8_t io, uint8_t frequency)
{
    if (io >= OUT_COUNT)
    {
        return -1;
    }

    return pwm_setFrequency(io, frequency);
}

uint8_t board_analogin(uint8_t io)
{
    if (io >= ANALOGIN_COUNT)
    {
        return 0;
    }
    return _board_analogin[io];
}
