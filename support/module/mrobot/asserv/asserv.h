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
void asserv_setCoderEntrax(float entrax);
void asserv_setCoderStep(float stepLenght);
void asserv_setCoders();

void asserv_setPid(uint16_t kp, uint16_t ki, uint16_t kd);
uint16_t asserv_getP();
uint16_t asserv_getI();
uint16_t asserv_getD();
//void asserv_setMotors();

// ============ tasks ==============
void asserv_locTask();
void asserv_controlTask();

// ===== asserv control/status =====
typedef enum {
    Asserv_State_Stopped,
    Asserv_State_Blocked,
    Asserv_State_Moving,
    Asserv_State_Rotating
} Asserv_State;
Asserv_State asserv_state();
typedef enum
{
    Asserv_Mode_Stop,
    Asserv_Mode_Fixe,
    Asserv_Mode_Linear,
    Asserv_Mode_Rotate
} Asserv_Mode;
void asserv_setMode(Asserv_Mode mode);

void asserv_goTo(int32_t x, int32_t y);
int32_t asserv_xDest();
int32_t asserv_yDest();
float asserv_getDistance();
void asserv_setSpeed(int16_t speed);
int16_t asserv_speed();
// http://stackoverflow.com/questions/1472138/c-default-arguments

// ====== localisation status ======
void asserv_setPos(float x, float y, float t);
float asserv_getXPos();
float asserv_getYPos();
float asserv_getTPos();

#endif // ASSERV_H
