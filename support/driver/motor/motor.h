/**
 * @file motor.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 14:40  
 * 
 * @brief Support for motors control
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "driver/device.h"

int motor_init();

int motor_setPower(uint8_t motor, int16_t power);
int16_t motor_getCurrent(uint8_t motor);

#endif // MOTOR_H
