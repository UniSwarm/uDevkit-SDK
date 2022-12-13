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

#define CMDLINE_ARGC_MAX       10
#define CMDLINE_CUSTOM_CMD_MAX 10

static int _cmd_help(int argc, char **argv);
static void _cmd_carriageReturn(void);

const Cmd _cmd_cmds[] = {
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
#ifdef USE_timer
    {"timer", cmd_timer},
#endif
#ifdef USE_uart
    {"uart", cmd_uart},
#endif
    {"", NULL}};

Cmd _cmd_custom_cmds[CMDLINE_CUSTOM_CMD_MAX];

extern rt_dev_t _cmdline_device_out;

int (*_cmdline_cmdTaskPtr)(void) = NULL;

int cmd_exec(char *line)
{
    char *argv[CMDLINE_ARGC_MAX];

    // parse line to argc argv
    char *sep = line;
    uint16_t argc = 1;
    argv[0] = sep;
    while (sep != NULL && argc < CMDLINE_ARGC_MAX)
    {
        sep = strchr(sep, ' ');
        if (sep != 0)
        {
            *sep = '\0';
            if (*(sep + 1) != ' ' && *(sep + 1) != '\0')
            {
                argv[argc++] = sep + 1;
            }
            sep++;
        }
        else
        {
            break;
        }
    }

    // looking for command name
    const Cmd *cmd = cmd_findFromName(line);

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

    for (uint16_t i = 0; i < sizeof(_cmd_cmds); i++)
    {
        if (_cmd_cmds[i].cmdFnPtr == 0)
        {
            break;
        }
        cmd_puts(_cmd_cmds[i].name);
    }

    uint custom_count = 0;
    for (uint16_t i = 0; i < CMDLINE_CUSTOM_CMD_MAX; i++)
    {
        if (_cmd_custom_cmds[i].cmdFnPtr == NULL)
        {
            continue;
        }
        if (custom_count++ == 0)
        {
            cmd_puts("+ Custom commands:");
        }
        cmd_puts(_cmd_custom_cmds[i].name);
    }
    return 0;
}

void _cmd_carriageReturn(void)
{
    char cmd[10];
    cmdline_curses_left(cmd, 200);
    device_write(_cmdline_device_out, cmd, strlen(cmd));
}

void cmd_puts(const char *str)
{
    device_write(_cmdline_device_out, str, strlen(str));
    device_write(_cmdline_device_out, "\n", 1);

    _cmd_carriageReturn();
}

int cmd_printf(const char *format, ...)
{
    va_list arg;
    int done;
    char buff[256];

    va_start(arg, format);
    done = vsprintf(buff, format, arg);
    va_end(arg);

    char *begin = buff;
    char *end = strchr(begin, '\r');
    while (end != NULL)
    {
        device_write(_cmdline_device_out, begin, end - begin);
        device_write(_cmdline_device_out, "\r\n", 1);

        _cmd_carriageReturn();

        begin = end + 1;
        end = strchr(begin, '\r');
    }
    device_write(_cmdline_device_out, begin, strlen(begin));

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

const Cmd *cmd_findFromName(char *name)
{
    const Cmd *cmd = NULL;
    for (uint i = 0; i < sizeof(_cmd_cmds); i++)
    {
        if (_cmd_cmds[i].cmdFnPtr == NULL)
        {
            break;
        }
        if (strcmp(_cmd_cmds[i].name, name) == 0)
        {
            cmd = &_cmd_cmds[i];
            break;
        }
    }

    if (cmd == NULL)
    {
        // looking for command name in custom commands
        for (uint i = 0; i < CMDLINE_CUSTOM_CMD_MAX; i++)
        {
            if (_cmd_custom_cmds[i].cmdFnPtr == NULL)
            {
                break;
            }
            if (strcmp(_cmd_custom_cmds[i].name, name) == 0)
            {
                cmd = &_cmd_custom_cmds[i];
                break;
            }
        }
    }

    return cmd;
}

int cmd_addCommand(const char name[10], int (*cmdFnPtr)(int, char **))
{
    Cmd *cmd = NULL;
    for (int i = 0; i < CMDLINE_CUSTOM_CMD_MAX; i++)
    {
        if (_cmd_custom_cmds[i].cmdFnPtr == NULL)
        {
            cmd = &_cmd_custom_cmds[i];
            break;
        }
    }
    if (cmd == NULL)
    {
        return -1;
    }

    strcpy(cmd->name, name);
    cmd->cmdFnPtr = cmdFnPtr;
    puts(cmd->name);

    return 0;
}
