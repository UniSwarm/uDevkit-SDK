
#define SYSCLOCK_DEBUG
#include "driver/sysclock.h"

#include "cmd_stdio.h"

void cmd_sysclock_statusclk(SYSCLOCK_SOURCE source)
{
    int32_t freq = sysclock_sourceFreq(source);
    if (freq == -1)
        return;
    printf("%s: %dHz\n", sysclock_sources_str[source], freq);
}

void cmd_sysclock_status()
{
    int source;
    printf("Current clock source: %s\n", sysclock_sources_str[sysclock_source()]);
    for (source=0; source <= SYSCLOCK_SRC_MAX; source++)
        cmd_sysclock_statusclk((SYSCLOCK_SOURCE) source);
}

int cmd_sysclock(int argc, char **argv)
{
    // no args -> show status
    if(argc == 1)
    {
        cmd_sysclock_status();
        return 0;
    }
    if(strcmp(argv[1], "status")==0)
    {
        cmd_sysclock_status();
        return 0;
    }

    // help
    if(strcmp(argv[1], "help")==0)
    {
        puts("sysclock");
        puts("sysclock <uart-id>");
        return 0;
    }

    return 1;
}
