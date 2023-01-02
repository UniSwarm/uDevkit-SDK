/**
 * @file adc_pic32mm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 2, 2023, 05:24 PM
 *
 * @brief ADC driver support for PIC32MM GPL/GPM
 *
 * Implementation based on Microchip document DS60001344B :
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/60001359b.pdf
 */

#ifndef ADC_PIC32MM_H
#define ADC_PIC32MM_H

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_RESOLUTION_BIT 12

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0064GPL020)
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
#    define ADC_CHANNEL_HAVE_MASK 0x07FFLU
#    define ADC_CHANNEL_COUNT     11
#    define ADC_CHANNEL_MAX       10
#elif defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0064GPL028)
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
#    define ADC_CHANNEL_HAVE_MASK 0x0FFFLU
#    define ADC_CHANNEL_COUNT     12
#    define ADC_CHANNEL_MAX       11
#elif defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL036) || defined(DEVICE_32MM0064GPL036)
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
#    define ADC_CHANNEL_HAVE_MASK 0x3FFFLU
#    define ADC_CHANNEL_COUNT     14
#    define ADC_CHANNEL_MAX       13
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0256GPM028)
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
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH16
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_CH18
#    define ADC_CHANNEL_HAVE_CH19
#    define ADC_CHANNEL_HAVE_MASK 0x000FDFFFLU
#    define ADC_CHANNEL_COUNT     19
#    define ADC_CHANNEL_MAX       19
#elif defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM036)                     \
    || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048)                    \
    || defined(DEVICE_32MM0256GPM064)
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
#    define ADC_CHANNEL_HAVE_MASK 0x000FFFFFLU
#    define ADC_CHANNEL_COUNT     20
#    define ADC_CHANNEL_MAX       19
#endif

#define ADC_COMPARATOR_COUNT     0
#define ADC_DIGITAL_FILTER_COUNT 0

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0016GPL028)                       \
    || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL036)                    \
    || defined(DEVICE_32MM0064GPL036)
// interrupt bits helpers for PIC32MM GPL
#    ifndef _AD1IE
#        define _AD1IE IEC0bits.AD1IE
#        define _AD1IF IFS0bits.AD1IF
#        define _AD1IP IPC3bits.AD1IP
#        define _AD1IS IPC3bits.AD1IS
#    endif

#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0256GPM028) || defined(DEVICE_32MM0064GPM036)                     \
    || defined(DEVICE_32MM0064GPM048) || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM036) || defined(DEVICE_32MM0128GPM048)                    \
    || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
// interrupt bits helpers for PIC32MM GPM
#    ifndef _AD1IE
#        define _AD1IE IEC1bits.AD1IE
#        define _AD1IF IFS1bits.AD1IF
#        define _AD1IP IPC8bits.AD1IP
#        define _AD1IS IPC8bits.AD1IS
#    endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // ADC_PIC32MM_H
