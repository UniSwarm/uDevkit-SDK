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

#include <string.h>

Cmd cmds[] = {
    {.name="ls", cmd_ls},
    {.name="", NULL}
};

#define CMDLINE_ARGC_MAX 10

int cmd_exec(char *line)
{
    int i, argc;
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
