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

uint16_t adc_channels[100] = {0};

int adc_init()
{
    char data[3];
    simulator_send(ADC_SIM_MODULE, 0, ADC_SIM_CONFIG, data, 1);
	return 0;
}

int16_t adc_getValue(uint8_t channel)
{
    ssize_t size_read;
    char data[10];
    uint16_t value;

    simulator_rec_task();
    size_read = simulator_recv(ADC_SIM_MODULE, 0, ADC_SIM_READ, data, 2);
    
    if (size_read <= 0)
    {
        value = adc_channels[channel];
    }
    else
    {
        value = *((uint16_t*)data);
        adc_channels[channel] = value;
    }

    return value;
}
