/**
 * @file cmd_sysclock.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Sysclock commands
 */

#define SYSCLOCK_DEBUG  // keep this line before includes

#include "cmds.h"

#include "cmd_stdio.h"

#include <driver/sysclock.h>
#include <driver/uart.h>

#include "modules.h"

static void cmd_sysclock_statusclk(SYSCLOCK_SOURCE source);
static void cmd_sysclock_status(void);

void cmd_sysclock_statusclk(SYSCLOCK_SOURCE source)
{
    uint8_t idUnit = 0;
    char unit[] = {' ', 'k', 'M', 'G'};
    int32_t freq = sysclock_sourceFreq(source);
    if (freq == -1)
    {
        return;
    }
    while (freq >= 1000)
    {
        freq /= 1000;
        idUnit++;
    }
    printf("%s: %ld %cHz\n", sysclock_sources_str[source], freq, unit[idUnit]);
}

void cmd_sysclock_status(void)
{
    int source;
    printf("Current clock source: %s\n", sysclock_sources_str[sysclock_source()]);
    for (source = 0; source <= SYSCLOCK_SRC_MAX; source++)
    {
        cmd_sysclock_statusclk((SYSCLOCK_SOURCE)source);
    }
}

int cmd_sysclock(int argc, char **argv)
{
    // no args -> show status
    if (argc == 1)
    {
        cmd_sysclock_status();
        return 0;
    }
    if (strcmp(argv[1], "status") == 0)
    {
        cmd_sysclock_status();
        return 0;
    }
    if (strcmp(argv[1], "switch") == 0)
    {
        int source;
        if (argc < 2)
        {
            return 1;
        }

        for (source = 0; source <= SYSCLOCK_SRC_MAX; source++)
        {
            if (strcmp(argv[2], sysclock_sources_str[source]) == 0)
            {
                uint16_t i;
                int res = sysclock_switchSourceTo(source);

#ifdef USE_uart
                // uart_reconfig();
#endif
#ifdef USE_timer
                // timer_reconfig();
#endif

                for (i = 0; i < 65000; i++)
                    ;

                printf("ret code: %d\n", res);
                return 0;
            }
        }
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        puts("sysclock status");
        puts("sysclock switch <source-clock-name>");
        return 0;
    }

    return 1;
}
