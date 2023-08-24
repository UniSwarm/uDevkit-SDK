/**
 * @file adc_dspic33_sar12.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
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

#ifdef __cplusplus
extern "C" {
#endif

volatile int16_t *adc_buffAddr(uint8_t channel);

#define ADC_MAX_RESOLUTION_BIT 12

// ====================================== Channel availability ======================================
#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_MASK 0x7FFFLU
#    define ADC_CHANNEL_COUNT     15
#    define ADC_CHANNEL_MAX       14
#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK64MC102)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_MASK 0x00030FFFLU
#    define ADC_CHANNEL_COUNT     14
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDVL64MC106) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                              \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_MASK 0x0003FFFFLU
#    define ADC_CHANNEL_COUNT     18
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1)                             \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1)                            \
    || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                            \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1)                            \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1)                            \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                        \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1)                        \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1)                        \
    || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                        \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1)                        \
    || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1)                        \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP218S1)                        \
    || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1)                        \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                        \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1)                        \
    || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1)                        \
    || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                            \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_MASK 0x001FFFFFLU
#    define ADC_CHANNEL_COUNT     21
#    define ADC_CHANNEL_MAX       20
#elif defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC502)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x00330F7FLU
#    define ADC_CHANNEL_COUNT     15
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC503)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x0033FF7FLU
#    define ADC_CHANNEL_COUNT     19
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                               \
    || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x003E4FDFLU
#    define ADC_CHANNEL_COUNT     17
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP64GS504)  \
    || defined(DEVICE_33EP64GS505)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x003E5FFFLU
#    define ADC_CHANNEL_COUNT     19
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506)                             \
    || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506)                            \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS806) \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS806)                             \
    || defined(DEVICE_33EP128GS808)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x003FFFFFLU
#    define ADC_CHANNEL_COUNT     22
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33EP128GS702)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x003C00DFLU
#    define ADC_CHANNEL_COUNT     11
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP64GS502)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_MASK 0x003C00FFLU
#    define ADC_CHANNEL_COUNT     12
#    define ADC_CHANNEL_MAX       21
#elif defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK128MP202) \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP502)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_MASK 0x03000FFFLU
#    define ADC_CHANNEL_COUNT     14
#    define ADC_CHANNEL_MAX       25
#elif defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK128MP203) \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP503)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_MASK 0x0300FFFFLU
#    define ADC_CHANNEL_COUNT     18
#    define ADC_CHANNEL_MAX       25
#elif defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK128MP205) \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP505)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_MASK 0x0307FFFFLU
#    define ADC_CHANNEL_COUNT     21
#    define ADC_CHANNEL_MAX       25
#elif defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506)                       \
    || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP506)                                \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP506)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_MASK 0x030FFFFFLU
#    define ADC_CHANNEL_COUNT     22
#    define ADC_CHANNEL_MAX       25
#elif defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP508)                               \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP508)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_MASK 0x03FFFFFFLU
#    define ADC_CHANNEL_COUNT     26
#    define ADC_CHANNEL_MAX       25
#elif defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP605)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_MASK 0x0F07FFFFLU
#    define ADC_CHANNEL_COUNT     23
#    define ADC_CHANNEL_MAX       27
#elif defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP606)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_MASK 0x0F0FFFFFLU
#    define ADC_CHANNEL_COUNT     24
#    define ADC_CHANNEL_MAX       27
#elif defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP308)                            \
    || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MPT608)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_MASK 0x0FFFFFFFLU
#    define ADC_CHANNEL_COUNT     28
#    define ADC_CHANNEL_MAX       27
#elif defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP306S1)                         \
    || defined(DEVICE_33CH512MP405) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP406S1)                        \
    || defined(DEVICE_33CH512MP605) || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP606S1)                        \
    || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP705S1) || defined(DEVICE_33CH512MP706) || defined(DEVICE_33CH512MP706S1)                        \
    || defined(DEVICE_33CH1024MP305) || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP306S1)                    \
    || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP405S1) || defined(DEVICE_33CH1024MP406) || defined(DEVICE_33CH1024MP406S1)                    \
    || defined(DEVICE_33CH1024MP605) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP606S1)                    \
    || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP705S1) || defined(DEVICE_33CH1024MP706) || defined(DEVICE_33CH1024MP706S1)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_MASK 0x1F02FFFFLU
#    define ADC_CHANNEL_COUNT     22
#    define ADC_CHANNEL_MAX       28
#elif defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP408S1)                         \
    || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP608S1) || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP708S1)                        \
    || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP308S1) || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP408S1)                    \
    || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP608S1) || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP708S1)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_MASK 0x1F0AFFFFLU
#    define ADC_CHANNEL_COUNT     23
#    define ADC_CHANNEL_MAX       28
#elif defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP412) || defined(DEVICE_33CH512MP412S1)                         \
    || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP710S1) || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH512MP712S1)                        \
    || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP410S1) || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP412S1)                    \
    || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP710S1) || defined(DEVICE_33CH1024MP712) || defined(DEVICE_33CH1024MP712S1)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_MASK 0x1FFFFFFFLU
#    define ADC_CHANNEL_COUNT     29
#    define ADC_CHANNEL_MAX       28
#elif defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP705)                             \
    || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP705)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_CH29
#    define ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_HAVE_CH31
#    define ADC_CHANNEL_HAVE_MASK 0xF807FFFFLU
#    define ADC_CHANNEL_COUNT     24
#    define ADC_CHANNEL_MAX       31
#elif defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP706) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP706)                             \
    || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP706)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_CH29
#    define ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_HAVE_CH31
#    define ADC_CHANNEL_HAVE_MASK 0xF80FFFFFLU
#    define ADC_CHANNEL_COUNT     25
#    define ADC_CHANNEL_MAX       31
#elif defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP708)                             \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP708)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_CH29
#    define ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_HAVE_CH31
#    define ADC_CHANNEL_HAVE_MASK 0xF8FFFFFFLU
#    define ADC_CHANNEL_COUNT     29
#    define ADC_CHANNEL_MAX       31
#elif defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP710)                             \
    || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP710)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_CH29
#    define ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_HAVE_CH31
#    define ADC_CHANNEL_HAVE_MASK 0xFFFFFFFFLU
#    define ADC_CHANNEL_COUNT     32
#    define ADC_CHANNEL_MAX       31
#endif

// ================================== Dedicated core availability ==================================
#if defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506)                         \
    || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                        \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1)                    \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)                    \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1)                    \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105)                             \
    || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) \
    || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                             \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503)                            \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                            \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208)                            \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506)                            \
    || defined(DEVICE_33CK256MP508) || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_HAVE_DEDICATED_CORE0
#    define ADC_HAVE_DEDICATED_CORE1
#elif defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306S1) || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP405S1)                     \
    || defined(DEVICE_33CH512MP406S1) || defined(DEVICE_33CH512MP408S1) || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP412S1)                    \
    || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606S1) || defined(DEVICE_33CH512MP608S1) || defined(DEVICE_33CH512MP705S1)                    \
    || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708S1) || defined(DEVICE_33CH512MP710S1) || defined(DEVICE_33CH512MP712S1)                    \
    || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306S1) || defined(DEVICE_33CH1024MP308S1) || defined(DEVICE_33CH1024MP405S1)                \
    || defined(DEVICE_33CH1024MP406S1) || defined(DEVICE_33CH1024MP408S1) || defined(DEVICE_33CH1024MP410S1) || defined(DEVICE_33CH1024MP412S1)                \
    || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606S1) || defined(DEVICE_33CH1024MP608S1) || defined(DEVICE_33CH1024MP705S1)                \
    || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708S1) || defined(DEVICE_33CH1024MP710S1) || defined(DEVICE_33CH1024MP712S1)                \
    || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405)                            \
    || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                            \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305)                           \
    || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406)                            \
    || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606)                            \
    || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708)                            \
    || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406)                         \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706)                        \
    || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                            \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) \
    || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) \
    || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                            \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                            \
    || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_DEDICATED_CORE0
#    define ADC_HAVE_DEDICATED_CORE1
#    define ADC_HAVE_DEDICATED_CORE2
#    define ADC_HAVE_DEDICATED_CORE3
#endif

// ================================== Autocalibration availability =================================
#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)    \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                                \
    || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                            \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                            \
    || defined(DEVICE_33EP128GS808)
#    define ADC_HAVE_AUTOCALIB
#endif

// ==================================== Comparator availability ====================================
#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)    \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                                \
    || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                            \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                            \
    || defined(DEVICE_33EP128GS808)
#    define ADC_COMPARATOR_COUNT 2
#elif defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506)                         \
    || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CDVL64MC106) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1)                         \
    || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                            \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1)                            \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1)                            \
    || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                            \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1)                          \
    || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1)                        \
    || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                        \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1)                        \
    || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1)                        \
    || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                        \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1)                        \
    || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP218S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                        \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1)                        \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1)                        \
    || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP305S1)                        \
    || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP306S1) || defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP308S1)                        \
    || defined(DEVICE_33CH512MP405) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP406S1)                        \
    || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP408S1) || defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP410S1)                        \
    || defined(DEVICE_33CH512MP412) || defined(DEVICE_33CH512MP412S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                        \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1)                        \
    || defined(DEVICE_33CH512MP605) || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP606S1)                        \
    || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP608S1) || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP705S1)                        \
    || defined(DEVICE_33CH512MP706) || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP708S1)                        \
    || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP710S1) || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH512MP712S1)                        \
    || defined(DEVICE_33CH1024MP305) || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP306S1)                    \
    || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP308S1) || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP405S1)                    \
    || defined(DEVICE_33CH1024MP406) || defined(DEVICE_33CH1024MP406S1) || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP408S1)                    \
    || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP410S1) || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP412S1)                    \
    || defined(DEVICE_33CH1024MP605) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP606S1)                    \
    || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP608S1) || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP705S1)                    \
    || defined(DEVICE_33CH1024MP706) || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP708S1)                    \
    || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP710S1) || defined(DEVICE_33CH1024MP712) || defined(DEVICE_33CH1024MP712S1)                    \
    || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) \
    || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102) \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) \
    || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) \
    || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106)                            \
    || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506)                            \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                            \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                            \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103)                            \
    || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503)                            \
    || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                            \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305)                            \
    || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406)                            \
    || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                            \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                            \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305)                           \
    || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406)                            \
    || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606)                            \
    || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708)                            \
    || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406)                         \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706)                        \
    || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
#    define ADC_COMPARATOR_COUNT 4
#else
#    define ADC_COMPARATOR_COUNT 0
#endif

// ================================== Digital filter availability ==================================
#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define ADC_DIGITAL_FILTER_COUNT 1
#elif defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS502)  \
    || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704)                              \
    || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                            \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808)
#    define ADC_DIGITAL_FILTER_COUNT 2
#elif defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506)                         \
    || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CDVL64MC106) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1)                         \
    || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1)                            \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1)                            \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1)                            \
    || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1)                            \
    || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1)                          \
    || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1)                        \
    || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1)                        \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1)                        \
    || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1)                        \
    || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1)                        \
    || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1)                        \
    || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP218S1) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1)                        \
    || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1)                        \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1)                        \
    || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP305S1)                        \
    || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP306S1) || defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP308S1)                        \
    || defined(DEVICE_33CH512MP405) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP406S1)                        \
    || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP408S1) || defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP410S1)                        \
    || defined(DEVICE_33CH512MP412) || defined(DEVICE_33CH512MP412S1) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1)                        \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1)                        \
    || defined(DEVICE_33CH512MP605) || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP606S1)                        \
    || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP608S1) || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP705S1)                        \
    || defined(DEVICE_33CH512MP706) || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP708S1)                        \
    || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP710S1) || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH512MP712S1)                        \
    || defined(DEVICE_33CH1024MP305) || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP306S1)                    \
    || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP308S1) || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP405S1)                    \
    || defined(DEVICE_33CH1024MP406) || defined(DEVICE_33CH1024MP406S1) || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP408S1)                    \
    || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP410S1) || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP412S1)                    \
    || defined(DEVICE_33CH1024MP605) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP606S1)                    \
    || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP608S1) || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP705S1)                    \
    || defined(DEVICE_33CH1024MP706) || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP708S1)                    \
    || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP710S1) || defined(DEVICE_33CH1024MP712) || defined(DEVICE_33CH1024MP712S1)                    \
    || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) \
    || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102) \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) \
    || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) \
    || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106)                            \
    || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506)                            \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                            \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                            \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103)                            \
    || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503)                            \
    || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                            \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305)                            \
    || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406)                            \
    || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                            \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                            \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305)                           \
    || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406)                            \
    || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606)                            \
    || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708)                            \
    || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406)                         \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706)                        \
    || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
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

#if defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208)    \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508)                            \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505)                            \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
// CH primary code
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

#elif defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                         \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505S1)                    \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1)                    \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)
// CH secondary code
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

#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103)  \
    || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)
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

#elif defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)  \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202)                               \
    || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                            \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                            \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205)                            \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306)                            \
    || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                            \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606)                            \
    || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308)                            \
    || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)
// CK MP2/3/5/6XX
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

#ifdef __cplusplus
}
#endif

#endif  // ADC_DSPIC33_SAR12_H
