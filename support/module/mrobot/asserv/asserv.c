/**
 * @file asserv_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 15:10
 *
 * @brief Support for motor control with positionning
 */

#include <archi.h>

#include "board.h"
#include "asserv.h"

#include "driver/qei.h"
#include "driver/motor.h"
#include "driver/timer.h"

#include <stdio.h>
#include <string.h>

rt_dev_t asserv_timer;

#include <math.h>
#define M_PI        3.14159265358979323846

#define ANGLE_MAX	M_PI/10
#define ERR_MINI 100
#define PWM_MINI 100
#define PWM_MAX  800

unsigned char asserv_stop = 0;

Asserv_State masserv_state = Asserv_State_Stopped;

Asserv_Mode masserv_mode = Asserv_Mode_Stop;
float dt,ds,tand;
float asserv_x = 1500, asserv_y = 1000, asserv_t = 0;
int32_t asserv_xf = 1500, asserv_yf = 1000;
int16_t asserv_mspeed = 10;

typedef enum {
    Asserv_Way_Forward,
    Asserv_Way_Back
} Asserv_Way;
Asserv_Way asserv_way = Asserv_Way_Forward;

float distance = 0, angle = 0;
int16_t asserv_kd = -0, asserv_ki = 0, asserv_kp = 45;

// loc variables
rt_dev_t coder1;
rt_dev_t coder2;
float asserv_loc_coderentrax = 100;
float asserv_loc_coderstep = 1;
float last_t = 0, td = 0;
float xr, yr;

long int ancv1 = 0, ancv2 = 0;
long int ancc1 = 0, ancc2 = 0;
long int v1, v2;

void asserv_task();
void asserv_locTask();
void asserv_controlTask();

int asserv_init(void)
{
    asserv_timer = timer_getFreeDevice();
    timer_setPeriodMs(asserv_timer, 1);
    timer_setHandler(asserv_timer, asserv_task);
    timer_enable(asserv_timer);

    return 0;
}

void asserv_setCoderGeometry(float entrax, float stepLength)
{
    asserv_loc_coderentrax = entrax;
    asserv_loc_coderstep = stepLength;
}

float asserv_entrax(void)
{
    return asserv_loc_coderentrax;
}

float asserv_stepLength(void)
{
    return asserv_loc_coderstep;
}

void asserv_setCoderDev(rt_dev_t leftCoder_dev, rt_dev_t rightCoder_dev)
{
    coder1 = leftCoder_dev;
    qei_setConfig(coder1, 0);
    qei_enable(coder1);

    coder2 = rightCoder_dev;
    qei_setConfig(coder2, 0);
    qei_enable(coder2);
}

void asserv_task(void)
{
    asserv_locTask();
    asserv_controlTask();
}

long int c1, c2;
void asserv_locTask(void)
{
    c1 = qei_getValue(coder1);
    c2 = qei_getValue(coder2);

    // loc
    v1 = c1 - ancc1;
    v2 = - c2 + ancc2;

    dt = atan((v2 - v1) * asserv_loc_coderstep / asserv_loc_coderentrax);
    ds = (v1 + v2) * (asserv_loc_coderstep / 2);
    asserv_x += ds * cos(asserv_t+dt*.5);
    asserv_y -= ds * sin(asserv_t+dt*.5);
    asserv_t -= dt;
    if(asserv_t > M_PI)
        asserv_t -= 2*M_PI;
    if(asserv_t < -M_PI)
        asserv_t += 2*M_PI;

    ancc1 = c1;
    ancc2 = c2;
    ancv1 = v1;
    ancv2 = v2;
}

void asserv_setDest(int32_t x, int32_t y)
{
    asserv_xf = x;
    asserv_yf = y;
}

int32_t asserv_xDest(void)
{
    return asserv_xf;
}

int32_t asserv_yDest(void)
{
    return asserv_yf;
}

void asserv_setSpeed(int16_t speed)
{
    if(speed >= 0)
    {
        asserv_way = Asserv_Way_Forward;
        asserv_mspeed = speed;
    }
    else
    {
        asserv_way = Asserv_Way_Back;
        asserv_mspeed = -speed;
    }
}

int16_t asserv_speed(void)
{
    if(asserv_way == Asserv_Way_Back)
        return -asserv_mspeed;
    else
        return asserv_mspeed;
}

int16_t asserv_currentSpeed(void)
{
    return (v1 + v2) / 2;
}

void asserv_setPid(uint16_t kp, uint16_t ki, uint16_t kd)
{
    asserv_kp = kp;
    asserv_ki = ki;
    asserv_kd = kd;
}

uint16_t asserv_getP(void)
{
    return asserv_kp;
}

uint16_t asserv_getI(void)
{
    return asserv_ki;
}

uint16_t asserv_getD(void)
{
    return asserv_kd;
}

Asserv_State asserv_state(void)
{
    return masserv_state;
}

void asserv_setMode(Asserv_Mode mode)
{
	masserv_mode = mode;
}

int i = 0;
void asserv_controlTask(void)
{
    float consds, consdt;
    float consV1, consV2;
    float errp1, errd1;
    float errp2, errd2;
    short err1, err2;
    long int ev1, ev2;

    distance = sqrt((asserv_x - asserv_xf)*(asserv_x - asserv_xf) + (asserv_y-asserv_yf) * (asserv_y - asserv_yf));

// FSM
    switch(masserv_mode)
    {
    case Asserv_Mode_Stop:                                                  // =================== Stop
        consds = 0.0;
        consdt = 0.0;
        break;

    case Asserv_Mode_Fixe:                                                  // =================== Fixe
        // distance reference
        consds = distance / 10;
        if(consds > asserv_mspeed)
            consds = asserv_mspeed;

        // angle reference
        if(asserv_y - asserv_yf <= 0)
        {
            if(asserv_x - asserv_xf <= 0)
                consdt = asin((asserv_yf - asserv_y) / distance);
            else
                consdt = -M_PI - asin((asserv_yf - asserv_y) / distance);
        }
        else
        {
            if(asserv_x - asserv_xf <= 0)
                consdt = asin((asserv_yf - asserv_y) / distance);
            else
                consdt = M_PI - asin((asserv_yf - asserv_y) / distance);
        }
        consdt = -consdt-asserv_t;
        if(consdt >= M_PI / 2 || consdt <= -M_PI / 2)
        {
            //consdt = M_PI-consdt;
            consds = -consds;
            if((consdt <= 3 * M_PI / 8) & (consdt >= -3 * M_PI / 8))
                consds = 0;
        }
        else
        {
            if(consdt >= M_PI/8 || consdt <= -M_PI / 8)
                consds = 0;
        }
        consdt = last_t - asserv_t;
        if(consdt > M_PI)
            consdt -= 2 * M_PI;
        if(consdt < -M_PI)
            consdt += 2 * M_PI;

        consdt /= 2.0;
        if(distance > 40.0)
            masserv_mode = Asserv_Mode_Linear;

        break;
    case Asserv_Mode_Linear:                                                // =================== Linear
        // distance reference
        consds = distance / 40;
        if(consds > asserv_mspeed)
            consds = asserv_mspeed;

        // angle reference
        if(asserv_y - asserv_yf <= 0)
        {
            if(asserv_x - asserv_xf <= 0)
                angle = asin((asserv_yf - asserv_y) / distance);
            else
                angle = -M_PI - asin((asserv_yf - asserv_y) / distance);
        }
        else
        {
            if(asserv_x - asserv_xf <= 0)
                angle = asin((asserv_yf - asserv_y) / distance);
            else
                angle = M_PI - asin((asserv_yf - asserv_y) / distance);
        }

        consdt = -angle - asserv_t;
        if(consdt > M_PI)
            consdt -= 2 * M_PI;
        if(consdt < -M_PI)
            consdt += 2 * M_PI;

        if(asserv_way == Asserv_Way_Back)
        {
            consds = -consds;
            consdt = consdt + M_PI;
            if(consdt > M_PI)
                consdt -= 2 * M_PI;
            if(consdt < -M_PI)
                consdt += 2 * M_PI;
        }

        if(distance<20.0)
        {
            masserv_mode = Asserv_Mode_Fixe;
            last_t = asserv_t;
        }
        else if(consdt > ANGLE_MAX || consdt < -ANGLE_MAX)
        {
            masserv_mode = Asserv_Mode_Rotate;
            xr = asserv_x;
            yr = asserv_y;
            if(asserv_way == Asserv_Way_Back)
                td = angle + M_PI;
            else
                td = angle;
        }
        consdt /= 5.0;

        break;
    case Asserv_Mode_Rotate:                                                // =================== Rotate
        // distance reference
        consds = 0;

        // angle reference
        consdt = -td - asserv_t;
        if(consdt >  M_PI)
            consdt -= 2 * M_PI;
        if(consdt < -M_PI)
            consdt += 2 * M_PI;

        if((consdt < ANGLE_MAX) && (consdt > -ANGLE_MAX))
            masserv_mode = Asserv_Mode_Linear;
        break;
    }

    if(consdt > M_PI)
        consdt -= 2 * M_PI;
    if(consdt < -M_PI)
        consdt += 2 * M_PI;

    // compute motor command
    tand = (asserv_loc_coderentrax * tan(consdt)) / (asserv_loc_coderstep * 20);
    if(consdt >= M_PI / 2)
        tand = asserv_mspeed;
    if(consdt <= -M_PI / 2)
        tand = -asserv_mspeed;
    if(tand > asserv_mspeed / 2)
        tand = asserv_mspeed / 2;
    if(tand < -asserv_mspeed / 2)
        tand = -asserv_mspeed / 2;
    consV1 = consds - tand;
    consV2 = consds + tand;

    // pid motor 1
    ev1 = v1;
    if(consV1 > 0 && v1 > consV1)
        ev1 = consV1;
    if(consV1 < 0 && v1 < consV1)
        ev1 = consV1;
    errp1 = asserv_kp * consV1;
    errd1 = asserv_kd * (ev1 - consV1);
    err1 = (short)errp1 + (short)errd1;
    if(err1 > PWM_MAX)
        err1 = PWM_MAX;
    if(err1 < -PWM_MAX)
        err1 = -PWM_MAX;
    if(err1 > -ERR_MINI && err1 < ERR_MINI)
        err1 = 0;

    // pid motor 2
    ev2 = v2;
    if(consV2 > 0 && v2 > consV2)
        ev2 = consV2;
    if(consV2 < 0 && v2 < consV2)
        ev2 = consV2;
    errp2 = asserv_kp * consV2;
    errd2 = asserv_kd * (ev2 - consV2);
    err2 = (short)errp2 + (short)errd2;
    if(err2 > PWM_MAX)
        err2 = PWM_MAX;
    if(err2 < -PWM_MAX)
        err2 = -PWM_MAX;
    if(err2 > -ERR_MINI && err2 < ERR_MINI)
        err2 = 0;

    // prevent reverse
    if(consds > 5.0)
    {
        if(err1 < 0)
            err1 = 0;
        if(err2 < 0)
            err2 = 0;
    }
    if(consds < -5)
    {
        if(err1 > 0)
            err1 = 0;
        if(err2 > 0)
            err2 = 0;
    }

    // motors commands
    if(asserv_stop != 0)
    {
        motor_setPower(1, 0);
        motor_setPower(2, 0);
    }
    else
    {
        if(err1 > 0)
            motor_setPower(1, err1 + PWM_MINI);
        if(err1 < 0)
            motor_setPower(1, err1 - PWM_MINI);
        if(err1 == 0)
            motor_setPower(1, 0);

        if(err2 > 0)
            motor_setPower(2, -err2 - PWM_MINI);
        if(err2 < 0)
            motor_setPower(2, -err2 + PWM_MINI);
        if(err2 == 0)
            motor_setPower(2, 0);
    }
}

void asserv_setPos(float x, float y, float t)
{
    asserv_x = x;
    asserv_y = y;
    asserv_t = t;
    td = asserv_t;
}

float asserv_getXPos(void)
{
    return asserv_x;
}

float asserv_getYPos(void)
{
    return asserv_y;
}

float asserv_getTPos(void)
{
    return asserv_t;
}

float asserv_getDistance(void)
{
    return distance;
}
