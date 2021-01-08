/**
 * @file adc_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 28, 2016, 20:35 PM 
 * 
 * @brief ADC simulator driver support
 */

#include "adc_sim.h"
#include "simulator.h"

#include <stdio.h>

static uint16_t adc_channels[ADC_CHANNEL_COUNT] = {0};

int adc_init()
{
    char data[3];
    data[0] = ADC_CHANNEL_COUNT;
    simulator_send(ADC_SIM_MODULE, 0, ADC_SIM_CONFIG, data, 1);
	return 0;
}

int16_t adc_getValue(uint8_t channel)
{
    ssize_t size_read;

    simulator_rec_task();
    size_read = simulator_recv(ADC_SIM_MODULE, 0, ADC_SIM_READ, (char*)adc_channels, ADC_CHANNEL_COUNT * 2);

    UDK_UNUSED(size_read);

    if (channel >= ADC_CHANNEL_COUNT)
        return 0;

    return adc_channels[channel];
}

int16_t adc_value(uint8_t channel)
{
    return 0;
}
