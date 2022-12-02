/**
 * @file cmd_timer.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date December 1, 2022, 11:27 AM
 *
 * @brief Timer commands
 */

#include "cmds.h"

#include "../cmdline_curses.h"
#include "cmd_stdio.h"

#include <driver/timer.h>

static void _cmd_timer_help(void);
static void _cmd_timer_printConfig(rt_dev_t timer_dev);

void _cmd_timer_help(void)
{
    puts("timer");
    puts("timer <timer-id>");
}

void _cmd_timer_printConfig(rt_dev_t timer_dev)
{
    if (timer_isOpened(timer_dev))
    {
        printf(CMDLINE_GRN " Opened," CMDLINE_NRM);
    }
    else
    {
        printf(CMDLINE_RED " Closed," CMDLINE_NRM);
    }

    if (timer_isEnabled(timer_dev))
    {
        printf(CMDLINE_GRN " enabled " CMDLINE_NRM);
    }
    else
    {
        printf(CMDLINE_RED " disabled" CMDLINE_NRM);
    }
    printf(" period: %lu (%lu ms)\r\n", timer_period(timer_dev), timer_periodMs(timer_dev));

    printf("  - value: %lu\r\n", timer_value(timer_dev));
}

int cmd_timer(int argc, char **argv)
{
#if (!defined(TIMER_COUNT) || TIMER_COUNT == 0)
    puts("No TIMER module");
    return 0;
#else
    // no args -> print number of timers
    if (argc == 1)
    {
        printf("count: %d\r\n", (int)TIMER_COUNT);
        for (uint8_t timer_id = 1; timer_id <= TIMER_COUNT; timer_id++)
        {
            printf("Timer %d:", timer_id);
            rt_dev_t timer_dev = timer(timer_id);
            _cmd_timer_printConfig(timer_dev);
        }
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        _cmd_timer_help();
        return 0;
    }

    // first arg numeric : convert to timer id
    uint8_t timer_id = atoi(argv[1]);
    if (timer_id <= 0 || timer_id > TIMER_COUNT)
    {
        printf("Invalid timer id %d\r\n", timer_id);
        return -1;
    }
    rt_dev_t timer_dev = timer(timer_id);

    // if no more arg, print properties of timer
    // > timer <timer-id>
    if (argc == 2)
    {
        _cmd_timer_printConfig(timer_dev);
        return 0;
    }

    return -1;
#endif
}