/**
 * @file adc_pic32mx.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2023
 *
 * @date May 15, 2023, 07:06 PM
 *
 * @brief .....
 */

#ifndef ADC_PIC32MX_H
#define ADC_PIC32MX_H

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_RESOLUTION_BIT 10

#if defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B)                               \
    || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C)                            \
    || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B)                            \
    || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D)                            \
    || defined(DEVICE_32MX210F016B) || defined(DEVICE_32MX210F016C) || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B)                            \
    || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D) || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F064C)                            \
    || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) || defined(DEVICE_32MX250F128B)                            \
    || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX250F128D) || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D)                            \
    || defined(DEVICE_32MX320F032H) || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX320F128L)                            \
    || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F128L) || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H)                            \
    || defined(DEVICE_32MX360F256L) || defined(DEVICE_32MX360F512L) || defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX440F128H)                            \
    || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H) || defined(DEVICE_32MX460F256L)                            \
    || defined(DEVICE_32MX460F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX564F064H)                            \
    || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX575F256H)                            \
    || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064H)                            \
    || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256H)                            \
    || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512H)                            \
    || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L) || defined(DEVICE_32MX775F256H)                            \
    || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512H)                            \
    || defined(DEVICE_32MX795F512L)
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
#    define ADC_CHANNEL_HAVE_MASK 0xFFFFLU
#    define ADC_CHANNEL_COUNT     16
#    define ADC_CHANNEL_MAX       15
#elif defined(DEVICE_32MX254F128B) || defined(DEVICE_32MX274F256B)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_MASK 0x0002EE3FLU
#    define ADC_CHANNEL_COUNT     13
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_32MX254F128D) || defined(DEVICE_32MX274F256D)
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
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_MASK 0x0002EFFFLU
#    define ADC_CHANNEL_COUNT     16
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX174F256B)
#    define ADC_CHANNEL_HAVE_CH0
#    define ADC_CHANNEL_HAVE_CH1
#    define ADC_CHANNEL_HAVE_CH2
#    define ADC_CHANNEL_HAVE_CH3
#    define ADC_CHANNEL_HAVE_CH4
#    define ADC_CHANNEL_HAVE_CH5
#    define ADC_CHANNEL_HAVE_CH9
#    define ADC_CHANNEL_HAVE_CH10
#    define ADC_CHANNEL_HAVE_CH11
#    define ADC_CHANNEL_HAVE_CH12
#    define ADC_CHANNEL_HAVE_CH13
#    define ADC_CHANNEL_HAVE_CH14
#    define ADC_CHANNEL_HAVE_CH15
#    define ADC_CHANNEL_HAVE_CH17
#    define ADC_CHANNEL_HAVE_MASK 0x0002FE3FLU
#    define ADC_CHANNEL_COUNT     14
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_32MX154F128D) || defined(DEVICE_32MX174F256D)
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
#    define ADC_CHANNEL_HAVE_MASK 0x0002FFFFLU
#    define ADC_CHANNEL_COUNT     17
#    define ADC_CHANNEL_MAX       17
#elif defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX170F512H)                             \
    || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX530F128H)                            \
    || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H)
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
#elif defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F128L)                             \
    || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX370F512L)                            \
    || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F128L)                            \
    || defined(DEVICE_32MX450F256H) || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX470F512H) || defined(DEVICE_32MX470F512L)
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
#    define ADC_CHANNEL_HAVE_MASK 0x7FFFFFFFLU
#    define ADC_CHANNEL_COUNT     31
#    define ADC_CHANNEL_MAX       30
#elif defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX230F128L)                             \
    || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX550F256L)                            \
    || defined(DEVICE_32MX570F512L)
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
#    define ADC_CHANNEL_HAVE_CH32
#    define ADC_CHANNEL_HAVE_CH33
#    define ADC_CHANNEL_HAVE_CH34
#    define ADC_CHANNEL_HAVE_CH35
#    define ADC_CHANNEL_HAVE_CH36
#    define ADC_CHANNEL_HAVE_CH37
#    define ADC_CHANNEL_HAVE_CH38
#    define ADC_CHANNEL_HAVE_CH39
#    define ADC_CHANNEL_HAVE_CH40
#    define ADC_CHANNEL_HAVE_CH41
#    define ADC_CHANNEL_HAVE_CH42
#    define ADC_CHANNEL_HAVE_CH43
#    define ADC_CHANNEL_HAVE_CH44
#    define ADC_CHANNEL_HAVE_CH45
#    define ADC_CHANNEL_HAVE_CH46
#    define ADC_CHANNEL_HAVE_CH47
#    define ADC_CHANNEL_HAVE_CH48
#    define ADC_CHANNEL_HAVE_CH49
#    define ADC_CHANNEL_HAVE_CH50
#    define ADC_CHANNEL_HAVE_CH51
#    define ADC_CHANNEL_HAVE_CH52
#    define ADC_CHANNEL_HAVE_CH53
#    define ADC_CHANNEL_HAVE_MASK 0x003FFFFFFFFFFFFFLU
#    define ADC_CHANNEL_COUNT     54
#    define ADC_CHANNEL_MAX       53
#endif

#define ADC_COMPARATOR_COUNT     0
#define ADC_DIGITAL_FILTER_COUNT 0

#ifdef __cplusplus
}
#endif

#endif  // ADC_PIC32MX_H
