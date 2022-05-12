/**
 * @file adc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2017-2022
 *
 * @date April 19, 2016, 10:56 AM
 *
 * @brief ADC driver support
 */

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#include "adc_device.h"

int adc_init(void);
int adc_setMasterClock(uint8_t source, uint16_t divider);
int adc_setCoreClockDivider(uint8_t core, uint16_t divider);
int adc_setCoreResolution(uint8_t core, uint16_t resolution);
int adc_setSamplingCycles(uint8_t core, uint16_t cycles);
// int adc_initchannel(uint8_t channel);
// int adc_closechannel(uint8_t channel);

int adc_startSampling(uint8_t channel);
int adc_dataReady(uint8_t channel);
int16_t adc_value(uint8_t channel);
volatile int16_t *adc_buffAddr(uint8_t channel);
int16_t adc_getValue(uint8_t channel);
// int adc_setSamplingPeriod(uint16_t priodMs);

int adc_setTriggerSource(uint8_t channel, uint8_t triggerSource);

int adc_setHandler(uint8_t channel, void (*handler)(int16_t));

#ifdef __cplusplus
}
#endif

#endif  // ADC_H
