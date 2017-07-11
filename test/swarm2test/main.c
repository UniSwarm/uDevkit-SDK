#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "ihm.h"
#include "motors.h"

extern void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer);
extern const Fs_FilesList file_list;

extern int ihm_d1, ihm_d2, ihm_d3;

int main(void)
{
    unsigned int i, j;
    int16_t value;

    board_init();

    // module init
    network_init();
    web_server_setRestApi(rest_api_exec);
    web_server_setRootFS(&file_list);

    motors_init();

    for (j=0;j<5;j++)
        for (i=0;i<65000;i++);

    // screen test
    ihm_init();
    motors_setSpeed(600);
    motors_moveForward(200);

    while(1)
    {
        #ifdef SIMULATOR
            usleep(1000);
        #endif
        network_task();
        ihm_task();

        value = VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR);
        ihm_d1 = value;
        if (value < 55)
        {
            board_setLed(3, 1);
            if (motors_state() != Motors_State_Rotate)
                motors_rotate(-90);
        }
        else
            board_setLed(3, 0);

        value = VL6180X_getDistance(board_i2c_tof(), TOF2_ADDR);
        ihm_d2 = value;
        if (value < 35)
            motors_stop();
        else
        {
            motors_start();
            if (motors_state() != Motors_State_Rotate)
                motors_moveForward(100);
        }

        value = VL6180X_getDistance(board_i2c_tof(), TOF3_ADDR);
        ihm_d3 = value;
        if (value < 55)
        {
            board_setLed(4, 1);
            if (motors_state() != Motors_State_Rotate)
                motors_rotate(90);
        }
        else
            board_setLed(4, 0);
    }

    return 0;
}
