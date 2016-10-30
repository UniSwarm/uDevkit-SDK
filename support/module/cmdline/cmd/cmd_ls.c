
#include "cmd_stdio.h"

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
