/**
 * @file asserv_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 15:10
 *
 * @brief Support for motor control with positionning
 */

#include <xc.h>

#include "board.h"
#include "asserv.h"

#include "driver/qei.h"
#include "driver/motor.h"

#include <stdio.h>
#include <string.h>

// <TODO replace theses functions by time/tasks support
void setup_timer1()
{
    T1CON  = 0b1000000000100000;    // FCY / 64
    PR1 = 625;          // 1kHz
    IEC0bits.T1IE = 1;
}
// TODO/>

#include <math.h>
#define M_PI        3.14159265358979323846

#define ANGLE_MAX	M_PI/10
#define ERR_MINI 100
#define PWM_MINI 100
#define PWM_MAX  1500

unsigned char asserv_stop = 0;

Asserv_State masserv_state = Asserv_State_Stopped;

Asserv_Mode masserv_mode = Asserv_Mode_Stop;
float dt,ds,tand;
float asserv_x = 1500, asserv_y = 1000, asserv_t = 0;
int32_t xf = 1500, yf = 1000;
int16_t asserv_speed = 10;

typedef enum {
    Asserv_Way_Forward,
    Asserv_Way_Back
} Asserv_Way;
Asserv_Way asserv_way = Asserv_Way_Forward;

float distance = 0, angle = 0;
short kd1=0, ki1=0, kp1=10;
short kd2=0, ki2=0, kp2=10;

// loc variables
rt_dev_t coder1;
rt_dev_t coder2;
float asserv_loc_coderentrax = 100;
float asserv_loc_coderstep = 1;
float last_t=0, td=0;
float xr, yr;

long int ancv1=0,ancv2=0;
long int ancc1=0,ancc2=0;
long int v1,v2;

int asserv_init()
{
    coder1 = qei_getFreeDevice();
    qei_setConfig(coder1, 0);
    qei_enable(coder1);

    coder2 = qei_getFreeDevice();
    qei_setConfig(coder2, 0);
    qei_enable(coder2);

    setup_timer1();

    return 0;
}

void asserv_setCoderEntrax(float entrax)
{
    asserv_loc_coderentrax = entrax;
}

void asserv_setCoderStep(float stepLenght)
{
    asserv_loc_coderstep = stepLenght;
}

void asserv_locTask()
{
    static long int c1, c2;

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
}

void asserv_goTo(int32_t asserv_x, int32_t asserv_y)
{
    xf = asserv_x;
    yf = asserv_y;
}

void asserv_setSpeed(int16_t speed)
{
    if(speed >= 0)
    {
        asserv_way = Asserv_Way_Forward;
        asserv_speed = speed;
    }
    else
    {
        asserv_way = Asserv_Way_Back;
        asserv_speed = -speed;
    }

}

Asserv_State asserv_state()
{
    return masserv_state;
}

void asserv_setMode(Asserv_Mode mode)
{
	masserv_mode = mode;
}

int i = 0;
void asserv_controlTask()
{
    float consds, consdt;
    float consV1, consV2;
    float errp1, errd1;
    float errp2, errd2;
    short err1, err2;

    distance = sqrt((asserv_x - xf)*(asserv_x - xf) + (asserv_y-yf) * (asserv_y - yf));

// FSM
    switch(masserv_mode)
    {
    case Asserv_Mode_Stop:                                                  // =================== Stop
        consds = 0.0;
        consdt = 0.0;
        break;

    case Asserv_Mode_Fixe:                                                  // =================== Fixe
        // distance reference
        consds = distance / 4;
        if(consds > asserv_speed)
            consds = asserv_speed;

        // angle reference
        if(asserv_y - yf <= 0)
        {
            if(asserv_x - xf <= 0)
                consdt = asin((yf - asserv_y) / distance);
            else
                consdt = -M_PI - asin((yf - asserv_y) / distance);
        }
        else
        {
            if(asserv_x - xf <= 0)
                consdt = asin((yf - asserv_y) / distance);
            else
                consdt = M_PI - asin((yf - asserv_y) / distance);
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
        consds = distance / 4;
        if(consds > asserv_speed)
            consds = asserv_speed;

        // angle reference
        if(asserv_y - yf <= 0)
        {
            if(asserv_x - xf <= 0)
                angle = asin((yf - asserv_y) / distance);
            else
                angle = -M_PI - asin((yf - asserv_y) / distance);
        }
        else
        {
            if(asserv_x - xf <= 0)
                angle = asin((yf - asserv_y) / distance);
            else
                angle = M_PI - asin((yf - asserv_y) / distance);
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
        if(consds > asserv_speed)
            consds = asserv_speed;

        // angle reference
        consdt = -td - asserv_t;
        if(consdt >  M_PI)
            consdt -= 2 * M_PI;
        if(consdt < -M_PI)
            consdt += 2 * M_PI;

        if((consdt < ANGLE_MAX) & (consdt > -ANGLE_MAX))
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
        tand = asserv_speed;
    if(consdt <= -M_PI / 2)
        tand = -asserv_speed;
    if(tand > asserv_speed / 2)
        tand = asserv_speed / 2;
    if(tand < -asserv_speed / 2)
        tand = -asserv_speed / 2;
    consV1 = consds - tand;
    consV2 = consds + tand;

    // pid motor 1
    errp1 = kp1 * (consV1 - v1);
    errd1 = kd1 * ((consV1 - v1) - (consV1 - ancv1));
    err1 = (short)errp1 + (short)errd1;
    if(err1 > PWM_MAX)
        err1 = PWM_MAX;
    if(err1 < -PWM_MAX)
        err1 = -PWM_MAX;
    if(err1 > -ERR_MINI && err1 < ERR_MINI)
        err1 = 0;

    // pid motor 2
    errp2 = kp2 * (consV2 - v2);
    errd2 = kd2 * ((consV2 - v2) - (consV2 - ancv2));
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
            motor_setPower(1, err1/* + PWM_MINI*/);
        if(err1 < 0)
            motor_setPower(1, err1/* - PWM_MINI*/);
        if(err1 == 0)
            motor_setPower(1, 0);

        if(err2 > 0)
            motor_setPower(2, -err2/* + PWM_MINI*/);
        if(err2 < 0)
            motor_setPower(2, -err2/* - PWM_MINI*/);
        if(err2 == 0)
            motor_setPower(2, 0);
    }

    if(i++>100)
    {
        char buff[200];
        i=0;
        sprintf(buff, "d: %d ds: %d dt: %d err:%d cons:%d\n",
				(int)distance,
				(int)consds,
				(int)consdt,
				(int)err1,
				(int)consV1
                );
        usb_serial_write(buff, strlen(buff));
    }
}

// <TODO replace theses functions by time/tasks support
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(void)
{
    asserv_locTask();
    asserv_controlTask();
    LED = ~LED;

    IFS0bits.T1IF = 0;
}
// TODO/>

void asserv_setPos(float x, float y, float t)
{
    asserv_x = x;
    asserv_y = y;
    asserv_t = t;
}

float asserv_getXPos()
{
    return asserv_x;
}

float asserv_getYPos()
{
    return asserv_y;
}

float asserv_getTPos()
{
    return (180.0 * asserv_t / M_PI);
}
