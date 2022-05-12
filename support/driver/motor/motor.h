/**
 * @file motor.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date avril 28, 2016, 14:40
 *
 * @brief Support for motors control
 */

#ifndef MOTOR_H
#define MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"
#include "driver/device.h"

int motor_init(void);

int motor_setPower(rt_dev_t device, int16_t power);
int16_t motor_getCurrent(rt_dev_t device);

#if defined(M4A)
#    define MOTOR_COUNT 4
#elif defined(M3A)
#    define MOTOR_COUNT 3
#elif defined(M2A)
#    define MOTOR_COUNT 2
#elif defined(M1A)
#    define MOTOR_COUNT 1
#else
#    define MOTOR_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_H
