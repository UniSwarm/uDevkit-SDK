/**
 * @file mrobot.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 07, 2016, 23:10
 *
 * @brief Support for mobile robot
 */

#ifndef MROBOT_H
#define MROBOT_H

#include "driver/device.h"

//#include "asserv/asserv.h"

void mrobot_init();

typedef struct
{
    float x;
    float y;
} MrobotPoint;

typedef struct
{
    float x;
    float y;
    float t;
} MrobotPose;

// ======== settings ========
// coders, geometry, location
void mrobot_setCoderDev(rt_dev_t leftCoder_dev, rt_dev_t rightCoder_dev);
void mrobot_setCoderWay(uint8_t leftCoder_way, uint8_t rightCoder_way);
void mrobot_setCoderGeometry(float entrax, float stepLenght);
void mrobot_setPose(MrobotPose pose);

// motors control
void mrobot_setMotorDev(rt_dev_t leftMotor_dev, rt_dev_t rightMotor_dev);
void mrobot_setMotorWay(uint8_t leftMotor_way, uint8_t rightMotor_way);
void mrobot_setMotorPid(int16_t kp, int16_t ki, int16_t kd);
int16_t mrobot_motorGetP();
int16_t mrobot_motorGetI();
int16_t mrobot_motorGetD();

// ===== pos / movements =====
// commands
void mrobot_pause();
void mrobot_restart();
void mrobot_stop();
void mrobot_goto(MrobotPoint pos, int16_t speed);        // global reference frame
void mrobot_move(MrobotPoint movement, int16_t speed);   // local (robot) reference frame
MrobotPoint mapToGlobal(MrobotPoint pos);
MrobotPoint mapToLocal(MrobotPoint pos);

// status
MrobotPose mrobot_pose();
MrobotPoint mrobot_nextKeypoint();
float mrobot_nextKeypointDistance();
float mrobot_speed();
float mrobot_targetSpeed();


#endif // MROBOT_H
