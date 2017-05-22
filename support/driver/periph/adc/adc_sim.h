/**
 * @file adc_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 28, 2016, 20:35 PM 
 * 
 * @brief ADC simulator driver support
 */

#ifndef ADC_SIM_H
#define ADC_SIM_H

#include "adc.h"

#include <stdint.h>

typedef struct
{
    uint32_t baudSpeed;
    uint8_t bitStop;
    uint8_t bitParity;
    uint8_t bitLenght;
    uint8_t enabled;
} adc_dev;

#define ADC_SIM_MODULE 0x0031

#define ADC_SIM_CONFIG 0x0000
#define ADC_SIM_READ   0x0001

#endif // ADC_SIM_H
