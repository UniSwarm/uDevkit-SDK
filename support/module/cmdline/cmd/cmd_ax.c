
#include "driver/ax12.h"

#include "cmd_stdio.h"

int cmd_ax(int argc, char **argv)
{
    uint8_t axid = 255;
    uint16_t pos, speed = 512, torque = 512;

    if(argc < 2)
        return 1;

    // first arg numeric : convert to axid
    axid = atoi(argv[1]);

    // if no more arg, print properties of ax
    // > ax <ax-id>
    if(argc == 2)
    {
        // TODO read ax values when ax12 driver will be abble

        return 0;
    }

    // > ax <ax-id> <pos> [<speed>] [<torque>]
    pos = atoi(argv[2]);
    if(argc > 3)
        speed = atoi(argv[3]);
    if(argc > 4)
        torque = atoi(argv[4]);
    ax12_moveTo(axid, pos, speed, torque);
    puts("ok");

    return 0;
}
