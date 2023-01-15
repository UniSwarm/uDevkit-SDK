/**
 * @file cmd_led.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Leds commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include "board.h"

int cmd_led(int argc, char **argv)
{
    char ledid = 255;
    char status = 0;

    if (argc < 2)
    {
        return -1;
    }

    // first arg numeric : convert to ledid
    ledid = atoi(argv[1]);
    if (ledid >= LED_COUNT)
    {
        puts("Invalid led id");
        return -1;
    }

    // if no more arg, print status of led
    // led status > led <led-id>
    if (argc == 2)
    {
        status = board_getLed(ledid);
        if (status == 1)
        {
            puts("LED is on");
        }
        else
        {
            puts("LED is off");
        }

        return 0;
    }

    // led on or led off > led <led-id> <0-1>
    if (argv[2][0] == '1')
    {
        status = 1;
    }
    else
    {
        status = 0;
    }

    if (board_setLed(ledid, status) == 0)
    {
        puts("ok");
    }
    else
    {
        puts("invalid");
    }

    return 0;
}
