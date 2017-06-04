/**
 * @file swarmtips2.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 15, 2017, 01:16 AM
 *
 * @brief Code for swarmtips2 from Robotips
 */

#include "swarmtips2.h"

#include <archi.h>

#include <driver/i2c.h>
#include <driver/sysclock.h>

#include <module/sensor.h>

uint8_t board_led_state = 0;

#ifdef SIMULATOR
#include <stdio.h>
#endif

rt_dev_t swarmtips2_i2c_tof;
rt_dev_t swarmtips2_i2c_ihm;

int board_init_io()
{
#ifndef SIMULATOR
    int i;

    // analog inputs
    ANSELB = 0x8000;    // all analog inputs of port B as digital buffer
                        //unless BOARD_VOLT_IN as analog
    ANSELE = 0x0000;    // all analog inputs of port E as digital buffer
    ANSELG = 0x0000;    // all analog inputs of port G as digital buffer

    OSC_EN = 1;
    TRISCbits.TRISC15 = 0;       // OSC_EN pin as output

    // digitals outputs
    TRISBbits.TRISB11 = 0;      // CHARGER_CE pin as output
    //TRISBbits.TRISB14 = 0;      // CHARGER_SYS pin as output
    CNPUBbits.CNPUB12 = 1; // pwgood
    CNPUBbits.CNPUB13 = 1; // charging

    TRISCbits.TRISC14 = 0;      // M1DIR pin as output
    TRISCbits.TRISC13 = 0;      // M2DIR pin as output
    TRISBbits.TRISB8 = 0;       // BOOST_SLEEP pin as output
    BOOST_SLEEP = 1;

    ESP8266_FLASH = 1;
    ESP8266_RST   = 0;
    TRISEbits.TRISE7 = 0;       // ESP8266_FLASH pin as output
    for(i=0;i<65000;i++);
    TRISEbits.TRISE5 = 0;       // ESP8266_RST pin as output

    for(i=0;i<65000;i++);
    ESP8266_RST   = 1;

    // buzzer
    LATBbits.LATB2 = 0;
    TRISBbits.TRISB2 = 0;       // buzzer default out off

    // acc
    ACC_CS = 1;
    //TRISDbits.TRISD2 = 0; //ACC_SD0
    TRISDbits.TRISD5 = 0; //ACC_CS
    //TRISDbits.TRISD3 = 0; //ACC_SCK
    
    // RGB led
    TRISEbits.TRISE6 = 0; // RBG_LED

    // remappable pins
    // Unlock configuration pin
    unlockIoConfig();

        // UART2 pins (esp8266 wifi)
        U2RXR = 0b0001;         // RX2 ==> RPG6
        RPG9R = 0b0010;         // TX2 ==> RPG9

        // OC PWM motors and buzzer
        RPB2R = 0b1100;  // OC1             // buzzer pwm tone
        RPF4R = 0b1011;  // OC3             // M1 pwm speed
        RPF5R = 0b1011;  // OC4             // M2 pwm speed
        RPB3R = 0b1100;  // OC7             // LED 3 intensity
        RPB7R = 0b1100;  // OC8             // LED 1 intensity
        RPB6R = 0b1101;  // OC9             // LED 2 intensity

    // Lock configuration pin
    lockIoConfig();
#endif
    return 0;
}

int board_init_ledpwm()
{
#ifndef SIMULATOR
    OC7CON = 0x0000;
    OC7R = 0;
    OC7RS = 0;
    OC7CON = 0x0006;// Configure for PWM mode without Fault pin
    OC7CONbits.OCTSEL = 1; // timer y
    OC7CONSET = 0x8000;// Enable OC7

    OC8CON = 0x0000;
    OC8R = 0;
    OC8RS = 0;
    OC8CON = 0x0006;// Configure for PWM mode without Fault pin
    OC8CONbits.OCTSEL = 1; // timer y
    OC8CONSET = 0x8000;// Enable OC8

    OC9CON = 0x0000;
    OC9R = 0;
    OC9RS = 0;
    OC9CON = 0x0006;// Configure for PWM mode without Fault pin
    OC9CONbits.OCTSEL = 1; // timer y
    OC9CONSET = 0x8000;// Enable OC9
#endif

    return 0;
}

int board_init_tof()
{
    int i;
    swarmtips2_i2c_tof = i2c(TOF_I2C_BUS);
    i2c_open(swarmtips2_i2c_tof);
    i2c_setBaudSpeed(swarmtips2_i2c_tof, I2C_BAUD_400K);
    i2c_enable(swarmtips2_i2c_tof);

    i2c_writereg(swarmtips2_i2c_tof, TOF_IOEXP_ADDR, 1, 0x00, 0); // leds off and disable tof 2 and tof 3
    i2c_writereg(swarmtips2_i2c_tof, TOF_IOEXP_ADDR, 3, 0x00, 0); // all io as output

    // tof1
    VL6180X_setAddr(swarmtips2_i2c_tof, 0x52, TOF1_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(swarmtips2_i2c_tof, TOF1_ADDR);

    // tof2
    i2c_writereg(swarmtips2_i2c_tof, TOF_IOEXP_ADDR, 1, 0x01, 0); // enable tof 2
    for(i=0;i<65000;i++);
    VL6180X_setAddr(swarmtips2_i2c_tof, 0x52, TOF2_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(swarmtips2_i2c_tof, TOF2_ADDR);

    // tof3
    i2c_writereg(swarmtips2_i2c_tof, TOF_IOEXP_ADDR, 1, 0x03, 0); // enable tof 3
    for(i=0;i<65000;i++);
    VL6180X_setAddr(swarmtips2_i2c_tof, 0x52, TOF3_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(swarmtips2_i2c_tof, TOF3_ADDR);

    return 0;
}

rt_dev_t board_i2c_tof()
{
    return swarmtips2_i2c_tof;
}

rt_dev_t board_i2c_ihm()
{
    return swarmtips2_i2c_ihm;
}

int board_init_buzzer()
{
#ifndef SIMULATOR
    OC1CON = 0x0000;// Turn off the OC1 when performing the setup
    OC1R = 0x0064;// Initialize primary Compare register
    OC1RS = 0x0064;// Initialize secondary Compare register
    PR2 = 0x00C7; // Set period
    OC1CON = 0x0006;// Configure for PWM mode without Fault pin // enabled

    T2CON = 0x8030;// Enable Timer2
    //OC1CONSET = 0x8000;// Enable OC1
#endif

    return 0;
}

void board_buzz(uint16_t freq)
{
#ifndef SIMULATOR
    if(freq > 0)
    {
        OC1R = freq/2;// Initialize primary Compare register
        OC1RS = freq/2;// Initialize secondary Compare register
        PR2 = freq; // Set period
        OC1CON = 0x0006;
        OC1CONSET = 0x8000;// Enable OC1
    }
    else
    {
        OC1CON = 0x0000;
        OC1CONCLR = 0x8000;// Disable OC1
    }
#endif
}

int board_init_ihm()
{
    // i2c ihm board
    swarmtips2_i2c_ihm = i2c(IHM_I2C_BUS);
    i2c_open(swarmtips2_i2c_ihm);
    i2c_setBaudSpeed(swarmtips2_i2c_ihm, I2C_BAUD_400K);
    i2c_enable(swarmtips2_i2c_ihm);

    i2c_writereg(swarmtips2_i2c_ihm, IHM_IOEXP_ADDR, 3, 0x0E, 0); // led IHM as output
    i2c_writereg(swarmtips2_i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM off

    return 0;
}

uint8_t board_button(uint8_t btn)
{
    uint8_t value;
    int ret;
    if (btn > 2)
        return 0;
    ret = i2c_readregs(swarmtips2_i2c_ihm, IHM_IOEXP_ADDR, 0, &value, 1, 0);
    if (ret != 0)
        return 0;
    switch (btn)
    {
    case 0:
        if ((value & IHM_BTN1_MASK) == 0)
            return 1;
        return 0;
    case 1:
        if ((value & IHM_BTN2_MASK) == 0)
            return 1;
        return 0;
    case 2:
        if ((value & IHM_BTN3_MASK) == 0)
            return 1;
        return 0;
    }
}

float board_getPowerVoltage()
{
    uint16_t value = adc_getValue(BOARD_VOLT_IN);
    return ((float)value) / 4096.0 * 6.6;
}

int board_init()
{
    init_archi();

    board_init_io();

    sysclock_setClock(24000000); // 24MHz
    sysclock_switchSourceTo(SYSCLOCK_SRC_POSC);

    board_init_tof();
    board_init_buzzer();
    board_init_ihm();
    board_init_ledpwm();
    
    adc_init();

    return 0;
}

int board_setLed(uint8_t led, uint8_t state)
{
    if (led >= LED_COUNT)
        return -1;
#ifndef SIMULATOR
    switch(led)
    {
    case 0:
        OC8R = state<<1;
        OC8RS = state<<1;
        break;
    case 1:
        OC9R = state<<1;
        OC9RS = state<<1;
        break;
    case 2:
        OC7R = state<<1;
        OC7RS = state<<1;
        break;
    case 3:
        if (state != 0)
            board_led_state |= 0x01;
        else
            board_led_state &= 0xFE;
        break;
    case 4:
        if (state != 0)
            board_led_state |= 0x02;
        else
            board_led_state &= 0xFD;
        break;
    case 5:
        if (state != 0)
        {
            board_led_state |= 0x04;
            i2c_writereg(swarmtips2_i2c_ihm, IHM_IOEXP_ADDR, 1, 1, 0); // led IHM off
        }
        else
        {
            board_led_state &= 0xFB;
            i2c_writereg(swarmtips2_i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM on
        }
        break;
    }

    if (led == 3 || led == 4)
        i2c_writereg(swarmtips2_i2c_tof, TOF_IOEXP_ADDR, 1, board_led_state << 2 | 0x03, 0);
#else
    if(state & 0x01)
    {
        //printf("LED %d on\n", led);
        board_led_state |= (1 << led);
    }
    else
    {
        //printf("LED %d off\n", led);
        board_led_state &= !(1 << led);
    }
#endif
    return 0;
}

int8_t board_getLed(uint8_t led)
{
    if(led >= LED_COUNT)
        return -1;
#ifndef SIMULATOR
    switch(led)
    {
    case 0:
        return OC8R>>1;
    case 1:
        return OC9R>>1;
    case 2:
        return OC7R>>1;
    case 3:
        return ((board_led_state & 0x01) == 1);
    case 4:
        return ((board_led_state & 0x02) == 1);
    case 5:
        return ((board_led_state & 0x04) == 1);
    }
    return 0;
#else
    return board_led_state & (!(1 << led));
#endif
}
