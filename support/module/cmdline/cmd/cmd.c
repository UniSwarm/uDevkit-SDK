/**
 * @file cmdline.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Define a base for all commands
 */

#include "cmd.h"
#include "cmds.h"
#include "../cmdline_curses.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "driver/device.h"

#include "modules.h"

int cmd_help(int argc, char **argv);

Cmd cmds[] = {
  #ifdef USE_uart
    {"uart", cmd_uart},
  #endif
  #ifdef USE_sysclock
    {"sysclock", cmd_sysclock},
  #endif
  #ifdef USE_i2c
    {"i2c", cmd_i2c},
  #endif
  #ifdef USE_adc
    {"adc", cmd_adc},
  #endif
  #ifdef USE_ax12
    {"ax", cmd_ax},
  #endif
  #ifdef USE_MODULE_mrobot
    {"mrobot", cmd_mrobot},
  #endif
    {"led", cmd_led},
    {"help", cmd_help},
    {"", NULL}
};

extern rt_dev_t cmdline_device_in;
extern rt_dev_t cmdline_device_out;

#define CMDLINE_ARGC_MAX 10

int cmd_exec(char *line)
{
    uint16_t i, argc;
    Cmd *cmd;
    char *argv[CMDLINE_ARGC_MAX];
    char *sep;

    // parse line to argc argv
    sep = line;
    i = 1;
    argv[0] = sep;
    while(sep != NULL && i<CMDLINE_ARGC_MAX)
    {
        sep = strchr(sep, ' ');
        if(sep != 0)
        {
            *sep = '\0';
            if(*(sep+1) != ' ' && *(sep+1) != '\0')
                argv[i++] = sep+1;
            sep++;
        }
        else
            break;
    }
    argc = i;

    // looking for command name
    cmd = NULL;
    for(i=0; i<sizeof(cmds); i++)
    {
        if(cmds[i].cmdFnPtr==0)
            break;
        if(strcmp(cmds[i].name, line)==0)
        {
            cmd = &cmds[i];
            break;
        }
    }

    // execute command if found
    if(cmd!=0)
        return (*cmd->cmdFnPtr)(argc, argv);
    else
        return -1;
}

int cmd_help(int argc, char **argv)
{
    uint16_t i;
    for(i=0; i<sizeof(cmds); i++)
    {
        if(cmds[i].cmdFnPtr==0)
            break;
        puts(cmds[i].name);
    }
    return 0;
}

void cmd_puts(const char *str)
{
    char cmd[10];
    device_write(cmdline_device_out, str, strlen(str));
    device_write(cmdline_device_out, "\n", 1);

    // move cursor 200 column before
    cmdline_curses_left(cmd, 200);
    device_write(cmdline_device_out, cmd, strlen(cmd));
}

int cmd_printf(const char *format, ...)
{
    va_list arg;
    int done;
    char buff[100];

    va_start (arg, format);
    done = vsprintf(buff, format, arg);
    va_end (arg);

    device_write(cmdline_device_out, buff, strlen(buff));
    device_write(cmdline_device_out, "\r\n", 1);
    cmdline_curses_left(buff, 200);
    device_write(cmdline_device_out, buff, strlen(buff));

    return done;
}
