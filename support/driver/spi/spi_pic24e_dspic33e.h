/**
 * @file spi_pic24e_dspic33e.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date October 10, 2016, 10:31 AM
 *
 * @brief SPI communication support driver for dsPIC33EP, dsPIC33EV, PIC24EP,
 * dsPIC33CK and dsPIC33CH
 *
 * Implementation based on Microchip document DS70005185A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005185a.pdf
 */

#ifndef SPI_PIC24E_DSPIC33E_H
#define SPI_PIC24E_DSPIC33E_H

#if defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                           \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1)                    \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)                    \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1)                    \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP32GS202)
#    define SPI_COUNT 1
#elif defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)  \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206)                            \
    || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204) || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512MC202)                            \
    || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDVL64MC106)                           \
    || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208) \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506)                            \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208)                            \
    || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CK32MC102)                             \
    || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) \
    || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106)                            \
    || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506)                            \
    || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106)                            \
    || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506)                            \
    || defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                               \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32GS502) \
    || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) \
    || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) \
    || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) \
    || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) \
    || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128MC202)                            \
    || defined(DEVICE_33EP128MC204) || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504)                            \
    || defined(DEVICE_33EP128MC506) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504) || defined(DEVICE_33EP256GP506)                            \
    || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502)                            \
    || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504)                            \
    || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206)                            \
    || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EV32GM002)                             \
    || defined(DEVICE_33EV32GM003) || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) \
    || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) \
    || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106) \
    || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006)                            \
    || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106)                            \
    || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006)                            \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define SPI_COUNT 2
#elif defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506)                       \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) \
    || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)                                \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                            \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                            \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                            \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305)                            \
    || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406)                            \
    || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                            \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                            \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306)                            \
    || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408)                            \
    || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)                            \
    || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710)                            \
    || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410)                        \
    || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)                        \
    || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) \
    || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM604)                            \
    || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704)                            \
    || defined(DEVICE_33EP128GS705) || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804)                            \
    || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808) || defined(DEVICE_33EP256GM304)                            \
    || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706)                            \
    || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310)                            \
    || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710)
#    define SPI_COUNT 3
#elif defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810)                             \
    || defined(DEVICE_24EP512GU814) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814)                            \
    || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
#    define SPI_COUNT 4
#else
#    define SPI_COUNT 0
#endif

#endif  // SPI_PIC24E_DSPIC33E_H
