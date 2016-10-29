
#define puts(str) cmd_puts((str))
#define printf(format, ...) cmd_printf((format), __VA_ARGS__)
#include "cmd.h"

int cmd_ls(int argc, char **argv)
{
    int i;
    puts("ls!!");

    for(i=0; i<argc; i++)
    {
        puts(argv[i]);
    }
    return 0;
}
