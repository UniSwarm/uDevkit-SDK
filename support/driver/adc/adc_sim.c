/**
 * @file adc_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief ADC simulator driver support
 */

#include "adc_sim.h"

#include "simulator.h"

#include <stdio.h>

static uint16_t adc_channels[ADC_CHANNEL_COUNT] = {0};

int adc_init(void)
{
    char data[3];
    data[0] = ADC_CHANNEL_COUNT;
    simulator_send(ADC_SIM_MODULE, 0, ADC_SIM_CONFIG, data, 1);
    return 0;
}

int adc_setMasterClock(uint8_t source, uint16_t divider)
{
    UDK_UNUSED(source);
    UDK_UNUSED(divider);

    return 0;
}

int adc_setCoreClockDivider(uint8_t core, uint16_t divider)
{
    UDK_UNUSED(core);
    UDK_UNUSED(divider);

    return 0;
}

int adc_setCoreResolution(uint8_t core, uint16_t resolution)
{
    UDK_UNUSED(core);
    UDK_UNUSED(resolution);

    // TODO implement

    return 0;
}

int adc_setSamplingCycles(uint8_t core, uint16_t cycles)
{
    UDK_UNUSED(core);
    UDK_UNUSED(cycles);

    // TODO implement

    return 0;
}

int adc_startSampling(uint8_t channel)
{
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return -1;
    }

    ssize_t size_read;

    simulator_rec_task();
    size_read = simulator_recv(ADC_SIM_MODULE, 0, ADC_SIM_READ, (char *)adc_channels, ADC_CHANNEL_COUNT * 2);

    UDK_UNUSED(size_read);

    return 0;
}

int16_t adc_getValue(uint8_t channel)
{
    ssize_t size_read;

    simulator_rec_task();
    size_read = simulator_recv(ADC_SIM_MODULE, 0, ADC_SIM_READ, (char *)adc_channels, ADC_CHANNEL_COUNT * 2);

    UDK_UNUSED(size_read);

    if (channel >= ADC_CHANNEL_COUNT)
    {
        return 0;
    }

    return adc_channels[channel];
}

int16_t adc_value(uint8_t channel)
{
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return 0;
    }

    return adc_channels[channel];
}

int adc_setTriggerSource(uint8_t channel, uint8_t triggerSource)
{
    UDK_UNUSED(triggerSource);
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return -1;
    }

    return 0;
}

int adc_setHandler(uint8_t channel, void (*handler)(int16_t))
{
    UDK_UNUSED(handler);
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return 0;
    }

    return 0;
}
