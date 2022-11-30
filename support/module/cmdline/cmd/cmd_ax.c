/**
 * @file cmd_ax.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief AX commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <driver/ax12.h>

int cmd_ax(int argc, char **argv)
{
    uint8_t axid = 255;
    uint16_t pos, speed = 512, torque = 512;

    if (argc < 2)
    {
        return -1;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        puts("ax <ax-id> move <pos> [<speed>] [<torque>]");
        puts("ax <ax-id> setled <0-1>");
        puts("ax <ax-id> setid <newid>");
        return 0;
    }

    // first arg numeric : convert to axid
    axid = atoi(argv[1]);

    // if no more arg, print properties of ax
    // > ax <ax-id>
    if (argc == 2)
    {
        // TODO read ax values when ax12 driver will be abble

        return 0;
    }

    if (argc < 4)
    {
        return -1;
    }
    pos = atoi(argv[3]);

    // > ax <ax-id> move <pos> [<speed>] [<torque>]
    if (strcmp(argv[2], "move") == 0)
    {
        if (argc > 4)
        {
            speed = atoi(argv[4]);
        }
        if (argc > 5)
        {
            torque = atoi(argv[5]);
        }
        ax12_moveTo(axid, pos, speed, torque);
        puts("ok");
    }

    // > ax <ax-id> setled <0:1>
    if (strcmp(argv[2], "setled") == 0)
    {
        ax12_setLed(axid, (uint8_t)pos);
        puts("ok");
    }

    // > ax <ax-id> setid <newid>
    if (strcmp(argv[2], "setid") == 0)
    {
        ax12_setId(axid, (uint8_t)pos);
        puts("ok");
    }

    return 0;
}
