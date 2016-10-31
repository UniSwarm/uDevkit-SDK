
#include "driver/asserv.h"

#include "cmd_stdio.h"

int cmd_asserv(int argc, char **argv)
{
    int16_t param1, param2, param3;
    // if no arg, print properties of asserv
    if(argc == 1)
    {
        printf("Pos: %.2f %.2f (mm) %f°\r\n",
            asserv_getXPos(),
            asserv_getYPos(),
            asserv_getTPos());
        printf("dest: %ld %ld dist %.2f (mm)\r\n",
            asserv_xDest(),
            asserv_yDest(),
            asserv_getDistance());
        printf("PID: %d %d %d\r\n",
            asserv_getP(),
            asserv_getI(),
            asserv_getD());
        printf("speed: %d\r\n",
            asserv_speed());

        return 0;
    }

    // parse argv 2
    if(argc < 3)
        return 1;
    param1 = atoi(argv[2]);
    // == setspeed > asserv setspeed <spedd>
    if(strcmp(argv[1], "setspeed")==0)
    {
        asserv_setSpeed(param1);
        puts("ok");
        return 0;
    }

    if(argc < 4)
        return 1;
    param2 = atoi(argv[3]);
    // == goto > asserv goto <xpos> <ypos>
    if(strcmp(argv[1], "goto")==0)
    {
        asserv_setMode(Asserv_Mode_Linear);
        asserv_goTo(param1, param2);
        puts("ok");
        return 0;
    }
    if(argc < 5)
        return 1;
    param3 = atoi(argv[4]);
    // == setpos > asserv setpos <xpos> <ypos> <tpos>
    if(strcmp(argv[1], "setpos")==0)
    {
        asserv_setPos(param1, param2, param3);
        puts("ok");
        return 0;
    }
    // == setpid > asserv setpid <p> <i> <d>
    if(strcmp(argv[1], "setpid")==0)
    {
        asserv_setPid(param1, param2, param3);
        puts("ok");
        return 0;
    }

    return 1;
}
