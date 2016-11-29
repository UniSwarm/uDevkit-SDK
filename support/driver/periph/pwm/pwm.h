/**
 * @file pwm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 20, 2016, 12:33 PM
 *
 * @brief PWM support driver
 */

#ifndef PWM_H
#define PWM_H

#include "driver/device.h"

// ====== device assignation ======
rt_dev_t pwm_getFreeDevice();
void pwm_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int pwm_enable(rt_dev_t device);
int pwm_disable(rt_dev_t device);

// ======== device control ========
int pwm_setFreq(rt_dev_t device, uint32_t period);
uint32_t pwm_freq(rt_dev_t device);
uint32_t pwm_freqVal(rt_dev_t device);
int pwm_setDuty(rt_dev_t device, uint32_t period);
uint32_t pwm_duty(rt_dev_t device);

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24fv) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj)
 #include "pwm_pic24_dspic33.h"
#else
 #error Unsuported ARCHI
#endif

#endif // PWM_H
