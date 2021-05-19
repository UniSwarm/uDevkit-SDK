/**
 * @file adc_dspic33_sar12.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
 *
 * @date December 13, 2018, 09:26 AM
 *
 * @brief ADC driver support for dsPIC33E GS, dsPIC33CK and dsPIC33CH
 *
 * Implementation based on Microchip document DS70005213G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM,-12-Bit-High-Speed,-Multiple-SARs-ADC-Converter-DS70005213G.pdf
 */

#ifndef ADC_DSPIC33_SAR12_H
#define ADC_DSPIC33_SAR12_H

// ====================================== Channel availability ======================================
#if defined(DEVICE_33EP128GS702)
#    define ADC_CHANNEL_COUNT 11
#elif defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP64GS502)
#    define ADC_CHANNEL_COUNT 12
#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP502)                        \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP502)
#    define ADC_CHANNEL_COUNT 14
#elif defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_CHANNEL_COUNT 15
#elif defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP128GS704)                       \
    || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)
#    define ADC_CHANNEL_COUNT 17
#elif defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP203)                        \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK128MP203)                      \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP503)
#    define ADC_CHANNEL_COUNT 18
#elif defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP32GS504)                        \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505)
#    define ADC_CHANNEL_COUNT 19
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                      \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                    \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP505)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK128MP205)                      \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP505)
#    define ADC_CHANNEL_COUNT 21
#elif defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP206)                        \
    || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP506)                     \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33EP16GS506)                     \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706)                      \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_CHANNEL_COUNT 22
#elif defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP208)                       \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP508)
#    define ADC_CHANNEL_COUNT 26
#endif

#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_CHANNEL_MAX 15
#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                        \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)
#    define ADC_CHANNEL_MAX 18
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                      \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                    \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103)                       \
    || defined(DEVICE_33CK64MP105)
#    define ADC_CHANNEL_MAX 21
#elif defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                        \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502)                       \
    || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702)                      \
    || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                    \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                    \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_CHANNEL_MAX 22
#elif defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205)                        \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP202)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)                       \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                    \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502)                    \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                    \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                    \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208)                    \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)
#    define ADC_CHANNEL_MAX 26
#endif

#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                    \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                       \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)                       \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                     \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                       \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704)                     \
    || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708)                    \
    || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                    \
    || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH0
#    define ADC_HAVE_CH1
#    define ADC_HAVE_CH2
#    define ADC_HAVE_CH3
#    define ADC_HAVE_CH4
#    define ADC_HAVE_CH6
#    define ADC_HAVE_CH7
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                    \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                       \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)                       \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                     \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                       \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                     \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH8
#    define ADC_HAVE_CH9
#    define ADC_HAVE_CH10
#    define ADC_HAVE_CH11
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                    \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                       \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)                       \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                     \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                       \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706)                      \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH5
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP203)                       \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                     \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP503)                    \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS202)                     \
    || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)                       \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505)                       \
    || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804)                       \
    || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                       \
    || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                    \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                    \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH14
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP203)                       \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                     \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP503)                    \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS202)                     \
    || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)                       \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505)                       \
    || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708)                     \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH12
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP203)                       \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                     \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP503)                    \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS202)                     \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS506)                       \
    || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708)                     \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH13
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP203)                       \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                     \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP503)                    \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS506)                     \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706)                      \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH15
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                    \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                     \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                       \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502)                       \
    || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702)                      \
    || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                    \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                    \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH19
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                    \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103)                       \
    || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP508)                       \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP208)                    \
    || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                      \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502)                       \
    || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506)                       \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505)                       \
    || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804)                       \
    || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                       \
    || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                    \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH20
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                    \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                       \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP505)                       \
    || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP205)                      \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP205)                    \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS504)                     \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                     \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH17
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                    \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                       \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP505)                       \
    || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP205)                      \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP205)                    \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS506)                     \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706)                      \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH16
#endif
#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203)                        \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                   \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208)                     \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                   \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505)                     \
    || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                   \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202)                    \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206)                  \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503)                  \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508)                  \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208)                  \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508)                  \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208)                  \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508)                  \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                    \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP505)                       \
    || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP205)                      \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP205)                    \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS502)                     \
    || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704)                     \
    || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708)                    \
    || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                    \
    || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH18
#endif
#if defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205)                          \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP202)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)                       \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                    \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502)                    \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                    \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                    \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208)                    \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)
#    define ADC_HAVE_CH24
#    define ADC_HAVE_CH25
#endif
#if defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP208)                         \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP508)
#    define ADC_HAVE_CH22
#    define ADC_HAVE_CH23
#endif
#if defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP208)                         \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                       \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502)                       \
    || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702)                      \
    || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                    \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                    \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_CH21
#endif

// ==================================== Dedicated core availability ====================================
#if defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205S1)                 \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)              \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1)              \
    || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1)              \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1)              \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1)              \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1)              \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1)                \
    || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208S1)                 \
    || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                 \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CK128MP202)                  \
    || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                    \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503)                    \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                    \
    || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205)                    \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502)                    \
    || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506)                    \
    || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                      \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)                       \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_HAVE_DEDICATED_CORE0
#    define ADC_HAVE_DEDICATED_CORE1
#elif defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                     \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)                    \
    || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                       \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502)                       \
    || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)
#    define ADC_HAVE_DEDICATED_CORE0
#    define ADC_HAVE_DEDICATED_CORE1
#    define ADC_HAVE_DEDICATED_CORE2
#    define ADC_HAVE_DEDICATED_CORE3
#endif

// ================================= Autocalibration availability =================================
#if defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                       \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                       \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808)
#    define ADC_HAVE_AUTOCALIB
#endif

// ==================================== Comparator availability ====================================
#if defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                       \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)                    \
    || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                       \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202)                       \
    || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505)                       \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504)                       \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708)                       \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806)                       \
    || defined(DEVICE_33EP64GS808)
#    define ADC_COMPARATOR_COUNT 2
#elif defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203)                   \
    || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1)                \
    || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208)                  \
    || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1)                \
    || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505)                  \
    || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1)                \
    || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205)                  \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1)                \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505)                  \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1)                \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205)                  \
    || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1)                \
    || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505)                  \
    || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1)                \
    || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH64MP202)                   \
    || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1)                   \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206)                     \
    || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1)                   \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503)                     \
    || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1)                   \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508)                     \
    || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                   \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205)                       \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
#    define ADC_COMPARATOR_COUNT 4
#else
#    define ADC_COMPARATOR_COUNT 0
#endif

// ================================== Digital filter availability ==================================
#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_DIGITAL_FILTER_COUNT 1
#elif defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                     \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                    \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)                    \
    || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                       \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504)                       \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502)                       \
    || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506)                       \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805)                       \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)
#    define ADC_DIGITAL_FILTER_COUNT 2
#elif defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203)                   \
    || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1)                \
    || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208)                  \
    || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1)                \
    || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505)                  \
    || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1)                \
    || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205)                  \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1)                \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505)                  \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1)                \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205)                  \
    || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1)                \
    || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505)                  \
    || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1)                \
    || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH64MP202)                   \
    || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1)                   \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206)                     \
    || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1)                   \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503)                     \
    || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1)                   \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508)                     \
    || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                   \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                    \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)                    \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205)                       \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102)                       \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
#    define ADC_DIGITAL_FILTER_COUNT 4
#else
#    define ADC_DIGITAL_FILTER_COUNT 0
#endif

// ================================== TRIGGER sources ==================================
#define ADC_TRIGSRC00 ADTRIG0Lbits.TRGSRC0
#define ADC_TRIGSRC01 ADTRIG0Lbits.TRGSRC1
#define ADC_TRIGSRC02 ADTRIG0Hbits.TRGSRC2
#define ADC_TRIGSRC03 ADTRIG0Hbits.TRGSRC3
#define ADC_TRIGSRC04 ADTRIG1Lbits.TRGSRC4
#define ADC_TRIGSRC05 ADTRIG1Lbits.TRGSRC5
#define ADC_TRIGSRC06 ADTRIG1Hbits.TRGSRC6
#define ADC_TRIGSRC07 ADTRIG1Hbits.TRGSRC7
#define ADC_TRIGSRC08 ADTRIG2Lbits.TRGSRC8
#define ADC_TRIGSRC09 ADTRIG2Lbits.TRGSRC9
#define ADC_TRIGSRC10 ADTRIG2Hbits.TRGSRC10
#define ADC_TRIGSRC11 ADTRIG2Hbits.TRGSRC11
#define ADC_TRIGSRC12 ADTRIG3Lbits.TRGSRC12
#define ADC_TRIGSRC13 ADTRIG3Lbits.TRGSRC13
#define ADC_TRIGSRC14 ADTRIG3Hbits.TRGSRC14
#define ADC_TRIGSRC15 ADTRIG3Hbits.TRGSRC15
#define ADC_TRIGSRC16 ADTRIG4Lbits.TRGSRC16
#define ADC_TRIGSRC17 ADTRIG4Lbits.TRGSRC17
#define ADC_TRIGSRC18 ADTRIG4Hbits.TRGSRC18
#define ADC_TRIGSRC19 ADTRIG4Hbits.TRGSRC19
#define ADC_TRIGSRC20 ADTRIG5Lbits.TRGSRC20
#define ADC_TRIGSRC21 ADTRIG5Lbits.TRGSRC21
#define ADC_TRIGSRC22 ADTRIG5Hbits.TRGSRC22
#define ADC_TRIGSRC23 ADTRIG5Hbits.TRGSRC23
#define ADC_TRIGSRC24 ADTRIG6Lbits.TRGSRC24
#define ADC_TRIGSRC25 ADTRIG6Lbits.TRGSRC25
#define ADC_TRIGSRC26 ADTRIG6Hbits.TRGSRC26
#define ADC_TRIGSRC27 ADTRIG6Hbits.TRGSRC27
#define ADC_TRIGSRC28 ADTRIG7Lbits.TRGSRC28
#define ADC_TRIGSRC29 ADTRIG7Lbits.TRGSRC29
#define ADC_TRIGSRC30 ADTRIG7Hbits.TRGSRC30
#define ADC_TRIGSRC31 ADTRIG7Hbits.TRGSRC31

#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205)                          \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP502)                       \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506)                       \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203)                     \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP208)                    \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                    \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205)                    \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP505)                    \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205)                    \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505)                    \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
// CH master
#    define ADC_TRGSRC_ADTRG31        0b11111
#    define ADC_TRGSRC_MSTR_PTG       0b11110
#    define ADC_TRGSRC_SLV_CLC1       0b11101
#    define ADC_TRGSRC_MSTR_CLC1      0b11100
#    define ADC_TRGSRC_SLV_PWM8_TRG2  0b11011
#    define ADC_TRGSRC_SLV_PWM5_TRG2  0b11010
#    define ADC_TRGSRC_SLV_PWM3_TRG2  0b11001
#    define ADC_TRGSRC_SLV_PWM1_TRG2  0b11000
#    define ADC_TRGSRC_MSTR_SCCP4     0b10111
#    define ADC_TRGSRC_MSTR_SCCP3     0b10110
#    define ADC_TRGSRC_MSTR_SCCP2     0b10101
#    define ADC_TRGSRC_MSTR_SCCP1     0b10100
#    define ADC_TRGSRC_MSTR_PWM4_TRG2 0b01011
#    define ADC_TRGSRC_MSTR_PWM4_TRG1 0b01010
#    define ADC_TRGSRC_MSTR_PWM3_TRG2 0b01001
#    define ADC_TRGSRC_MSTR_PWM3_TRG1 0b01000
#    define ADC_TRGSRC_MSTR_PWM2_TRG2 0b00111
#    define ADC_TRGSRC_MSTR_PWM2_TRG1 0b00110
#    define ADC_TRGSRC_MSTR_PWM1_TRG2 0b00101
#    define ADC_TRGSRC_MSTR_PWM1_TRG1 0b00100
#    define ADC_TRGSRC_SOFTTRG        0b00010
#    define ADC_TRGSRC_COMMONSOFTTRG  0b00001
#    define ADC_TRGSRC_NOTRIG         0b00000

#elif defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1)                  \
    || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1)                 \
    || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506S1)                 \
    || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)               \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1)              \
    || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1)              \
    || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205S1)              \
    || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505S1)              \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)              \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1)              \
    || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)
// CH slave
#    define ADC_TRGSRC_ADTRG31        0b11111
#    define ADC_TRGSRC_MSTR_PTG       0b11110
#    define ADC_TRGSRC_SLV_CLC1       0b11101
#    define ADC_TRGSRC_MSTR_CLC1      0b11100
#    define ADC_TRGSRC_MSTR_PWM3_TRG2 0b11001
#    define ADC_TRGSRC_MSTR_PWM1_TRG2 0b11000
#    define ADC_TRGSRC_SLV_SCCP4      0b10111
#    define ADC_TRGSRC_SLV_SCCP3      0b10110
#    define ADC_TRGSRC_SLV_SCCP2      0b10101
#    define ADC_TRGSRC_SLV_SCCP1      0b10100
#    define ADC_TRGSRC_SLV_PWM8_TRG1  0b01111
#    define ADC_TRGSRC_SLV_PWM7_TRG1  0b01110
#    define ADC_TRGSRC_SLV_PWM6_TRG1  0b01101
#    define ADC_TRGSRC_SLV_PWM5_TRG1  0b01100
#    define ADC_TRGSRC_SLV_PWM4_TRG2  0b01011
#    define ADC_TRGSRC_SLV_PWM4_TRG1  0b01010
#    define ADC_TRGSRC_SLV_PWM3_TRG2  0b01001
#    define ADC_TRGSRC_SLV_PWM3_TRG1  0b01000
#    define ADC_TRGSRC_SLV_PWM2_TRG2  0b00111
#    define ADC_TRGSRC_SLV_PWM2_TRG1  0b00110
#    define ADC_TRGSRC_SLV_PWM1_TRG2  0b00101
#    define ADC_TRGSRC_SLV_PWM1_TRG1  0b00100
#    define ADC_TRGSRC_SOFTTRG        0b00010
#    define ADC_TRGSRC_COMMONSOFTTRG  0b00001
#    define ADC_TRGSRC_NOTRIG         0b00000

#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                        \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)                       \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)
// CK MP1XX
#    define ADC_TRGSRC_ADTRG31       0b11111
#    define ADC_TRGSRC_MSTR_PTG      0b11110
#    define ADC_TRGSRC_CLC4          0b10010
#    define ADC_TRGSRC_CLC3          0b10001
#    define ADC_TRGSRC_CLC2          0b11101
#    define ADC_TRGSRC_CLC1          0b11100
#    define ADC_TRGSRC_MCCP5         0b11000
#    define ADC_TRGSRC_SCCP4         0b10111
#    define ADC_TRGSRC_SCCP3         0b10110
#    define ADC_TRGSRC_SCCP2         0b10101
#    define ADC_TRGSRC_SCCP1         0b10100
#    define ADC_TRGSRC_MCCP5_TRG     0b10000
#    define ADC_TRGSRC_SCCP4_TRG     0b01111
#    define ADC_TRGSRC_SCCP3_TRG     0b01110
#    define ADC_TRGSRC_SCCP2_TRG     0b01101
#    define ADC_TRGSRC_SCCP1_TRG     0b01100
#    define ADC_TRGSRC_PWM4_TRG2     0b01011
#    define ADC_TRGSRC_PWM4_TRG1     0b01010
#    define ADC_TRGSRC_PWM3_TRG2     0b01001
#    define ADC_TRGSRC_PWM3_TRG1     0b01000
#    define ADC_TRGSRC_PWM2_TRG2     0b00111
#    define ADC_TRGSRC_PWM2_TRG1     0b00110
#    define ADC_TRGSRC_PWM1_TRG2     0b00101
#    define ADC_TRGSRC_PWM1_TRG1     0b00100
#    define ADC_TRGSRC_SOFTTRG       0b00010
#    define ADC_TRGSRC_COMMONSOFTTRG 0b00001
#    define ADC_TRGSRC_NOTRIG        0b00000

#elif defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205)                        \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503)                       \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP202)                       \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206)                       \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503)                       \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)                       \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                    \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502)                    \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                    \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                    \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208)                    \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                    \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)
// CK MP2/5XX
#    define ADC_TRGSRC_ADTRG31       0b11111
#    define ADC_TRGSRC_MSTR_PTG      0b11110
#    define ADC_TRGSRC_CLC2          0b11101
#    define ADC_TRGSRC_CLC1          0b11100
#    define ADC_TRGSRC_MCCP9         0b11011
#    define ADC_TRGSRC_SCCP7         0b11010
#    define ADC_TRGSRC_SCCP6         0b11001
#    define ADC_TRGSRC_SCCP5         0b11000
#    define ADC_TRGSRC_SCCP4         0b10111
#    define ADC_TRGSRC_SCCP3         0b10110
#    define ADC_TRGSRC_SCCP2         0b10101
#    define ADC_TRGSRC_SCCP1         0b10100
#    define ADC_TRGSRC_PWM8_TRG2     0b10011
#    define ADC_TRGSRC_PWM8_TRG1     0b10010
#    define ADC_TRGSRC_PWM7_TRG2     0b10001
#    define ADC_TRGSRC_PWM7_TRG1     0b10000
#    define ADC_TRGSRC_PWM6_TRG2     0b01111
#    define ADC_TRGSRC_PWM6_TRG1     0b01110
#    define ADC_TRGSRC_PWM5_TRG2     0b01101
#    define ADC_TRGSRC_PWM5_TRG1     0b01100
#    define ADC_TRGSRC_PWM4_TRG2     0b01011
#    define ADC_TRGSRC_PWM4_TRG1     0b01010
#    define ADC_TRGSRC_PWM3_TRG2     0b01001
#    define ADC_TRGSRC_PWM3_TRG1     0b01000
#    define ADC_TRGSRC_PWM2_TRG2     0b00111
#    define ADC_TRGSRC_PWM2_TRG1     0b00110
#    define ADC_TRGSRC_PWM1_TRG2     0b00101
#    define ADC_TRGSRC_PWM1_TRG1     0b00100
#    define ADC_TRGSRC_SOFTTRG       0b00010
#    define ADC_TRGSRC_COMMONSOFTTRG 0b00001
#    define ADC_TRGSRC_NOTRIG        0b00000
#endif

#endif  // ADC_DSPIC33_SAR12_H
