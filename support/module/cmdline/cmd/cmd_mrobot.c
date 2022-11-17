/**
 * @file cmd_mrobot.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief MRobot module commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <module/mrobot.h>

int cmd_mrobot(int argc, char **argv)
{
    int16_t param1, param2, param3;
    // if no arg, print properties of mrobot
    if (argc == 1)
    {
        MrobotPose pose = mrobot_pose();
        printf("Pos: %.1f %.1f (mm) %.1f°\r\n", pose.x, pose.y, pose.t * 180.0 / 3.1415);
        MrobotPoint dest = mrobot_nextKeypoint();
        printf("dest: %.1f %.1f dist %.2f (mm)\r\n", dest.x, dest.y, mrobot_nextKeypointDistance());
        printf("PID: %d %d %d\r\n", mrobot_motorGetP(), mrobot_motorGetI(), mrobot_motorGetD());
        printf("speed: %.1f mm/s (target %.1f mm/s)\r\n", mrobot_speed(), mrobot_targetSpeed());

        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        puts("mrobot");
        puts("mrobot goto <xpos> <ypos> [<speed>]");
        puts("mrobot setpos <xpos> <ypos> <tpos>");
        puts("mrobot setpid <p> <i> <d>");
        return 0;
    }

    // parse argv 2, 3
    if (argc < 4)
    {
        return 1;
    }
    param1 = atoi(argv[2]);
    param2 = atoi(argv[3]);
    // == goto > mrobot goto <xpos> <ypos> [<speed>]
    if (strcmp(argv[1], "goto") == 0)
    {
        MrobotPoint pos;
        int16_t speed = 20;
        pos.x = param1;
        pos.y = param2;
        if (argc >= 5)
        {
            speed = atoi(argv[4]);
        }
        mrobot_goto(pos, speed);
        puts("ok");
        return 0;
    }
    if (argc < 5)
    {
        return 1;
    }
    param3 = atoi(argv[4]);
    // == setpos > mrobot setpos <xpos> <ypos> <tpos>
    if (strcmp(argv[1], "setpos") == 0)
    {
        MrobotPose pose;
        pose.x = param1;
        pose.y = param2;
        pose.t = param3;
        mrobot_setPose(pose);
        puts("ok");
        return 0;
    }
    // == setpid > mrobot setpid <p> <i> <d>
    if (strcmp(argv[1], "setpid") == 0)
    {
        mrobot_setMotorPid(param1, param2, param3);
        puts("ok");
        return 0;
    }

    return 1;
}
