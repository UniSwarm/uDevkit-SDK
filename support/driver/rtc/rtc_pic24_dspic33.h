/**
 * @file rtc_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date May 07, 2017, 17:37 PM
 *
 * @brief RTC driver support for dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70301C, DS70584B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70301C.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/S29.pdf
 */

#ifndef RTC_PIC24_DSPIC33_H
#define RTC_PIC24_DSPIC33_H

#if defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM604)                               \
    || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306)                            \
    || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710)                            \
    || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM304)                            \
    || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706)                            \
    || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810)                            \
    || defined(DEVICE_33EP512MU814) || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP802)                            \
    || defined(DEVICE_33FJ128GP804) || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC802)                            \
    || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ16GP101) || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16MC101)                               \
    || defined(DEVICE_33FJ16MC102) || defined(DEVICE_33FJ32GP101) || defined(DEVICE_33FJ32GP102) || defined(DEVICE_33FJ32GP104) || defined(DEVICE_33FJ32GP302) \
    || defined(DEVICE_33FJ32GP304) || defined(DEVICE_33FJ32MC101) || defined(DEVICE_33FJ32MC102) || defined(DEVICE_33FJ32MC104) || defined(DEVICE_33FJ32MC302) \
    || defined(DEVICE_33FJ32MC304) || defined(DEVICE_33FJ64GP202) || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64GP804) \
    || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804)                                \
    || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                            \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_24F08KA101) || defined(DEVICE_24F08KA102) || defined(DEVICE_24F08KM202) || defined(DEVICE_24F08KM204)    \
    || defined(DEVICE_24F16KA101) || defined(DEVICE_24F16KA102) || defined(DEVICE_24F16KA301) || defined(DEVICE_24F16KA302) || defined(DEVICE_24F16KA304)      \
    || defined(DEVICE_24F16KM202) || defined(DEVICE_24F16KM204) || defined(DEVICE_24F32KA301) || defined(DEVICE_24F32KA302) || defined(DEVICE_24F32KA304)      \
    || defined(DEVICE_24FJ128DA106) || defined(DEVICE_24FJ128DA110) || defined(DEVICE_24FJ128DA206) || defined(DEVICE_24FJ128DA210)                            \
    || defined(DEVICE_24FJ128GA006) || defined(DEVICE_24FJ128GA008) || defined(DEVICE_24FJ128GA010) || defined(DEVICE_24FJ128GA106)                            \
    || defined(DEVICE_24FJ128GA108) || defined(DEVICE_24FJ128GA110) || defined(DEVICE_24FJ128GA202) || defined(DEVICE_24FJ128GA204)                            \
    || defined(DEVICE_24FJ128GA306) || defined(DEVICE_24FJ128GA308) || defined(DEVICE_24FJ128GA310) || defined(DEVICE_24FJ128GB106)                            \
    || defined(DEVICE_24FJ128GB108) || defined(DEVICE_24FJ128GB110) || defined(DEVICE_24FJ128GB202) || defined(DEVICE_24FJ128GB204)                            \
    || defined(DEVICE_24FJ128GB206) || defined(DEVICE_24FJ128GB210) || defined(DEVICE_24FJ128GC006) || defined(DEVICE_24FJ128GC010)                            \
    || defined(DEVICE_24FJ16GA002) || defined(DEVICE_24FJ16GA004) || defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102)                                \
    || defined(DEVICE_24FJ192GA106) || defined(DEVICE_24FJ192GA108) || defined(DEVICE_24FJ192GA110) || defined(DEVICE_24FJ192GB106)                            \
    || defined(DEVICE_24FJ192GB108) || defined(DEVICE_24FJ192GB110) || defined(DEVICE_24FJ256DA106) || defined(DEVICE_24FJ256DA110)                            \
    || defined(DEVICE_24FJ256DA206) || defined(DEVICE_24FJ256DA210) || defined(DEVICE_24FJ256GA106) || defined(DEVICE_24FJ256GA108)                            \
    || defined(DEVICE_24FJ256GA110) || defined(DEVICE_24FJ256GB106) || defined(DEVICE_24FJ256GB108) || defined(DEVICE_24FJ256GB110)                            \
    || defined(DEVICE_24FJ256GB206) || defined(DEVICE_24FJ256GB210) || defined(DEVICE_24FJ32GA002) || defined(DEVICE_24FJ32GA004)                              \
    || defined(DEVICE_24FJ32GA102) || defined(DEVICE_24FJ32GA104) || defined(DEVICE_24FJ32GB002) || defined(DEVICE_24FJ32GB004) || defined(DEVICE_24FJ32MC101) \
    || defined(DEVICE_24FJ32MC102) || defined(DEVICE_24FJ32MC104) || defined(DEVICE_24FJ48GA002) || defined(DEVICE_24FJ48GA004) || defined(DEVICE_24FJ64GA002) \
    || defined(DEVICE_24FJ64GA004) || defined(DEVICE_24FJ64GA006) || defined(DEVICE_24FJ64GA008) || defined(DEVICE_24FJ64GA010) || defined(DEVICE_24FJ64GA102) \
    || defined(DEVICE_24FJ64GA104) || defined(DEVICE_24FJ64GA106) || defined(DEVICE_24FJ64GA108) || defined(DEVICE_24FJ64GA110) || defined(DEVICE_24FJ64GA202) \
    || defined(DEVICE_24FJ64GA204) || defined(DEVICE_24FJ64GA306) || defined(DEVICE_24FJ64GA308) || defined(DEVICE_24FJ64GA310) || defined(DEVICE_24FJ64GB002) \
    || defined(DEVICE_24FJ64GB004) || defined(DEVICE_24FJ64GB106) || defined(DEVICE_24FJ64GB108) || defined(DEVICE_24FJ64GB110) || defined(DEVICE_24FJ64GB202) \
    || defined(DEVICE_24FJ64GB204) || defined(DEVICE_24FJ64GC006) || defined(DEVICE_24FJ64GC010) || defined(DEVICE_24FJ96GA006) || defined(DEVICE_24FJ96GA008) \
    || defined(DEVICE_24FJ96GA010) || defined(DEVICE_24FV08KM202) || defined(DEVICE_24FV08KM204) || defined(DEVICE_24FV16KA301) || defined(DEVICE_24FV16KA302) \
    || defined(DEVICE_24FV16KA304) || defined(DEVICE_24FV16KM202) || defined(DEVICE_24FV16KM204) || defined(DEVICE_24FV32KA301) || defined(DEVICE_24FV32KA302) \
    || defined(DEVICE_24FV32KA304) || defined(DEVICE_24HJ128GP202) || defined(DEVICE_24HJ128GP204) || defined(DEVICE_24HJ128GP502)                             \
    || defined(DEVICE_24HJ128GP504) || defined(DEVICE_24HJ32GP302) || defined(DEVICE_24HJ32GP304) || defined(DEVICE_24HJ64GP202)                               \
    || defined(DEVICE_24HJ64GP204) || defined(DEVICE_24HJ64GP502) || defined(DEVICE_24HJ64GP504)
#    define RTC_COUNT 1
#else
#    define RTC_COUNT 0
#endif

#endif  // RTC_PIC24_DSPIC33_H
