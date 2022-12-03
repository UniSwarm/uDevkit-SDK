/**
 * @file pwm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date August 20, 2016, 12:33 PM
 *
 * @brief PWM support driver
 */

#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pwm_device.h"

// ====== device assignation ======
#define pwm(d) MKDEV(DEV_CLASS_PWM, (d)-1)
rt_dev_t pwm_getFreeDevice(void);
int pwm_open(rt_dev_t device);
int pwm_close(rt_dev_t device);

// ==== device enable/disable =====
int pwm_enable(rt_dev_t device);
int pwm_disable(rt_dev_t device);

// ======== device control ========
int pwm_setFreq(rt_dev_t device, uint32_t freq);
uint32_t pwm_freq(rt_dev_t device);
uint32_t pwm_freqVal(rt_dev_t device);
int pwm_setDuty(rt_dev_t device, uint16_t duty);
uint32_t pwm_duty(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // PWM_H
