/**
 * @file adc_pic32_sar12.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date May 07, 2017, 10:07 AM
 *
 * @brief ADC driver support for PIC32MZDA and PIC32MZEF
 *
 * Implementation based on Microchip document DS60001344B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001344B.pdf
 */

#ifndef ADC_PIC32MZ_H
#define ADC_PIC32MZ_H

// ====================================== Channel availability ======================================
#if defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ1024EFE064)                       \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFK064)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFM064)
#    define ADC_COUNT 21
#elif defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512MCF064)                     \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPK064)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCM064)
#    define ADC_COUNT 30
#elif defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ1024EFE100)                     \
    || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFK100)                    \
    || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFM100)
#    define ADC_COUNT 37
#elif defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                     \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_COUNT 44
#elif defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                     \
    || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)
#    define ADC_COUNT 45
#elif defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                     \
    || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064)                    \
    || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM100)
#    define ADC_COUNT 46
#else
#    define ADC_COUNT 0
#endif

#if defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                       \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_CHANNEL_MAX 44
#elif defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                     \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144)                    \
    || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)
#    define ADC_CHANNEL_MAX 45
#elif defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                     \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define ADC_CHANNEL_MAX 54
#endif

#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064)                    \
    || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM100)
#    define ADC_HAVE_CH45
#    define ADC_HAVE_CH46
#    define ADC_HAVE_CH47
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define ADC_HAVE_CH48
#    define ADC_HAVE_CH49
#    define ADC_HAVE_CH50
#    define ADC_HAVE_CH51
#    define ADC_HAVE_CH52
#    define ADC_HAVE_CH53
#endif
#if defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                       \
    || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176)                    \
    || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288)                    \
    || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176)                    \
    || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176)                    \
    || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176) || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176)                    \
    || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169)                    \
    || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176)                    \
    || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176)                    \
    || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176)                    \
    || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176)                    \
    || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169) || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288)                    \
    || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176)                    \
    || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176)                    \
    || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176) || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH42
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064)                    \
    || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                    \
    || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                    \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)                    \
    || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169)                    \
    || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288) || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176)                    \
    || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176)                    \
    || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176) || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176)                    \
    || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH35
#    define ADC_HAVE_CH36
#    define ADC_HAVE_CH37
#    define ADC_HAVE_CH38
#    define ADC_HAVE_CH39
#    define ADC_HAVE_CH40
#    define ADC_HAVE_CH41
#endif
#if defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF100)                       \
    || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124)                    \
    || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG100)                    \
    || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124)                    \
    || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169)                    \
    || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176)                    \
    || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169)                    \
    || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169)                    \
    || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176) || defined(DEVICE_32MZ1025DAS169)                    \
    || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288)                    \
    || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169)                    \
    || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ1064DAK169)                    \
    || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169)                    \
    || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169)                    \
    || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169) || defined(DEVICE_32MZ2025DAB176)                    \
    || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169)                    \
    || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169)                    \
    || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176) || defined(DEVICE_32MZ2025DAS169)                    \
    || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH28
#    define ADC_HAVE_CH29
#    define ADC_HAVE_CH30
#    define ADC_HAVE_CH31
#    define ADC_HAVE_CH32
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064)                    \
    || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM100) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124)                    \
    || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024EFE100)                    \
    || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124)                    \
    || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK100)                    \
    || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124)                    \
    || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288)                    \
    || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169)                    \
    || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169)                    \
    || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169)                    \
    || defined(DEVICE_32MZ1025DAR176) || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169)                    \
    || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176)                    \
    || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169)                    \
    || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169)                    \
    || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169)                    \
    || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288)                    \
    || defined(DEVICE_32MZ2025DAB169) || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169)                    \
    || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169)                    \
    || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169)                    \
    || defined(DEVICE_32MZ2025DAR176) || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG100)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124)                    \
    || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)                    \
    || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169)                    \
    || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288) || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176)                    \
    || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176)                    \
    || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176) || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176)                    \
    || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH20
#    define ADC_HAVE_CH21
#    define ADC_HAVE_CH22
#    define ADC_HAVE_CH23
#    define ADC_HAVE_CH33
#    define ADC_HAVE_CH34
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF100)                    \
    || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124)                    \
    || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG100)                    \
    || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124)                    \
    || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169)                    \
    || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176)                    \
    || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169)                    \
    || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169)                    \
    || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176) || defined(DEVICE_32MZ1025DAS169)                    \
    || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288)                    \
    || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169)                    \
    || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ1064DAK169)                    \
    || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169)                    \
    || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169)                    \
    || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169) || defined(DEVICE_32MZ2025DAB176)                    \
    || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169)                    \
    || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169)                    \
    || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176) || defined(DEVICE_32MZ2025DAS169)                    \
    || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH19
#    define ADC_HAVE_CH24
#    define ADC_HAVE_CH25
#    define ADC_HAVE_CH26
#    define ADC_HAVE_CH27
#endif
#if defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                       \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144)                    \
    || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)
#    define ADC_HAVE_CH44
#endif
#if defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                       \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                    \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH43
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                    \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                    \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_CH0
#    define ADC_HAVE_CH1
#    define ADC_HAVE_CH2
#    define ADC_HAVE_CH3
#    define ADC_HAVE_CH4
#    define ADC_HAVE_CH5
#    define ADC_HAVE_CH6
#    define ADC_HAVE_CH7
#    define ADC_HAVE_CH8
#    define ADC_HAVE_CH9
#    define ADC_HAVE_CH10
#    define ADC_HAVE_CH11
#    define ADC_HAVE_CH12
#    define ADC_HAVE_CH13
#    define ADC_HAVE_CH14
#    define ADC_HAVE_CH15
#    define ADC_HAVE_CH16
#    define ADC_HAVE_CH17
#    define ADC_HAVE_CH18
#endif

// ==================================== Dedicated core availability ====================================
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064) || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100)                    \
    || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100) || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCM064)                    \
    || defined(DEVICE_32MK1024MCM100)
#    define ADC_HAVE_DEDICATED_CORE6
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define ADC_HAVE_DEDICATED_CORE5
#endif
#if defined(DEVICE_32MK0256GPG048) || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064)                       \
    || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                    \
    || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100)                    \
    || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144)                    \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                    \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define ADC_HAVE_DEDICATED_CORE0
#    define ADC_HAVE_DEDICATED_CORE1
#    define ADC_HAVE_DEDICATED_CORE2
#    define ADC_HAVE_DEDICATED_CORE3
#    define ADC_HAVE_DEDICATED_CORE4
#    define ADC_HAVE_DEDICATED_CORE7
#endif

#endif  // ADC_PIC32MZ_H
