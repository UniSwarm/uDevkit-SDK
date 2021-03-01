/**
 * @file UMC4D30CRU.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 21, 2018, 20:00 PM
 *
 * @brief Code for UMC4D30CRU board (or UMC4D30CRU-I)
 *
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320106
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005316A.pdf
 */

#include "UMC4D30CRU.h"

#include "driver/sysclock.h"
#include "driver/gpio.h"

rt_dev_t board_leds[LED_COUNT];
rt_dev_t board_buttons[BUTTON_COUNT];

int board_init_io(void)
{
#ifndef SIMULATOR
    // analog inputs
    ANSELA = 0x0807;         // all analog inputs of port A as digital buffer
    ANSELB = 0x008F;         // all analog inputs of port B as digital buffer
    ANSELC = 0x1003;         // all analog inputs of port C as digital buffer
    ANSELD = 0x4000;         // all analog inputs of port D as digital buffer
    ANSELE = 0x0200;         // all analog inputs of port E as digital buffer
    ANSELF = 0x2020;         // all analog inputs of port F as digital buffer
    ANSELG = 0x0000;         // all analog inputs of port G as digital buffer

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();
        // QEI M1
        QEA2R = 0b1100; // RG1
        QEB2R = 0b1100; // RF0
        // invalid index

        // QEI M2
        QEA1R = 0b1011;
        QEB1R = 0b1011;
        // INDX1R = 0b1100;

        // QEI M3
        QEA3R = 0b0101;
        QEB3R = 0b0110;
        // INDX3R = 0b0101;

        // QEI M4
        QEA4R = 0b1101;
        QEB4R = 0b1101;
        // invalid index

        // CAN
        C1RXR = 0b1000;
        RPE0R = 0b01100; // (CAN1)

        // RS485
        U3RXR = 0b1101;
        RPC15R = 0b00001; // (UART3)

        // UART
        U4RXR = 0b1000;
        RPE1R = 0b00010; // (UART4)

        // accel gyro
        /*SDI6R = 0b0100;
        RPC10R = 0b10001; // (SPI6)
        RPB11R = 0b10001; // (SPI6 SCL)*/

        // LED1
        RPA8R = 0b01000; // (OC9)
    lockIoConfig();

    TRISGbits.TRISG7 = 0; // BM1
    TRISBbits.TRISB9 = 0; // AM2
    TRISDbits.TRISD8 = 0; // BM2
    TRISDbits.TRISD6 = 0; // AM3
    TRISDbits.TRISD5 = 0; // BM3
    TRISGbits.TRISG8 = 0; // AM4
    TRISGbits.TRISG10 = 0; // BM4
#endif

    /*board_leds[1] = gpio_pin(GPIO_PORTB, 13);
    gpio_setBitConfig(board_leds[1], GPIO_OUTPUT);
    board_leds[0] = gpio_pin(GPIO_PORTG, 12);
    gpio_setBitConfig(board_leds[0], GPIO_OUTPUT);
    board_leds[2] = gpio_pin(GPIO_PORTG, 14);
    gpio_setBitConfig(board_leds[2], GPIO_OUTPUT);

    board_buttons[0] = gpio_pin(GPIO_PORTG, 11);
    gpio_setBitConfig(board_buttons[0], GPIO_INPUT);
    board_buttons[1] = gpio_pin(GPIO_PORTF, 13);
    gpio_setBitConfig(board_buttons[1], GPIO_INPUT);
    board_buttons[2] = gpio_pin(GPIO_PORTF, 12);
    gpio_setBitConfig(board_buttons[2], GPIO_INPUT);*/
    
    //TRISAbits.TRISA8 = 0;

    return 0;
}

int board_init(void)
{
    sysclock_setSourceFreq(SYSCLOCK_SRC_POSC, 24000000); // 24MHz
    archi_init();

    board_init_io();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if(led >= LED_COUNT)
        return -1;

    switch (led)
    {
    case 0:
        break;
    case 1:
#ifndef SIMULATOR
        if (state & 1)
            LED2 = 1;
        else
            LED2 = 0;
#endif
        break;
    }
    return 0;
}

int board_toggleLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    gpio_toggleBit(board_leds[led]);
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;

    return gpio_readBit(board_leds[led]);
}

int8_t board_getButton(uint8_t button)
{
    GPIO_VALUE value;
    if(button >= BUTTON_COUNT)
        return -1;

    value = gpio_readBit(board_buttons[button]);
    if (value == GPIO_HIGH)
        return 0;
    return 1;
}
