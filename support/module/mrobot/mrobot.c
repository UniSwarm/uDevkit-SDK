#include "mrobot.h"

#include "asserv/asserv.h"
#include <driver/motor.h>

#include <math.h>
#define M_PI 3.14159265358979323846

int16_t mrobot_lastSpeed = 0;

void mrobot_init(void)
{
#ifndef SIMULATOR
    asserv_init();
    motor_init();
#endif
}

void mrobot_setCoderDev(rt_dev_t leftCoder_dev, rt_dev_t rightCoder_dev)
{
    asserv_setCoderDev(leftCoder_dev, rightCoder_dev);
}

void mrobot_setCoderWay(uint8_t leftCoder_way, uint8_t rightCoder_way)
{
    // TODO
}

void mrobot_setCoderGeometry(float entrax, float stepLength)
{
    asserv_setCoderGeometry(entrax, stepLength);
}

void mrobot_setPose(MrobotPose pose)
{
    asserv_setPos(pose.x, pose.y, pose.t);
}

void mrobot_setMotorDev(rt_dev_t leftMotor_dev, rt_dev_t rightMotor_dev)
{
    // TODO
}

void mrobot_setMotorWay(uint8_t leftMotor_way, uint8_t rightMotor_way)
{
    // TODO
}

void mrobot_setMotorPid(int16_t kp, int16_t ki, int16_t kd)
{
    asserv_setPid(kp, ki, kd);
}

int16_t mrobot_motorGetP(void)
{
    return asserv_getP();
}

int16_t mrobot_motorGetI(void)
{
    return asserv_getI();
}

int16_t mrobot_motorGetD(void)
{
    return asserv_getD();
}

void mrobot_pause(void)
{
    asserv_setSpeed(0);
}

void mrobot_restart(void)
{
    asserv_setSpeed(mrobot_lastSpeed);
}

void mrobot_stop(void)
{
    asserv_setDest(asserv_getXPos(), asserv_getXPos());
}

void mrobot_goto(MrobotPoint pos, int16_t speed)
{
    mrobot_lastSpeed = speed;
    asserv_setDest(pos.x, pos.y);
    asserv_setSpeed(speed);
    asserv_setMode(Asserv_Mode_Linear);
}

void mrobot_move(MrobotPoint movement, int16_t speed)
{
    MrobotPoint pointGlobal;
    mrobot_lastSpeed = speed;
    pointGlobal = mapToGlobal(movement);
    mrobot_goto(pointGlobal, speed);
}

MrobotPoint mapToGlobal(MrobotPoint pointLocal)
{
    MrobotPoint pointGlobal;
    MrobotPose pose = mrobot_pose();
    float mcos = cos(pose.t);
    float msin = sin(pose.t);
    pointGlobal.x = pointLocal.x * mcos - pointLocal.y * msin + pose.x;
    pointGlobal.y = pointLocal.x * msin + pointLocal.y * mcos + pose.y;
    return pointGlobal;
}

MrobotPoint mapToLocal(MrobotPoint pointGlobal)
{
    MrobotPoint pointLocal;
    MrobotPose pose = mrobot_pose();
    float mcos = cos(-pose.t);
    float msin = sin(-pose.t);
    pointLocal.x = pointLocal.x * mcos - pointLocal.y * msin - pose.x;
    pointLocal.y = pointLocal.x * msin + pointLocal.y * mcos - pose.y;
    return pointLocal;
}

MrobotPose mrobot_pose(void)
{
    MrobotPose pose;
    pose.x = asserv_getXPos();
    pose.y = asserv_getYPos();
    pose.t = asserv_getTPos();
    return pose;
}

MrobotPoint mrobot_nextKeypoint(void)
{
    MrobotPoint point;
    point.x = asserv_xDest();
    point.y = asserv_yDest();
    return point;
}

float mrobot_nextKeypointDistance(void)
{
    return asserv_getDistance();
}

float mrobot_speed(void)
{
    return asserv_currentSpeed() * asserv_stepLength() * 1000.0;
}

float mrobot_targetSpeed(void)
{
    return mrobot_lastSpeed * asserv_stepLength() * 1000.0;
}
