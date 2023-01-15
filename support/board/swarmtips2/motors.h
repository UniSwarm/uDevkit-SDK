/**
 * @file motor.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date April 15, 2017, 01:16 AM
 *
 * @brief Code for swarmtips2 from Robotips
 */

#ifndef MOTORS_H
#define MOTORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void motors_init(void);
void motors_task(void);

// coders
int getC1(void);
int getC2(void);

// motors_init
void motors_start(void);
void motors_stop(void);

typedef enum
{
    Motors_State_Stop,
    Motors_State_Linear,
    Motors_State_Rotate
} Motors_State;

void motors_moveForward(int16_t distance);  // mm
void motors_rotate(int16_t angle);          // deg

void motors_setSpeed(int16_t speed);
Motors_State motors_state(void);

#ifdef __cplusplus
}
#endif

#endif  // MOTORS_H
