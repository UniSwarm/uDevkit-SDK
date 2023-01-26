/**
 * @file cmd_sysclock.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Sysclock commands
 */

#define SYSCLOCK_DEBUG  // keep this line before includes

#include "cmds.h"

#include "cmd_stdio.h"

#include <archi.h>
#include <driver/sysclock.h>

static void _cmd_sysclock_help(void);
static void _cmd_sysclock_statusclk(const char *sourceStr, int32_t freq);
static void _cmd_sysclock_status(void);

void _cmd_sysclock_help(void)
{
    puts("sysclock status");
    puts("sysclock switch <source-clock-name>");
    puts("sysclock setpll <pll-freq>");
}

void _cmd_sysclock_statusclk(const char *sourceStr, int32_t freq)
{
    uint8_t idUnit = 0;
    char unit[] = {' ', 'k', 'M', 'G'};
    if (freq == -1)
    {
        return;
    }
    float freq_fp = freq;
    while (freq_fp >= 1000.0f)
    {
        freq_fp /= 1000.0f;
        idUnit++;
    }
    printf("%s: %.3f %cHz\r\n", sourceStr, freq_fp, unit[idUnit]);
}

void _cmd_sysclock_status(void)
{
    SYSCLOCK_SOURCE currentSource = sysclock_source();
    printf("Current clock source: ");
    _cmd_sysclock_statusclk(sysclock_sources_str[currentSource], sysclock_sourceFreq(currentSource));
    for (int source = 0; source <= SYSCLOCK_SRC_MAX; source++)
    {
        _cmd_sysclock_statusclk(sysclock_sources_str[source], sysclock_sourceFreq((SYSCLOCK_SOURCE)source));
    }

    // _cmd_sysclock_statusclk("Fvco", sysclock_periphFreq(SYSCLOCK_CLOCK_VCO));
}

int cmd_sysclock(int argc, char **argv)
{
    // no args -> show status
    if (argc == 1)
    {
        _cmd_sysclock_status();
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        _cmd_sysclock_help();
        return 0;
    }

    // status
    if (strcmp(argv[1], "status") == 0)
    {
        _cmd_sysclock_status();
        return 0;
    }

    // switch <source-clock-name>
    if (strcmp(argv[1], "switch") == 0)
    {
        int source;
        if (argc < 2)
        {
            return -1;
        }

        for (source = 0; source <= SYSCLOCK_SRC_MAX; source++)
        {
            if (strcmp(argv[2], sysclock_sources_str[source]) == 0)
            {
                int res = sysclock_switchSourceTo(source);

                device_reconfig();

                for (uint16_t i = 0; i < 65000; i++)
                {
                    nop();
                }

                printf("ret code: %d\r\n", res);
                return 0;
            }
        }
        return 0;
    }
    if (strcmp(argv[1], "setpll") == 0)
    {
        if (argc < 2)
        {
            return -1;
        }

        uint32_t pllFreq = atol(argv[2]);

        int res;
        if (sysclock_sourceFreq(SYSCLOCK_SRC_POSC) == 0)
        {
            res = sysclock_setPLLClock(pllFreq, SYSCLOCK_SRC_FRC);
        }
        else
        {
            res = sysclock_setPLLClock(pllFreq, SYSCLOCK_SRC_POSC);
        }

        device_reconfig();

        for (volatile uint16_t i = 0; i < 65000; i++)
        {
            nop();
        }

        _cmd_sysclock_status();
        printf("ret code: %d\r\n", res);
        return 0;
    }

    return -1;
}
