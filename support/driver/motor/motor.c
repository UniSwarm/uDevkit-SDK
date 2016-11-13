/**
 * @file motor_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 14:40
 *
 * @brief Support for motors control
 */

#include <xc.h>

#include "motor.h"
#include "driver/adc.h"

// <TODO replace theses functions by pwm support
#ifdef M1A
void setup_PWM1(void)
{
    M1A=0;
    M1B=0;
    OC1CON1 = 0b0001110000000110;
    OC1CON2 = 0b0000000000011111;
    OC1R = 0;
    OC1RS = 1500;   // 20kz
}
#endif
#ifdef M2A
void setup_PWM2(void)
{
    M2A=0;
    M2B=0;
    OC2CON1 = 0b0001110000000110;
    OC2CON2 = 0b0000000000011111;
    OC2R = 0;
    OC2RS = 1500;   // 20kz
}
#endif
#ifdef M3A
void setup_PWM3(void)
{
    M3A=0;
    M3B=0;
    OC3CON1 = 0b0001110000000110;
    OC3CON2 = 0b0000000000011111;
    OC3R = 0;
    OC3RS = 1500;   // 20kz
}
#endif
#ifdef M4A
void setup_PWM4(void)
{
    M4A=0;
    M4B=0;
    OC4CON1 = 0b0001110000000110;
    OC4CON2 = 0b0000000000011111;
    OC4R = 0;
    OC4RS = 1500;   // 20kz
}
#endif
// TODO/>

int motor_init()
{
#ifdef M1A
    setup_PWM1();
#endif
#ifdef M2A
    setup_PWM2();
#endif
#ifdef M3A
    setup_PWM3();
#endif
#ifdef M4A
    setup_PWM4();
#endif

    return 0;
}

int motor_setPower(rt_dev_t device, int16_t power)
{
    int16_t pwm = power;
    uint8_t motor = MINOR(device);
    if (motor >= MOTOR_COUNT)
        return -1;

    if(pwm>1500)
        pwm = 1500;
    if(pwm<-1500)
        pwm = -1500;

    switch(motor)
    {
#ifdef M1A
    case 1:
        if(pwm>0)
        {
            M1A=0;
            M1B=1;
            OC1R = pwm;
        }
        else
        {
            M1A=1;
            M1B=0;
            OC1R = -pwm;
        }
        break;
#endif
#ifdef M2A
    case 2:
        if(pwm>0)
        {
            M2A=0;
            M2B=1;
            OC2R = pwm;
        }
        else
        {
            M2A=1;
            M2B=0;
            OC2R = -pwm;
        }
        break;
#endif
#ifdef M3A
    case 3:
        if(pwm>0)
        {
            M3A=0;
            M3B=1;
            OC3R = pwm;
        }
        else
        {
            M3A=1;
            M3B=0;
            OC3R = -pwm;
        }
        break;
#endif
#ifdef M4A
    case 4:
        if(pwm>0)
        {
            M4A=0;
            M4B=1;
            OC4R = pwm;
        }
        else
        {
            M4A=1;
            M4B=0;
            OC4R = -pwm;
        }
        break;
#endif
    default:
        return -1;
    }

    return 0;
}

int16_t motor_getCurrent(rt_dev_t device)
{
    int8_t channel;
    int16_t value;
    uint8_t motor = MINOR(device);
    if (motor >= MOTOR_COUNT)
        return -1;

    switch(motor)
    {
#ifdef M1I
    case 1:
        channel = M1I;
        break;
#endif
#ifdef M2I
    case 2:
        channel = M2I;
        break;
#endif
#ifdef M3I
    case 3:
        channel = M3I;
        break;
#endif
#ifdef M4I
    case 4:
        channel = M4I;
        break;
#endif
    default:
        return -1;
    }

    value = adc_getValue(channel);
    return (value * 13) >> 1;
}
