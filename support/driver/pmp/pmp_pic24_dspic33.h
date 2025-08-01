/**
 * @file pmp_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date August 1, 2025, 05:11 PM
 *
 * @brief Parallel Master Port (PMP) support driver for dsPIC33CK, dsPIC33FJ,
 * dsPIC33EP, dsPIC33EV, PIC24FJ, PIC24EP and PIC24HJ
 */

#ifndef PMP_PIC24_DSPIC33_H
#define PMP_PIC24_DSPIC33_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                               \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_24FJ16GA002) || defined(DEVICE_24FJ16GA004) || defined(DEVICE_24FJ32GA002)                               \
    || defined(DEVICE_24FJ32GA004) || defined(DEVICE_24FJ32GA102) || defined(DEVICE_24FJ32GA104) || defined(DEVICE_24FJ32GB002) || defined(DEVICE_24FJ32GB004) \
    || defined(DEVICE_24FJ48GA002) || defined(DEVICE_24FJ48GA004) || defined(DEVICE_24FJ64GA002) || defined(DEVICE_24FJ64GA004) || defined(DEVICE_24FJ64GA006) \
    || defined(DEVICE_24FJ64GA008) || defined(DEVICE_24FJ64GA010) || defined(DEVICE_24FJ64GA102) || defined(DEVICE_24FJ64GA104) || defined(DEVICE_24FJ64GA106) \
    || defined(DEVICE_24FJ64GA108) || defined(DEVICE_24FJ64GA110) || defined(DEVICE_24FJ64GB002) || defined(DEVICE_24FJ64GB004) || defined(DEVICE_24FJ64GB106) \
    || defined(DEVICE_24FJ64GB108) || defined(DEVICE_24FJ64GB110) || defined(DEVICE_24FJ96GA006) || defined(DEVICE_24FJ96GA008) || defined(DEVICE_24FJ96GA010) \
    || defined(DEVICE_24FJ128GA006) || defined(DEVICE_24FJ128GA008) || defined(DEVICE_24FJ128GA010) || defined(DEVICE_24FJ128GA106)                            \
    || defined(DEVICE_24FJ128GA108) || defined(DEVICE_24FJ128GA110) || defined(DEVICE_24FJ128GB106) || defined(DEVICE_24FJ128GB108)                            \
    || defined(DEVICE_24FJ128GB110) || defined(DEVICE_24FJ192GA106) || defined(DEVICE_24FJ192GA108) || defined(DEVICE_24FJ192GA110)                            \
    || defined(DEVICE_24FJ192GB106) || defined(DEVICE_24FJ192GB108) || defined(DEVICE_24FJ192GB110) || defined(DEVICE_24FJ256GA106)                            \
    || defined(DEVICE_24FJ256GA108) || defined(DEVICE_24FJ256GA110) || defined(DEVICE_24FJ256GB106) || defined(DEVICE_24FJ256GB108)                            \
    || defined(DEVICE_24FJ256GB110) || defined(DEVICE_24HJ32GP302) || defined(DEVICE_24HJ32GP304) || defined(DEVICE_24HJ64GP202)                               \
    || defined(DEVICE_24HJ64GP204) || defined(DEVICE_24HJ64GP502) || defined(DEVICE_24HJ64GP504) || defined(DEVICE_24HJ128GP202)                               \
    || defined(DEVICE_24HJ128GP204) || defined(DEVICE_24HJ128GP502) || defined(DEVICE_24HJ128GP504) || defined(DEVICE_33CDV128MP206)                           \
    || defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP206) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506)                       \
    || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP206)                             \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP206)                               \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP206)                            \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308)                            \
    || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410)                            \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606)                            \
    || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706) || defined(DEVICE_33CK256MP708)                            \
    || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308)                            \
    || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410)                            \
    || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705)                            \
    || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK1024MP405)                           \
    || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705)                        \
    || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710) || defined(DEVICE_33EP128GM306)                         \
    || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM306)                            \
    || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806)                            \
    || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310)                            \
    || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806)                            \
    || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814) || defined(DEVICE_33FJ32GP302) || defined(DEVICE_33FJ32GP304)                              \
    || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) || defined(DEVICE_33FJ64GP202) || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP802) \
    || defined(DEVICE_33FJ64GP804) || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804) \
    || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP802) || defined(DEVICE_33FJ128GP804)                            \
    || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC802) || defined(DEVICE_33FJ128MC804)
#    define PMP_COUNT 1
#else
#    define PMP_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // PMP_PIC24_DSPIC33_H
