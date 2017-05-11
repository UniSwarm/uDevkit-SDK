/**
 * @file pwm_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 20, 2016, 12:33 PM
 *
 * @brief PWM support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#include "pwm.h"

// !!! This implementation only support oc periph at the time


rt_dev_t pwm_getFreeDevice()
{
    rt_dev_t dev = oc_getFreeDevice();
    if (dev != NULLDEV)
        dev = MKDEV(DEV_CLASS_PWM, MINOR(dev));
    return dev;;
}

int pwm_open(rt_dev_t device)
{
    return oc_open(device);
}

int pwm_close(rt_dev_t device)
{
    return oc_close(device);
}

int pwm_enable(rt_dev_t device)
{
    oc_setMode(device, OC_MODE_PWM);
    return oc_enable(device);
}

int pwm_disable(rt_dev_t device)
{
    return oc_disable(device);
}

int pwm_setFreq(rt_dev_t device, uint32_t period)
{
    return 0;
}

uint32_t pwm_freq(rt_dev_t device)
{
    return 0;
}

uint32_t pwm_freqVal(rt_dev_t device)
{
    return 0;
}

int pwm_setDuty(rt_dev_t device, uint16_t duty)
{
    return 0;
}

uint32_t pwm_duty(rt_dev_t device)
{
    return 0;
}
