/**
 * @file adc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2017-2021
 *
 * @date April 19, 2016, 10:56 AM
 *
 * @brief ADC driver support
 */

#ifndef ADC_H
#define ADC_H

#include <driver/device.h>

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
int16_t adc_getValue(uint8_t channel);
// int adc_setSamplingPeriod(uint16_t priodMs);

int adc_setTriggerSource(uint8_t channel, uint8_t triggerSource);

int adc_setHandler(uint8_t channel, void (*handler)(int16_t));

#if defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                       \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                       \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "adc_dspic33_sar12.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "adc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mk)
#    include "adc_pic32_sar12.h"
#endif

#endif  // ADC_H
