#include "mrobot.h"

#include "asserv/asserv.h"
#include "driver/motor.h"

void mrobot_init()
{
    asserv_init();
    motor_init();
}
