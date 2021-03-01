/**
 * @file deltatips.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date September 23, 2016, 04:06 PM
 *
 * @brief Code for deltaTips robot from Robotips
 */

#include "deltatips.h"

#include "module/mrobot.h"
#include "driver/qei.h"
#include "driver/motor.h"

int robot_init(void)
{
    rt_dev_t leftCoder_dev, rightCoder_dev;

    board_init();

    leftCoder_dev = qei_getFreeDevice();
    rightCoder_dev = qei_getFreeDevice();
    mrobot_setCoderDev(leftCoder_dev, rightCoder_dev);
    mrobot_init();
    mrobot_setCoderGeometry(195.0,
                            0.00849123461395001864975755315181); // 72.5mm wheel / 28000 steps per rotate

    return 0;
}
