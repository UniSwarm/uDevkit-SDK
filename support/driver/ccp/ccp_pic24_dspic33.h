/**
 * @file ccp_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
 *
 * @date December 17, 2018, 23:00 PM
 *
 * @brief CCP capture/compare/PWM/Timer support driver for PIC24 and dsPIC33C
 *
 * Implementation based on Microchip document DS30003035B:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/30003035b.pdf
 */

#ifndef CCP_PIC24_DSPIC33_H
#define CCP_PIC24_DSPIC33_H

#if defined(DEVICE_24F08KM101) || defined(DEVICE_24F08KM102) || defined(DEVICE_24F16KM102) || defined(DEVICE_24F16KM104) || defined(DEVICE_24FV08KM101)        \
    || defined(DEVICE_24FV08KM102) || defined(DEVICE_24FV16KM102) || defined(DEVICE_24FV16KM104)
#    define CCP_COUNT 2
#elif defined(DEVICE_24FJ64GA702) || defined(DEVICE_24FJ64GA704) || defined(DEVICE_24FJ64GA705) || defined(DEVICE_24FJ128GA702)                                \
    || defined(DEVICE_24FJ128GA704) || defined(DEVICE_24FJ128GA705) || defined(DEVICE_24FJ256GA702) || defined(DEVICE_24FJ256GA704)                            \
    || defined(DEVICE_24FJ256GA705) || defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDVL64MC106) || defined(DEVICE_33CH64MP202S1)                          \
    || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208S1)                        \
    || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506S1)                        \
    || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205S1)                     \
    || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503S1)                    \
    || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205S1)                    \
    || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1) || defined(DEVICE_33CH256MP505S1)                    \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1)                    \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)                    \
    || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) \
    || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105)                             \
    || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505)                            \
    || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105)                            \
    || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505)                            \
    || defined(DEVICE_33CK256MC506)
#    define CCP_COUNT 4
#elif defined(DEVICE_24F08KM202) || defined(DEVICE_24F08KM204) || defined(DEVICE_24F16KM202) || defined(DEVICE_24F16KM204) || defined(DEVICE_24FJ32GP202)      \
    || defined(DEVICE_24FJ32GP203) || defined(DEVICE_24FJ32GP205) || defined(DEVICE_24FJ32GU202) || defined(DEVICE_24FJ32GU203) || defined(DEVICE_24FJ32GU205) \
    || defined(DEVICE_24FJ64GL302) || defined(DEVICE_24FJ64GL303) || defined(DEVICE_24FJ64GL305) || defined(DEVICE_24FJ64GL306) || defined(DEVICE_24FJ64GP202) \
    || defined(DEVICE_24FJ64GP203) || defined(DEVICE_24FJ64GP205) || defined(DEVICE_24FJ64GU202) || defined(DEVICE_24FJ64GU203) || defined(DEVICE_24FJ64GU205) \
    || defined(DEVICE_24FJ128GL302) || defined(DEVICE_24FJ128GL303) || defined(DEVICE_24FJ128GL305) || defined(DEVICE_24FJ128GL306)                            \
    || defined(DEVICE_24FV08KM202) || defined(DEVICE_24FV08KM204) || defined(DEVICE_24FV16KM202) || defined(DEVICE_24FV16KM204) || defined(DEVICE_33CK32MP102) \
    || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)
#    define CCP_COUNT 5
#elif defined(DEVICE_24FJ64GA406) || defined(DEVICE_24FJ64GA410) || defined(DEVICE_24FJ64GA412) || defined(DEVICE_24FJ64GB406) || defined(DEVICE_24FJ64GB410)  \
    || defined(DEVICE_24FJ64GB412) || defined(DEVICE_24FJ128GA406) || defined(DEVICE_24FJ128GA410) || defined(DEVICE_24FJ128GA412)                             \
    || defined(DEVICE_24FJ128GA606) || defined(DEVICE_24FJ128GA610) || defined(DEVICE_24FJ128GB406) || defined(DEVICE_24FJ128GB410)                            \
    || defined(DEVICE_24FJ128GB412) || defined(DEVICE_24FJ128GB606) || defined(DEVICE_24FJ128GB610) || defined(DEVICE_24FJ128GL405)                            \
    || defined(DEVICE_24FJ128GU405) || defined(DEVICE_24FJ256GA406) || defined(DEVICE_24FJ256GA410) || defined(DEVICE_24FJ256GA412)                            \
    || defined(DEVICE_24FJ256GA606) || defined(DEVICE_24FJ256GA610) || defined(DEVICE_24FJ256GB406) || defined(DEVICE_24FJ256GB410)                            \
    || defined(DEVICE_24FJ256GB412) || defined(DEVICE_24FJ256GB606) || defined(DEVICE_24FJ256GB610) || defined(DEVICE_24FJ256GL405)                            \
    || defined(DEVICE_24FJ256GU405) || defined(DEVICE_24FJ512GA606) || defined(DEVICE_24FJ512GA610) || defined(DEVICE_24FJ512GB606)                            \
    || defined(DEVICE_24FJ512GB610) || defined(DEVICE_24FJ512GL405) || defined(DEVICE_24FJ512GU405) || defined(DEVICE_24FJ1024GA606)                           \
    || defined(DEVICE_24FJ1024GA610) || defined(DEVICE_24FJ1024GB606) || defined(DEVICE_24FJ1024GB610)
#    define CCP_COUNT 7
#elif defined(DEVICE_24FJ128GL406) || defined(DEVICE_24FJ128GL408) || defined(DEVICE_24FJ128GL410) || defined(DEVICE_24FJ128GU406)                             \
    || defined(DEVICE_24FJ128GU408) || defined(DEVICE_24FJ128GU410) || defined(DEVICE_24FJ256GL406) || defined(DEVICE_24FJ256GL408)                            \
    || defined(DEVICE_24FJ256GL410) || defined(DEVICE_24FJ256GU406) || defined(DEVICE_24FJ256GU408) || defined(DEVICE_24FJ256GU410)                            \
    || defined(DEVICE_24FJ512GL406) || defined(DEVICE_24FJ512GL408) || defined(DEVICE_24FJ512GL410) || defined(DEVICE_24FJ512GU406)                            \
    || defined(DEVICE_24FJ512GU408) || defined(DEVICE_24FJ512GU410) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203)                              \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) \
    || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH128MP202)                               \
    || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP208)                            \
    || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP506)                            \
    || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP208)                            \
    || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508)                            \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505)                            \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
#    define CCP_COUNT 8
#elif defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506)                       \
    || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202)                               \
    || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                            \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                            \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205)                            \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306)                            \
    || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408)                            \
    || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                            \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606)                            \
    || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706) || defined(DEVICE_33CK256MP708)                            \
    || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308)                            \
    || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410)                            \
    || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705)                            \
    || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK1024MP405)                           \
    || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705)                        \
    || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
#    define CCP_COUNT 9
#else
#    define CCP_COUNT 0
#endif

#endif  // CCP_PIC24_DSPIC33_H
