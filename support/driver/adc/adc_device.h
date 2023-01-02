/**
 * @file adc_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date February 14, 2022, 05:26 PM
 *
 * @brief ADC support for specific devices
 */

#ifndef ADC_DEVICE_H
#define ADC_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506)    \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                                \
    || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706)                            \
    || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                            \
    || defined(DEVICE_33EP128GS808) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "adc_dspic33_sar12.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "adc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mk)
#    include "adc_pic32_sar12.h"
#else
#    define ADC_CHANNEL_COUNT      0
#    define ADC_CHANNEL_MAX        0
#    define ADC_MAX_RESOLUTION_BIT 0
#    define ADC_CHANNEL_HAVE_MASK  0x00U

#    define ADC_COMPARATOR_COUNT     0
#    define ADC_DIGITAL_FILTER_COUNT 0
#endif

#ifdef ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_CH0 0
#endif
#ifdef ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_CH1 1
#endif
#ifdef ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_CH2 2
#endif
#ifdef ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_CH3 3
#endif
#ifdef ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_CH4 4
#endif
#ifdef ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_CH5 5
#endif
#ifdef ADC_CHANNEL_HAVE_CH6
#    define ADC_CHANNEL_CH6 6
#endif
#ifdef ADC_CHANNEL_HAVE_CH7
#    define ADC_CHANNEL_CH7 7
#endif
#ifdef ADC_CHANNEL_HAVE_CH8
#    define ADC_CHANNEL_CH8 8
#endif
#ifdef ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_CH9 9
#endif
#ifdef ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_CH10 10
#endif
#ifdef ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_CH11 11
#endif
#ifdef ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_CH12 12
#endif
#ifdef ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_CH13 13
#endif
#ifdef ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_CH14 14
#endif
#ifdef ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_CH15 15
#endif
#ifdef ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_CH16 16
#endif
#ifdef ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_CH17 17
#endif
#ifdef ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_CH18 18
#endif
#ifdef ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_CH19 19
#endif
#ifdef ADC_CHANNEL_HAVE_CH20
#    define ADC_CHANNEL_CH20 20
#endif
#ifdef ADC_CHANNEL_HAVE_CH21
#    define ADC_CHANNEL_CH21 21
#endif
#ifdef ADC_CHANNEL_HAVE_CH22
#    define ADC_CHANNEL_CH22 22
#endif
#ifdef ADC_CHANNEL_HAVE_CH23
#    define ADC_CHANNEL_CH23 23
#endif
#ifdef ADC_CHANNEL_HAVE_CH24
#    define ADC_CHANNEL_CH24 24
#endif
#ifdef ADC_CHANNEL_HAVE_CH25
#    define ADC_CHANNEL_CH25 25
#endif
#ifdef ADC_CHANNEL_HAVE_CH26
#    define ADC_CHANNEL_CH26 26
#endif
#ifdef ADC_CHANNEL_HAVE_CH27
#    define ADC_CHANNEL_CH27 27
#endif
#ifdef ADC_CHANNEL_HAVE_CH28
#    define ADC_CHANNEL_CH28 28
#endif
#ifdef ADC_CHANNEL_HAVE_CH29
#    define ADC_CHANNEL_CH29 29
#endif
#ifdef ADC_CHANNEL_HAVE_CH30
#    define ADC_CHANNEL_CH30 30
#endif
#ifdef ADC_CHANNEL_HAVE_CH31
#    define ADC_CHANNEL_CH31 31
#endif
#ifdef ADC_CHANNEL_HAVE_CH32
#    define ADC_CHANNEL_CH32 32
#endif
#ifdef ADC_CHANNEL_HAVE_CH33
#    define ADC_CHANNEL_CH33 33
#endif
#ifdef ADC_CHANNEL_HAVE_CH34
#    define ADC_CHANNEL_CH34 34
#endif
#ifdef ADC_CHANNEL_HAVE_CH35
#    define ADC_CHANNEL_CH35 35
#endif
#ifdef ADC_CHANNEL_HAVE_CH36
#    define ADC_CHANNEL_CH36 36
#endif
#ifdef ADC_CHANNEL_HAVE_CH37
#    define ADC_CHANNEL_CH37 37
#endif
#ifdef ADC_CHANNEL_HAVE_CH38
#    define ADC_CHANNEL_CH38 38
#endif
#ifdef ADC_CHANNEL_HAVE_CH39
#    define ADC_CHANNEL_CH39 39
#endif
#ifdef ADC_CHANNEL_HAVE_CH40
#    define ADC_CHANNEL_CH40 40
#endif
#ifdef ADC_CHANNEL_HAVE_CH41
#    define ADC_CHANNEL_CH41 41
#endif
#ifdef ADC_CHANNEL_HAVE_CH42
#    define ADC_CHANNEL_CH42 42
#endif
#ifdef ADC_CHANNEL_HAVE_CH43
#    define ADC_CHANNEL_CH43 43
#endif
#ifdef ADC_CHANNEL_HAVE_CH44
#    define ADC_CHANNEL_CH44 44
#endif
#ifdef ADC_CHANNEL_HAVE_CH45
#    define ADC_CHANNEL_CH45 45
#endif
#ifdef ADC_CHANNEL_HAVE_CH46
#    define ADC_CHANNEL_CH46 46
#endif
#ifdef ADC_CHANNEL_HAVE_CH47
#    define ADC_CHANNEL_CH47 47
#endif
#ifdef ADC_CHANNEL_HAVE_CH48
#    define ADC_CHANNEL_CH48 48
#endif
#ifdef ADC_CHANNEL_HAVE_CH49
#    define ADC_CHANNEL_CH49 49
#endif
#ifdef ADC_CHANNEL_HAVE_CH50
#    define ADC_CHANNEL_CH50 50
#endif
#ifdef ADC_CHANNEL_HAVE_CH51
#    define ADC_CHANNEL_CH51 51
#endif
#ifdef ADC_CHANNEL_HAVE_CH52
#    define ADC_CHANNEL_CH52 52
#endif
#ifdef ADC_CHANNEL_HAVE_CH53
#    define ADC_CHANNEL_CH53 53
#endif
#ifdef ADC_CHANNEL_HAVE_CH54
#    define ADC_CHANNEL_CH54 54
#endif
#ifdef ADC_CHANNEL_HAVE_CH55
#    define ADC_CHANNEL_CH55 55
#endif
#ifdef ADC_CHANNEL_HAVE_CH56
#    define ADC_CHANNEL_CH56 56
#endif
#ifdef ADC_CHANNEL_HAVE_CH57
#    define ADC_CHANNEL_CH57 57
#endif
#ifdef ADC_CHANNEL_HAVE_CH58
#    define ADC_CHANNEL_CH58 58
#endif
#ifdef ADC_CHANNEL_HAVE_CH59
#    define ADC_CHANNEL_CH59 59
#endif
#ifdef ADC_CHANNEL_HAVE_CH60
#    define ADC_CHANNEL_CH60 60
#endif

#ifdef __cplusplus
}
#endif

#endif  // ADC_DEVICE_H
