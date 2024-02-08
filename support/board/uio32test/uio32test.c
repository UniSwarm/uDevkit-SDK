/**
 * @file uio32test.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date January 21, 2024, 10:30 AM
 *
 * @brief Board support package for UIO32TEST board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio32test
 */

#include "uio32test.h"

#include <driver/gpio.h>
#include <driver/sysclock.h>

static rt_dev_t _board_leds[LED_COUNT];
uint8_t _board_analogin[ANALOGIN_COUNT];

static int _board_init_io(void);

int _board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0xFFFF;           // all analog inputs of port A as analog inputs
    ANSELB = 0x0000;           // all analog inputs of port B as digital buffer
    ANSELC = 0x0080;           // all analog inputs of port C as digital buffer
    ANSELD = 0x0000;           // all analog inputs of port D as digital buffer
    ADCON4Hbits.C1CHS = 0b01;  // Dedicated ADC Core 1 Input Channel Selection bits set to ANA1

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

    // CAN fd 1
    _CAN1RXR = 40;           // CAN1RX ==> RP40
    _RP39R = _RPOUT_CAN1TX;  // CAN1TX ==> RP39

    // Lock configuration pin
    lockIoConfig();

    LED_LAT = 1;
    TRISBbits.TRISB2 = 0;  // LED_LAT
#endif

    _board_leds[LEDOUT1] = GPIO_PD10;
    gpio_setBitConfig(_board_leds[LEDOUT1], GPIO_OUTPUT);

    _board_analogin[0] = BOARD_IN1_ADC_CHAN;
    _board_analogin[1] = BOARD_IN2_ADC_CHAN;
    _board_analogin[2] = BOARD_IN3_ADC_CHAN;
    _board_analogin[3] = BOARD_IN4_ADC_CHAN;

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

uint8_t board_analogin(uint8_t io)
{
    if (io >= ANALOGIN_COUNT)
    {
        return 0;
    }
    return _board_analogin[io];
}

uint8_t board_dipId(void)
{
#ifndef SIMULATOR
    return (~((DIP1 << 0) + (DIP2 << 1) + (DIP3 << 2) + (DIP4 << 3)) & 0x0F) + 1;
#else
    return 0;
#endif
}

typedef struct
{
    union
    {
        uint32_t g32;
        struct
        {
            uint32_t IO01 : 1;
            uint32_t IO02 : 1;
            uint32_t IO03 : 1;
            uint32_t IO04 : 1;
            uint32_t IO05 : 1;
            uint32_t IO06 : 1;
            uint32_t IO07 : 1;
            uint32_t IO08 : 1;
            uint32_t IO09 : 1;
            uint32_t IO10 : 1;
            uint32_t IO11 : 1;
            uint32_t IO12 : 1;
            uint32_t IO13 : 1;
            uint32_t IO14 : 1;
            uint32_t IO15 : 1;
            uint32_t IO16 : 1;
            uint32_t IO17 : 1;
            uint32_t IO18 : 1;
            uint32_t IO19 : 1;
            uint32_t IO20 : 1;
            uint32_t IO21 : 1;
            uint32_t IO22 : 1;
            uint32_t IO23 : 1;
            uint32_t IO24 : 1;
            uint32_t IO25 : 1;
            uint32_t IO26 : 1;
            uint32_t IO27 : 1;
            uint32_t IO28 : 1;
            uint32_t IO29 : 1;
            uint32_t IO30 : 1;
            uint32_t IO31 : 1;
            uint32_t IO32 : 1;
        };
    };
} Global32;

typedef struct
{
    union
    {
        uint16_t p16;
        struct
        {
            uint32_t IO00 : 1;
            uint32_t IO01 : 1;
            uint32_t IO02 : 1;
            uint32_t IO03 : 1;
            uint32_t IO04 : 1;
            uint32_t IO05 : 1;
            uint32_t IO06 : 1;
            uint32_t IO07 : 1;
            uint32_t IO08 : 1;
            uint32_t IO09 : 1;
            uint32_t IO10 : 1;
            uint32_t IO11 : 1;
            uint32_t IO12 : 1;
            uint32_t IO13 : 1;
            uint32_t IO14 : 1;
            uint32_t IO15 : 1;
        };
    };
} Port16;

uint32_t portsToGlobal32(uint16_t ports[])
{
    Global32 io;

    Port16 portB;
    portB.p16 = ports[1];
    Port16 portC;
    portC.p16 = ports[2];
    Port16 portD;
    portD.p16 = ports[3];

    io.IO01 = portD.IO01;
    io.IO02 = portD.IO00;
    io.IO03 = portB.IO10;
    io.IO04 = portB.IO11;
    io.IO05 = portB.IO12;
    io.IO06 = portB.IO13;
    io.IO07 = portB.IO14;
    io.IO08 = portB.IO15;
    io.IO09 = portC.IO12;
    io.IO10 = portC.IO13;
    io.IO11 = portC.IO14;
    io.IO12 = portC.IO15;
    io.IO13 = portD.IO15;
    io.IO14 = portD.IO14;
    io.IO15 = portD.IO12;
    io.IO16 = portC.IO08;
    io.IO17 = portC.IO09;
    io.IO18 = portD.IO09;
    io.IO19 = portD.IO08;
    io.IO20 = portD.IO07;
    io.IO21 = portD.IO06;
    io.IO22 = portD.IO05;
    io.IO23 = portB.IO05;
    io.IO24 = portB.IO06;
    io.IO25 = portC.IO04;
    io.IO26 = portC.IO05;
    io.IO27 = portC.IO10;
    io.IO28 = portC.IO11;
    io.IO29 = portD.IO04;
    io.IO30 = portD.IO03;
    io.IO31 = portD.IO02;
    io.IO32 = portB.IO09;
    return io.g32;
}

void global32ToPorts(uint32_t global, uint16_t ports[])
{
    Global32 io;
    io.g32 = global;

    // PortA
    ports[0] = 0;

    // PortB
    Port16 portB;
    portB.IO05 = io.IO23;
    portB.IO06 = io.IO24;
    portB.IO09 = io.IO32;
    portB.IO10 = io.IO03;
    portB.IO11 = io.IO04;
    portB.IO12 = io.IO05;
    portB.IO13 = io.IO06;
    portB.IO14 = io.IO07;
    portB.IO15 = io.IO08;
    ports[1] = portB.p16;

    // PortC
    Port16 portC;
    portC.IO04 = io.IO25;
    portC.IO05 = io.IO26;
    portC.IO08 = io.IO16;
    portC.IO09 = io.IO17;
    portC.IO10 = io.IO27;
    portC.IO11 = io.IO28;
    portC.IO12 = io.IO09;
    portC.IO13 = io.IO10;
    portC.IO14 = io.IO11;
    portC.IO15 = io.IO12;
    ports[2] = portC.p16;

    // PortD
    Port16 portD;
    portD.IO00 = io.IO02;
    portD.IO01 = io.IO01;
    portD.IO02 = io.IO31;
    portD.IO03 = io.IO30;
    portD.IO04 = io.IO29;
    portD.IO05 = io.IO22;
    portD.IO06 = io.IO21;
    portD.IO07 = io.IO20;
    portD.IO08 = io.IO19;
    portD.IO09 = io.IO18;
    portD.IO12 = io.IO15;
    portD.IO14 = io.IO14;
    portD.IO15 = io.IO13;
    ports[3] = portD.p16;
}
