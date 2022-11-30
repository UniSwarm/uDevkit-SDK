/**
 * @file cmdline.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Define a base for all commands
 */

#include "cmd.h"

#include "../cmdline_curses.h"
#include "cmds.h"

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <driver/device.h>

#include "modules.h"

static int _cmd_help(int argc, char **argv);

const Cmd _cmds[] = {
#ifdef USE_adc
    {"adc", cmd_adc},
#endif
#ifdef USE_ax12
    {"ax", cmd_ax},
#endif
#ifdef USE_can
    {"can", cmd_can},
#endif
#ifdef USE_gpio
    {"gpio", cmd_gpio},
#endif
    {"help", _cmd_help},
#ifdef USE_i2c
    {"i2c", cmd_i2c},
#endif
    {"led", cmd_led},
#ifdef USE_MODULE_mrobot
    {"mrobot", cmd_mrobot},
#endif
    {"reg", cmd_reg},
#ifdef USE_sysclock
    {"sysclock", cmd_sysclock},
#endif
#ifdef USE_uart
    {"uart", cmd_uart},
#endif
    {"", NULL}};

extern rt_dev_t _cmdline_device_out;

int (*_cmdline_cmdTaskPtr)(void) = NULL;

#define CMDLINE_ARGC_MAX 10

int cmd_exec(char *line)
{
    uint16_t i, argc;
    const Cmd *cmd;
    char *argv[CMDLINE_ARGC_MAX];
    char *sep;

    // parse line to argc argv
    sep = line;
    i = 1;
    argv[0] = sep;
    while (sep != NULL && i < CMDLINE_ARGC_MAX)
    {
        sep = strchr(sep, ' ');
        if (sep != 0)
        {
            *sep = '\0';
            if (*(sep + 1) != ' ' && *(sep + 1) != '\0')
            {
                argv[i++] = sep + 1;
            }
            sep++;
        }
        else
        {
            break;
        }
    }
    argc = i;

    // looking for command name
    cmd = NULL;
    for (i = 0; i < sizeof(_cmds); i++)
    {
        if (_cmds[i].cmdFnPtr == NULL)
        {
            break;
        }
        if (strcmp(_cmds[i].name, line) == 0)
        {
            cmd = &_cmds[i];
            break;
        }
    }

    // execute command if found
    if (cmd == NULL)
    {
        return INT_MIN;
    }
    return (*cmd->cmdFnPtr)(argc, argv);
}

int _cmd_help(int argc, char **argv)
{
    UDK_UNUSED(argc);
    UDK_UNUSED(argv);

    uint16_t i;
    for (i = 0; i < sizeof(_cmds); i++)
    {
        if (_cmds[i].cmdFnPtr == 0)
        {
            break;
        }
        cmd_puts(_cmds[i].name);
    }
    return 0;
}

void cmd_puts(const char *str)
{
    char cmd[10];
    device_write(_cmdline_device_out, str, strlen(str));
    device_write(_cmdline_device_out, "\n", 1);

    // move cursor 200 column before
    cmdline_curses_left(cmd, 200);
    device_write(_cmdline_device_out, cmd, strlen(cmd));
}

int cmd_printf(const char *format, ...)
{
    va_list arg;
    int done;
    char buff[100];

    va_start(arg, format);
    done = vsprintf(buff, format, arg);
    va_end(arg);

    device_write(_cmdline_device_out, buff, strlen(buff));
    device_write(_cmdline_device_out, "\r\n", 1);
    cmdline_curses_left(buff, 200);
    device_write(_cmdline_device_out, buff, strlen(buff));

    return done;
}

int cmd_task(void)
{
    if (_cmdline_cmdTaskPtr == NULL)
    {
        return 0;  // no command task active
    }

    if ((*_cmdline_cmdTaskPtr)() <= 0)
    {
        return 0;  // command task finished or crashed
    }
    return 1;
}

void cmd_setTask(int (*cmdTaskPtr)(void))
{
    _cmdline_cmdTaskPtr = cmdTaskPtr;
}
