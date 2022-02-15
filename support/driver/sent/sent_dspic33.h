/**
 * @file sent_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2017-2021
 *
 * @date November 17, 2017, 16:10 PM
 *
 * @brief SAE J2716 SENT (Single Edge Nibble Transmission) support driver for dsPIC33EV, dsPIC33CH
 * and dsPIC33CK
 *
 * Implementation based on Microchip document DS70005145B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005145b.pdf
 */

#ifndef SENT_DSPIC33_H
#define SENT_DSPIC33_H

#if defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDVL64MC106) || defined(DEVICE_33CK32MC102)                       \
    || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK64MC102)                       \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK128MC102)                      \
    || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106)                    \
    || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505)                    \
    || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103)                    \
    || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502)                    \
    || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506)
#    define SENT_COUNT 1
#elif defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506)                 \
    || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203)                    \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208)                       \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505)                       \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH128MP202)                      \
    || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                    \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503)                    \
    || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508)                    \
    || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP208)                    \
    || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506)                    \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206)                    \
    || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506)                    \
    || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)                      \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)                       \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502)                       \
    || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506)                       \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105)                       \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205)                       \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502)                       \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506)                       \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                     \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                    \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                    \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202)                    \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                    \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306)                    \
    || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406)                    \
    || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502)                    \
    || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506)                    \
    || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606)                    \
    || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                    \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK512MP305)                    \
    || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405)                    \
    || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410)                    \
    || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)                    \
    || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708)                    \
    || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406)                  \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705)                 \
    || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
#    define SENT_COUNT 2
#else
#    define SENT_COUNT 0
#endif

#endif  // SENT_DSPIC33_H
