/**
 * @file pwm_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date May 10, 2017, 13:00 PM
 *
 * @brief PWM support driver for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 */

#ifndef PWM_PIC32_H
#define PWM_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

// !!! This implementation only support oc periph at the time
#include "driver/oc.h"

#define PWM_COUNT OC_COUNT

#ifdef __cplusplus
}
#endif

#endif  // PWM_PIC32_H
