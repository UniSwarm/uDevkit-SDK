/**
 * @file asserv.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date avril 28, 2016, 15:10
 *
 * @brief Support for motor control with positionning
 */

#ifndef ASSERV_H
#define ASSERV_H

#include "driver/device.h"

// ======= init and settings =======
int asserv_init(void);
void asserv_setCoderGeometry(float entrax, float stepLength);
float asserv_entrax(void);
float asserv_stepLength(void);
void asserv_setCoderDev(rt_dev_t leftCoder_dev, rt_dev_t rightCoder_dev);

void asserv_setPid(uint16_t kp, uint16_t ki, uint16_t kd);
uint16_t asserv_getP(void);
uint16_t asserv_getI(void);
uint16_t asserv_getD(void);
//void asserv_setMotors(void);

// ============ tasks ==============
void asserv_locTask(void);
void asserv_controlTask(void);

// ===== asserv control/status =====
typedef enum {
    Asserv_State_Stopped,
    Asserv_State_Blocked,
    Asserv_State_Moving,
    Asserv_State_Rotating
} Asserv_State;
Asserv_State asserv_state(void);
typedef enum
{
    Asserv_Mode_Stop,
    Asserv_Mode_Fixe,
    Asserv_Mode_Linear,
    Asserv_Mode_Rotate
} Asserv_Mode;
void asserv_setMode(Asserv_Mode mode);

void asserv_setDest(int32_t x, int32_t y);
int32_t asserv_xDest(void);
int32_t asserv_yDest(void);
float asserv_getDistance(void);
void asserv_setSpeed(int16_t speed);
int16_t asserv_speed(void);
int16_t asserv_currentSpeed(void);
// http://stackoverflow.com/questions/1472138/c-default-arguments

// ====== localisation status ======
void asserv_setPos(float x, float y, float t);
float asserv_getXPos(void);
float asserv_getYPos(void);
float asserv_getTPos(void);

#endif // ASSERV_H
