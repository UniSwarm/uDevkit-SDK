/**
 * @file oc_pic24e_dspic33e.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver for PIC24EP, dspic33EP,
 * dsPIC33EV and PIC24FJxxxGA/GB/GC/DA
 *
 * Implementation based on Microchip document DS70005159A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005159a.pdf
 */

#ifndef OC_PIC24E_dsPIC33E_H
#define OC_PIC24E_dsPIC33E_H

#ifdef __cplusplus
extern "C" {
#endif

#define OC_HAVE_INDEPENDENT_TIMER

#if defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define OC_COUNT 1
#elif defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)  \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206)                            \
    || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204) || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512MC202)                            \
    || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP16GS502)                             \
    || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) \
    || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) \
    || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) \
    || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) \
    || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) \
    || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP64MC202) \
    || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) \
    || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504)                              \
    || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                            \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                            \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808) || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204)                            \
    || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506)                            \
    || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504) || defined(DEVICE_33EP256GP506) || defined(DEVICE_33EP256MC202)                            \
    || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504)                            \
    || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506)                            \
    || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502)                            \
    || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003)                              \
    || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) \
    || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) \
    || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106)                                \
    || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006)                            \
    || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106)                            \
    || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006)                            \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define OC_COUNT 4
#elif defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM604)                             \
    || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306)                            \
    || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710)                            \
    || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604)                            \
    || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710)
#    define OC_COUNT 8
#elif defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                             \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814)                            \
    || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
#    define OC_COUNT 16
#else
#    define OC_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // OC_PIC24E_dsPIC33E_H
