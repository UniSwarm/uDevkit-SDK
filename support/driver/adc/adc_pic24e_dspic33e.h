/**
 * @file adc_pic24e_dspic33e.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 19, 2016, 10:56 AM
 *
 * @brief ADC driver support for dsPIC33EP, dsPIC33EV and PIC24EP
 *
 * Implementation based on Microchip document DS70621C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70621c.pdf
 */

#ifndef ADC_PIC24E_DSPIC33E_H
#define ADC_PIC24E_DSPIC33E_H

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_RESOLUTION_BIT 10

// ====================================== Channel availability ======================================
#if defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)    \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206)                            \
    || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204) || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512MC202)                            \
    || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP32GP502)                             \
    || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) \
    || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) || defined(DEVICE_33EP64GP503) \
    || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) \
    || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) \
    || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128MC202)                            \
    || defined(DEVICE_33EP128MC204) || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504)                            \
    || defined(DEVICE_33EP128MC506) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504) || defined(DEVICE_33EP256GP506)                            \
    || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502)                            \
    || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504)                            \
    || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206)                            \
    || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506)
#    define ADC_CHANNEL_COUNT 21
#elif defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003) || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102)  \
    || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) \
    || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) \
    || defined(DEVICE_33EV64GM106) || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004)                             \
    || defined(DEVICE_33EV128GM006) || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104)                            \
    || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004)                            \
    || defined(DEVICE_33EV256GM006) || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104)                            \
    || defined(DEVICE_33EV256GM106)
#    define ADC_CHANNEL_COUNT 28
#elif defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                             \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310)                            \
    || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304)                            \
    || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706)                            \
    || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814)                            \
    || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604)                            \
    || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806)                            \
    || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
#    define ADC_CHANNEL_COUNT 32
#else
#    define ADC_CHANNEL_COUNT 0
#endif

#if defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)    \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP256MC202)                            \
    || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206) || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204)                            \
    || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512GU814)                            \
    || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_33EDV64MC205)                            \
    || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) \
    || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) \
    || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) \
    || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) \
    || defined(DEVICE_33EP64MC506) || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310)                             \
    || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP128GP502)                            \
    || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204)                            \
    || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506)                            \
    || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604)                            \
    || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504)                            \
    || defined(DEVICE_33EP256GP506) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206)                            \
    || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP256MU806)                            \
    || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306)                            \
    || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710)                            \
    || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512GP806)                            \
    || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502)                            \
    || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810)                            \
    || defined(DEVICE_33EP512MU814) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003) || defined(DEVICE_33EV32GM004)                               \
    || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) \
    || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) \
    || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106) || defined(DEVICE_33EV128GM002)                               \
    || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006) || defined(DEVICE_33EV128GM102)                            \
    || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM002)                            \
    || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006) || defined(DEVICE_33EV256GM102)                            \
    || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define ADC_CHANNEL_MAX 32
#endif

#if defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                               \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310)                            \
    || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304)                            \
    || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706)                            \
    || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814)                            \
    || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604)                            \
    || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806)                            \
    || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
#    define ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_HAVE_CH23
#endif
#if defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                               \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310)                            \
    || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304)                            \
    || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706)                            \
    || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814)                            \
    || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604)                            \
    || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806)                            \
    || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003)                              \
    || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) \
    || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) \
    || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106)                                \
    || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006)                            \
    || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106)                            \
    || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006)                            \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_HAVE_CH29
#endif
#if defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)    \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP256MC202)                            \
    || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206) || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204)                            \
    || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512GU814)                            \
    || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_33EDV64MC205)                            \
    || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) \
    || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) \
    || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) \
    || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) \
    || defined(DEVICE_33EP64MC506) || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310)                             \
    || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP128GP502)                            \
    || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204)                            \
    || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506)                            \
    || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604)                            \
    || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504)                            \
    || defined(DEVICE_33EP256GP506) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206)                            \
    || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP256MU806)                            \
    || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306)                            \
    || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710)                            \
    || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512GP806)                            \
    || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502)                            \
    || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810)                            \
    || defined(DEVICE_33EP512MU814) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003) || defined(DEVICE_33EV32GM004)                               \
    || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) \
    || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) \
    || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106) || defined(DEVICE_33EV128GM002)                               \
    || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006) || defined(DEVICE_33EV128GM102)                            \
    || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM002)                            \
    || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006) || defined(DEVICE_33EV256GM102)                            \
    || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define ADC_CHANNEL_HAVE_CH0
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
#    define ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_HAVE_CH31
#endif

#ifdef __cplusplus
}
#endif

#endif  // ADC_PIC24E_DSPIC33E_H
