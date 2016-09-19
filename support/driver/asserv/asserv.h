/**
 * @file asserv.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 15:10
 *
 * @brief Support for motor control with positionning
 */

#ifndef ASSERV_H
#define ASSERV_H

#include "driver/device.h"

// ======= init and settings =======
int asserv_init();
void asserv_setCoders();
//void asserv_setMotors();

// ============ tasks ==============
void asserv_locTask();
void asserv_controlTask();

// ====== localisation status ======
float asserv_getXPos();
float asserv_getYPos();
float asserv_getTPos();

#endif // ASSERV_H
