/**
 * @file adc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 19, 2016, 10:56 AM
 *
 * @brief ADC driver support
 */

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

int adc_init();
//int adc_initchannel(uint8_t channel);
//int adc_closechannel(uint8_t channel);

int16_t adc_getValue(uint8_t channel);
//int adc_setSamplingPeriod(uint16_t priodMs);

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "adc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
 #include "adc_pic32mz.h"
#endif

#endif // ADC_H
