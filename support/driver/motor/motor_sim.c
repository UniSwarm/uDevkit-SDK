/**
 * @file motor_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief Support for simulator motors control
 */

#include "motor_sim.h"
#include "driver/adc.h"

int motor_init(void)
{
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

    // TODO SIM

    return 0;
}

int16_t motor_getCurrent(rt_dev_t device)
{
    int16_t value = 0;
    uint8_t motor = MINOR(device);
    if (motor >= MOTOR_COUNT)
        return -1;

    // TODO SIM

    return (value * 13) >> 1;
}
