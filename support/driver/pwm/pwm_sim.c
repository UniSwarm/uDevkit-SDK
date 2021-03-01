/**
 * @file pwm_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date May 10, 2017, 13:00 PM
 *
 * @brief PWM support for udevkit simulator
 */

#include "pwm.h"

#include "driver/timer.h"

// !!! This implementation only support oc periph at the time

struct pwm_dev
{
    uint32_t period;
    uint32_t freq;
    uint16_t duty;
};

struct pwm_dev pwms[PWM_COUNT];

rt_dev_t pwm_getFreeDevice(void)
{
    rt_dev_t dev = oc_getFreeDevice();
    if (dev != NULLDEV)
    {
        dev = MKDEV(DEV_CLASS_PWM, MINOR(dev));
    }
    return dev;
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
    rt_dev_t timer = oc_getTimer(device);
    timer_enable(timer);
    oc_setMode(device, OC_MODE_PWM);
    return oc_enable(device);
}

int pwm_disable(rt_dev_t device)
{
    return oc_disable(device);
}

int pwm_setFreq(rt_dev_t device, uint32_t freq)
{
#ifndef OC_HAVE_INDEPENDENT_TIMER
    int returnv;
    rt_dev_t timer = oc_getTimer(device);
    uint8_t pwm = MINOR(device);
    if (pwm >= PWM_COUNT)
    {
        return -1;
    }

    pwms[pwm].period = 1.0 / freq;

    return 0;
#else
    return 0;
#endif
}

uint32_t pwm_freq(rt_dev_t device)
{
    uint8_t pwm = MINOR(device);
    if (pwm >= PWM_COUNT)
    {
        return -1;
    }

    return pwms[pwm].freq;
}

uint32_t pwm_freqVal(rt_dev_t device)
{
    uint8_t pwm = MINOR(device);
    if (pwm >= PWM_COUNT)
    {
        return -1;
    }

    return pwms[pwm].period;
}

int pwm_setDuty(rt_dev_t device, uint16_t duty) // 1000 => 100%
{
    uint8_t pwm = MINOR(device);
    uint16_t dutyR;
    if (pwm >= PWM_COUNT)
    {
        return -1;
    }
    
    pwms[pwm].duty = duty;

    dutyR = pwms[pwm].period * duty / 1000;
    oc_setRVal(device, dutyR, dutyR);

    return 0;
}

uint32_t pwm_duty(rt_dev_t device)
{
    uint8_t pwm = MINOR(device);
    if (pwm >= PWM_COUNT)
    {
        return -1;
    }

    return pwms[pwm].duty;
}
