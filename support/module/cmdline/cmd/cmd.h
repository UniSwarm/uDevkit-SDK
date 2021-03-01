/**
 * @file cmdline.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Define a base for all commands
 */

#ifndef CMD_H
#define CMD_H

typedef struct
{
    char name[20];
    int (*cmdFnPtr)(int, char**);
} Cmd;

int cmd_exec(char *line);

void cmd_puts(const char *str);
int cmd_printf(const char *format, ...);

#endif // CMD_H
