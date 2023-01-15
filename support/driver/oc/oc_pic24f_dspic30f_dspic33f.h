/**
 * @file oc_pic24f_dspic30f_dspic33f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver for dsPIC30F, dsPIC33FJ,
 * PIC24F, some PIC24FJ, PIC24FV and PIC24HJ
 *
 * Warning ! PIC24FJxxxGA/GB/GC/DA use oc_pic24e_dspic33e driver
 *
 * Implementation based on Microchip document DS70005159A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005157a.pdf
 */

#ifndef OC_PIC24F_dsPIC30F_dsPIC33F_H
#define OC_PIC24F_dsPIC30F_dsPIC33F_H

#ifdef __cplusplus
extern "C" {
#endif

int oc_setTimer(rt_dev_t device, uint8_t timer);
rt_dev_t oc_getTimer(rt_dev_t device);

#if defined(DEVICE_30F1010) || defined(DEVICE_33FJ06GS101) || defined(DEVICE_33FJ06GS101A) || defined(DEVICE_33FJ06GS102) || defined(DEVICE_33FJ06GS102A)      \
    || defined(DEVICE_33FJ06GS202) || defined(DEVICE_33FJ06GS202A) || defined(DEVICE_33FJ09GS302)
#    define OC_COUNT 1
#elif defined(DEVICE_30F2010) || defined(DEVICE_30F2011) || defined(DEVICE_30F2012) || defined(DEVICE_30F2020) || defined(DEVICE_30F2023)                      \
    || defined(DEVICE_30F3010) || defined(DEVICE_30F3012) || defined(DEVICE_30F3013) || defined(DEVICE_30F3014) || defined(DEVICE_30F4012)                     \
    || defined(DEVICE_33FJ12GP201) || defined(DEVICE_33FJ12GP202) || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202) || defined(DEVICE_33FJ16GP101) \
    || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16GP304) || defined(DEVICE_33FJ16GS402) || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ16GS502) \
    || defined(DEVICE_33FJ16GS504) || defined(DEVICE_33FJ16MC101) || defined(DEVICE_33FJ16MC102) || defined(DEVICE_33FJ16MC304) || defined(DEVICE_33FJ32GP101) \
    || defined(DEVICE_33FJ32GP102) || defined(DEVICE_33FJ32GP104) || defined(DEVICE_33FJ32GP202) || defined(DEVICE_33FJ32GP204) || defined(DEVICE_33FJ32MC101) \
    || defined(DEVICE_33FJ32MC102) || defined(DEVICE_33FJ32MC104) || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC204)
#    define OC_COUNT 2
#elif defined(DEVICE_30F3011) || defined(DEVICE_30F4011) || defined(DEVICE_30F4013) || defined(DEVICE_30F5015) || defined(DEVICE_30F5016)                      \
    || defined(DEVICE_33FJ32GP302) || defined(DEVICE_33FJ32GP304) || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608) \
    || defined(DEVICE_33FJ32GS610) || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) || defined(DEVICE_33FJ64GP202) || defined(DEVICE_33FJ64GP204) \
    || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64GP804) || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608) \
    || defined(DEVICE_33FJ64GS610) || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804) \
    || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP802) || defined(DEVICE_33FJ128GP804)                            \
    || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC802) || defined(DEVICE_33FJ128MC804)
#    define OC_COUNT 4
#elif defined(DEVICE_30F5011) || defined(DEVICE_30F5013) || defined(DEVICE_30F6010) || defined(DEVICE_30F6010A) || defined(DEVICE_30F6011)                     \
    || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012) || defined(DEVICE_30F6012A) || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A)                  \
    || defined(DEVICE_30F6014) || defined(DEVICE_30F6014A) || defined(DEVICE_30F6015) || defined(DEVICE_33FJ64GP206) || defined(DEVICE_33FJ64GP206A)           \
    || defined(DEVICE_33FJ64GP306) || defined(DEVICE_33FJ64GP306A) || defined(DEVICE_33FJ64GP310) || defined(DEVICE_33FJ64GP310A)                              \
    || defined(DEVICE_33FJ64GP706) || defined(DEVICE_33FJ64GP706A) || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A)                              \
    || defined(DEVICE_33FJ64GP710) || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64MC506) || defined(DEVICE_33FJ64MC506A)                              \
    || defined(DEVICE_33FJ64MC508) || defined(DEVICE_33FJ64MC508A) || defined(DEVICE_33FJ64MC510) || defined(DEVICE_33FJ64MC510A)                              \
    || defined(DEVICE_33FJ64MC706) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710) || defined(DEVICE_33FJ64MC710A)                              \
    || defined(DEVICE_33FJ128GP206) || defined(DEVICE_33FJ128GP206A) || defined(DEVICE_33FJ128GP306) || defined(DEVICE_33FJ128GP306A)                          \
    || defined(DEVICE_33FJ128GP310) || defined(DEVICE_33FJ128GP310A) || defined(DEVICE_33FJ128GP706) || defined(DEVICE_33FJ128GP706A)                          \
    || defined(DEVICE_33FJ128GP708) || defined(DEVICE_33FJ128GP708A) || defined(DEVICE_33FJ128GP710) || defined(DEVICE_33FJ128GP710A)                          \
    || defined(DEVICE_33FJ128MC506) || defined(DEVICE_33FJ128MC506A) || defined(DEVICE_33FJ128MC510) || defined(DEVICE_33FJ128MC510A)                          \
    || defined(DEVICE_33FJ128MC706) || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC708) || defined(DEVICE_33FJ128MC708A)                          \
    || defined(DEVICE_33FJ128MC710) || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ256GP506) || defined(DEVICE_33FJ256GP506A)                          \
    || defined(DEVICE_33FJ256GP510) || defined(DEVICE_33FJ256GP510A) || defined(DEVICE_33FJ256GP710) || defined(DEVICE_33FJ256GP710A)                          \
    || defined(DEVICE_33FJ256MC510) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710) || defined(DEVICE_33FJ256MC710A)
#    define OC_COUNT 8
#else
#    define OC_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // OC_PIC24F_dsPIC30F_dsPIC33F_H
