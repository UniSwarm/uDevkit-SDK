/**
 * @file cmd_adc.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief ADC commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <driver/adc.h>

static void _cmd_adc_help(void);

void _cmd_adc_help(void)
{
    puts("adc");
    puts("adc scan");
    puts("adc <channel>");
}

int cmd_adc(int argc, char **argv)
{
    uint16_t value;
    if (argc < 2)
    {
        printf("%d channels, %d max channel\r\n", (int)ADC_CHANNEL_COUNT, (int)ADC_CHANNEL_MAX);
        printf("%d bits resolution\r\n", (int)ADC_MAX_RESOLUTION_BIT);
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        _cmd_adc_help();
        return 0;
    }

    // scan
    if (strcmp(argv[1], "scan") == 0)
    {
        for (int channel = 0; channel <= ADC_CHANNEL_MAX; channel++)
        {
            if (adc_channelExists(channel))
            {
                value = adc_getValue(channel);
                printf("channel %d : %d => %.3fV\r\n", channel, value, (float)value / (1U << ADC_MAX_RESOLUTION_BIT) * 3.3);
            }
        }
        return 0;
    }

    int8_t channel = atoi(argv[1]);

    // read value of an adc channel
    // > adc <adc-channel>
    value = adc_getValue(channel);
    printf("%d => %.3fV\r\n", value, (float)value / (1U << ADC_MAX_RESOLUTION_BIT) * 3.3);

    return 0;
}
