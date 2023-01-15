/**
 * @file pwm_pic24_dspic30f_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 20, 2016, 12:33 PM
 *
 * @brief PWM support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#ifndef PWM_PIC24_DSPIC30F_DSPIC33_H
#define PWM_PIC24_DSPIC30F_DSPIC33_H

#ifdef __cplusplus
extern "C" {
#endif

// !!! This implementation only support oc periph at the time
#include "driver/oc.h"

#define PWM_COUNT OC_COUNT

#ifdef __cplusplus
}
#endif

#endif  // PWM_PIC24_DSPIC30F_DSPIC33_H
