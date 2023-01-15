/**
 * @file mrobot.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date November 07, 2016, 23:10
 *
 * @brief Support for mobile robot
 */

#ifndef MROBOT_H
#define MROBOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/device.h"

// #include "asserv/asserv.h"

void mrobot_init(void);

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
void mrobot_setCoderGeometry(float entrax, float stepLength);
void mrobot_setPose(MrobotPose pose);

// motors control
void mrobot_setMotorDev(rt_dev_t leftMotor_dev, rt_dev_t rightMotor_dev);
void mrobot_setMotorWay(uint8_t leftMotor_way, uint8_t rightMotor_way);
void mrobot_setMotorPid(int16_t kp, int16_t ki, int16_t kd);
int16_t mrobot_motorGetP(void);
int16_t mrobot_motorGetI(void);
int16_t mrobot_motorGetD(void);

// ===== pos / movements =====
// commands
void mrobot_pause(void);
void mrobot_restart(void);
void mrobot_stop(void);
void mrobot_goto(MrobotPoint pos, int16_t speed);       // global reference frame
void mrobot_move(MrobotPoint movement, int16_t speed);  // local (robot) reference frame
MrobotPoint mapToGlobal(MrobotPoint pos);
MrobotPoint mapToLocal(MrobotPoint pos);

// status
MrobotPose mrobot_pose(void);
MrobotPoint mrobot_nextKeypoint(void);
float mrobot_nextKeypointDistance(void);
float mrobot_speed(void);
float mrobot_targetSpeed(void);

#ifdef __cplusplus
}
#endif

#endif  // MROBOT_H
