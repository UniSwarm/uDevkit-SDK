/**
 * @file i2c_pic24_dspic30f_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date June 09, 2016, 18:47 PM
 *
 * @brief I2C communication support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP,
 * dsPIC33CH, dsPIC33CK, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#ifndef I2C_PIC24_DSPIC30F_DSPIC33_H
#define I2C_PIC24_DSPIC30F_DSPIC33_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_24F04KA200) || defined(DEVICE_24F04KA201) || defined(DEVICE_24F08KA101) || defined(DEVICE_24F08KA102) || defined(DEVICE_24F16KA101)         \
    || defined(DEVICE_24F16KA102) || defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102) || defined(DEVICE_24FJ32MC101) || defined(DEVICE_24FJ32MC102)  \
    || defined(DEVICE_24FJ32MC104) || defined(DEVICE_24HJ12GP201) || defined(DEVICE_24HJ12GP202) || defined(DEVICE_24HJ16GP304) || defined(DEVICE_24HJ32GP202) \
    || defined(DEVICE_24HJ32GP204) || defined(DEVICE_24HJ32GP302) || defined(DEVICE_24HJ32GP304) || defined(DEVICE_24HJ64GP202) || defined(DEVICE_24HJ64GP204) \
    || defined(DEVICE_24HJ64GP206) || defined(DEVICE_24HJ64GP206A) || defined(DEVICE_24HJ64GP502) || defined(DEVICE_24HJ64GP504)                               \
    || defined(DEVICE_24HJ128GP202) || defined(DEVICE_24HJ128GP204) || defined(DEVICE_24HJ128GP502) || defined(DEVICE_24HJ128GP504) || defined(DEVICE_30F1010) \
    || defined(DEVICE_30F2010) || defined(DEVICE_30F2011) || defined(DEVICE_30F2012) || defined(DEVICE_30F2020) || defined(DEVICE_30F2023)                     \
    || defined(DEVICE_30F3010) || defined(DEVICE_30F3011) || defined(DEVICE_30F3012) || defined(DEVICE_30F3013) || defined(DEVICE_30F3014)                     \
    || defined(DEVICE_30F4011) || defined(DEVICE_30F4012) || defined(DEVICE_30F4013) || defined(DEVICE_30F5011) || defined(DEVICE_30F5013)                     \
    || defined(DEVICE_30F5015) || defined(DEVICE_30F5016) || defined(DEVICE_30F6010) || defined(DEVICE_30F6010A) || defined(DEVICE_30F6011)                    \
    || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012) || defined(DEVICE_30F6012A) || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A)                  \
    || defined(DEVICE_30F6014) || defined(DEVICE_30F6014A) || defined(DEVICE_30F6015) || defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDVL64MC106)         \
    || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                        \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1)                    \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)                    \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306S1)                    \
    || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406S1) || defined(DEVICE_33CH512MP408S1)                    \
    || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)                    \
    || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606S1) || defined(DEVICE_33CH512MP608S1) || defined(DEVICE_33CH512MP705S1)                    \
    || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708S1) || defined(DEVICE_33CH512MP710S1) || defined(DEVICE_33CH1024MP305S1)                   \
    || defined(DEVICE_33CH1024MP306S1) || defined(DEVICE_33CH1024MP308S1) || defined(DEVICE_33CH1024MP405S1) || defined(DEVICE_33CH1024MP406S1)                \
    || defined(DEVICE_33CH1024MP408S1) || defined(DEVICE_33CH1024MP410S1) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606S1)                \
    || defined(DEVICE_33CH1024MP608S1) || defined(DEVICE_33CH1024MP705S1) || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708S1)                \
    || defined(DEVICE_33CH1024MP710S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                            \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK128MC102)                               \
    || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC502)                            \
    || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK256MC102)                            \
    || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502)                            \
    || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506) || defined(DEVICE_33EP16GS202)                             \
    || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003) || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) \
    || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) \
    || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) \
    || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106) || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003)                              \
    || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006) || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103)                            \
    || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003)                            \
    || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006) || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103)                            \
    || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106) || defined(DEVICE_33FJ06GS001) || defined(DEVICE_33FJ06GS101)                              \
    || defined(DEVICE_33FJ06GS101A) || defined(DEVICE_33FJ06GS102) || defined(DEVICE_33FJ06GS102A) || defined(DEVICE_33FJ06GS202)                              \
    || defined(DEVICE_33FJ06GS202A) || defined(DEVICE_33FJ09GS302) || defined(DEVICE_33FJ12GP201) || defined(DEVICE_33FJ12GP202)                               \
    || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202) || defined(DEVICE_33FJ16GP101) || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16GP304) \
    || defined(DEVICE_33FJ16GS402) || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ16GS502) || defined(DEVICE_33FJ16GS504) || defined(DEVICE_33FJ16MC101) \
    || defined(DEVICE_33FJ16MC102) || defined(DEVICE_33FJ16MC304) || defined(DEVICE_33FJ32GP101) || defined(DEVICE_33FJ32GP102) || defined(DEVICE_33FJ32GP104) \
    || defined(DEVICE_33FJ32GP202) || defined(DEVICE_33FJ32GP204) || defined(DEVICE_33FJ32GP302) || defined(DEVICE_33FJ32GP304) || defined(DEVICE_33FJ32MC101) \
    || defined(DEVICE_33FJ32MC102) || defined(DEVICE_33FJ32MC104) || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC204) || defined(DEVICE_33FJ32MC302) \
    || defined(DEVICE_33FJ32MC304) || defined(DEVICE_33FJ64GP202) || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64GP804) \
    || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804)                                \
    || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP206) || defined(DEVICE_33FJ128GP206A)                           \
    || defined(DEVICE_33FJ128GP802) || defined(DEVICE_33FJ128GP804) || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204)                            \
    || defined(DEVICE_33FJ128MC802) || defined(DEVICE_33FJ128MC804)
#    define I2C_COUNT 1
#elif defined(DEVICE_24EP32GP202) || defined(DEVICE_24EP32GP203) || defined(DEVICE_24EP32GP204) || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203)  \
    || defined(DEVICE_24EP32MC204) || defined(DEVICE_24EP64GP202) || defined(DEVICE_24EP64GP203) || defined(DEVICE_24EP64GP204) || defined(DEVICE_24EP64GP206) \
    || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) || defined(DEVICE_24EP64MC206)                                \
    || defined(DEVICE_24EP128GP202) || defined(DEVICE_24EP128GP204) || defined(DEVICE_24EP128GP206) || defined(DEVICE_24EP128MC202)                            \
    || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) || defined(DEVICE_24EP256GP202) || defined(DEVICE_24EP256GP204)                            \
    || defined(DEVICE_24EP256GP206) || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) || defined(DEVICE_24EP256MC202)                            \
    || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206) || defined(DEVICE_24EP512GP202) || defined(DEVICE_24EP512GP204)                            \
    || defined(DEVICE_24EP512GP206) || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512GU814)                            \
    || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) || defined(DEVICE_24F16KA301)                              \
    || defined(DEVICE_24F16KA302) || defined(DEVICE_24F16KA304) || defined(DEVICE_24F32KA301) || defined(DEVICE_24F32KA302) || defined(DEVICE_24F32KA304)      \
    || defined(DEVICE_24FJ16GA002) || defined(DEVICE_24FJ16GA004) || defined(DEVICE_24FJ32GA002) || defined(DEVICE_24FJ32GA004) || defined(DEVICE_24FJ32GA102) \
    || defined(DEVICE_24FJ32GA104) || defined(DEVICE_24FJ32GB002) || defined(DEVICE_24FJ32GB004) || defined(DEVICE_24FJ32GP202) || defined(DEVICE_24FJ32GP203) \
    || defined(DEVICE_24FJ32GP205) || defined(DEVICE_24FJ32GU202) || defined(DEVICE_24FJ32GU203) || defined(DEVICE_24FJ32GU205) || defined(DEVICE_24FJ48GA002) \
    || defined(DEVICE_24FJ48GA004) || defined(DEVICE_24FJ64GA002) || defined(DEVICE_24FJ64GA004) || defined(DEVICE_24FJ64GA006) || defined(DEVICE_24FJ64GA008) \
    || defined(DEVICE_24FJ64GA010) || defined(DEVICE_24FJ64GA102) || defined(DEVICE_24FJ64GA104) || defined(DEVICE_24FJ64GA202) || defined(DEVICE_24FJ64GA204) \
    || defined(DEVICE_24FJ64GA306) || defined(DEVICE_24FJ64GA308) || defined(DEVICE_24FJ64GA310) || defined(DEVICE_24FJ64GA702) || defined(DEVICE_24FJ64GA704) \
    || defined(DEVICE_24FJ64GA705) || defined(DEVICE_24FJ64GB002) || defined(DEVICE_24FJ64GB004) || defined(DEVICE_24FJ64GB202) || defined(DEVICE_24FJ64GB204) \
    || defined(DEVICE_24FJ64GC006) || defined(DEVICE_24FJ64GC010) || defined(DEVICE_24FJ64GL302) || defined(DEVICE_24FJ64GL303) || defined(DEVICE_24FJ64GL305) \
    || defined(DEVICE_24FJ64GL306) || defined(DEVICE_24FJ64GP202) || defined(DEVICE_24FJ64GP203) || defined(DEVICE_24FJ64GP205) || defined(DEVICE_24FJ64GU202) \
    || defined(DEVICE_24FJ64GU203) || defined(DEVICE_24FJ64GU205) || defined(DEVICE_24FJ96GA006) || defined(DEVICE_24FJ96GA008) || defined(DEVICE_24FJ96GA010) \
    || defined(DEVICE_24FJ128GA006) || defined(DEVICE_24FJ128GA008) || defined(DEVICE_24FJ128GA010) || defined(DEVICE_24FJ128GA202)                            \
    || defined(DEVICE_24FJ128GA204) || defined(DEVICE_24FJ128GA306) || defined(DEVICE_24FJ128GA308) || defined(DEVICE_24FJ128GA310)                            \
    || defined(DEVICE_24FJ128GA702) || defined(DEVICE_24FJ128GA704) || defined(DEVICE_24FJ128GA705) || defined(DEVICE_24FJ128GB202)                            \
    || defined(DEVICE_24FJ128GB204) || defined(DEVICE_24FJ128GC006) || defined(DEVICE_24FJ128GC010) || defined(DEVICE_24FJ128GL302)                            \
    || defined(DEVICE_24FJ128GL303) || defined(DEVICE_24FJ128GL305) || defined(DEVICE_24FJ128GL306) || defined(DEVICE_24FJ256GA702)                            \
    || defined(DEVICE_24FJ256GA704) || defined(DEVICE_24FJ256GA705) || defined(DEVICE_24FV16KA301) || defined(DEVICE_24FV16KA302)                              \
    || defined(DEVICE_24FV16KA304) || defined(DEVICE_24FV32KA301) || defined(DEVICE_24FV32KA302) || defined(DEVICE_24FV32KA304) || defined(DEVICE_24HJ64GP210) \
    || defined(DEVICE_24HJ64GP210A) || defined(DEVICE_24HJ64GP506) || defined(DEVICE_24HJ64GP506A) || defined(DEVICE_24HJ64GP510)                              \
    || defined(DEVICE_24HJ64GP510A) || defined(DEVICE_24HJ128GP206) || defined(DEVICE_24HJ128GP206A) || defined(DEVICE_24HJ128GP210)                           \
    || defined(DEVICE_24HJ128GP210A) || defined(DEVICE_24HJ128GP306) || defined(DEVICE_24HJ128GP306A) || defined(DEVICE_24HJ128GP310)                          \
    || defined(DEVICE_24HJ128GP310A) || defined(DEVICE_24HJ128GP506) || defined(DEVICE_24HJ128GP506A) || defined(DEVICE_24HJ128GP510)                          \
    || defined(DEVICE_24HJ128GP510A) || defined(DEVICE_24HJ256GP206) || defined(DEVICE_24HJ256GP206A) || defined(DEVICE_24HJ256GP210)                          \
    || defined(DEVICE_24HJ256GP210A) || defined(DEVICE_24HJ256GP610) || defined(DEVICE_24HJ256GP610A) || defined(DEVICE_33CH64MP202)                           \
    || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP502) \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508)                                \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506)                            \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208)                            \
    || defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP405)                            \
    || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP412S1)                          \
    || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP605)                            \
    || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP706)                            \
    || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP712S1) || defined(DEVICE_33CH1024MP305)                         \
    || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP406)                        \
    || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP412S1) || defined(DEVICE_33CH1024MP605)                      \
    || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP706)                        \
    || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP712S1) || defined(DEVICE_33CK32MP102)                        \
    || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) \
    || defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505)                               \
    || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32GS502) \
    || defined(DEVICE_33EP32GS504) || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) \
    || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP64GP502) \
    || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) \
    || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) \
    || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) \
    || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) \
    || defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) || defined(DEVICE_33EP128GM604)                            \
    || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504)                            \
    || defined(DEVICE_33EP128GP506) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                            \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                            \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808) || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204)                            \
    || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506)                            \
    || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604)                            \
    || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504)                            \
    || defined(DEVICE_33EP256GP506) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206)                            \
    || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP256MU806)                            \
    || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306)                            \
    || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710)                            \
    || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512GP806)                            \
    || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502)                            \
    || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810)                            \
    || defined(DEVICE_33EP512MU814) || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608)                               \
    || defined(DEVICE_33FJ32GS610) || defined(DEVICE_33FJ64GP206) || defined(DEVICE_33FJ64GP206A) || defined(DEVICE_33FJ64GP306)                               \
    || defined(DEVICE_33FJ64GP306A) || defined(DEVICE_33FJ64GP310) || defined(DEVICE_33FJ64GP310A) || defined(DEVICE_33FJ64GP706)                              \
    || defined(DEVICE_33FJ64GP706A) || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A) || defined(DEVICE_33FJ64GP710)                              \
    || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608)                               \
    || defined(DEVICE_33FJ64GS610) || defined(DEVICE_33FJ64MC506) || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508)                               \
    || defined(DEVICE_33FJ64MC508A) || defined(DEVICE_33FJ64MC510) || defined(DEVICE_33FJ64MC510A) || defined(DEVICE_33FJ64MC706)                              \
    || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710) || defined(DEVICE_33FJ64MC710A) || defined(DEVICE_33FJ128GP306)                             \
    || defined(DEVICE_33FJ128GP306A) || defined(DEVICE_33FJ128GP310) || defined(DEVICE_33FJ128GP310A) || defined(DEVICE_33FJ128GP706)                          \
    || defined(DEVICE_33FJ128GP706A) || defined(DEVICE_33FJ128GP708) || defined(DEVICE_33FJ128GP708A) || defined(DEVICE_33FJ128GP710)                          \
    || defined(DEVICE_33FJ128GP710A) || defined(DEVICE_33FJ128MC506) || defined(DEVICE_33FJ128MC506A) || defined(DEVICE_33FJ128MC510)                          \
    || defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC706) || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC708)                          \
    || defined(DEVICE_33FJ128MC708A) || defined(DEVICE_33FJ128MC710) || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ256GP506)                          \
    || defined(DEVICE_33FJ256GP506A) || defined(DEVICE_33FJ256GP510) || defined(DEVICE_33FJ256GP510A) || defined(DEVICE_33FJ256GP710)                          \
    || defined(DEVICE_33FJ256GP710A) || defined(DEVICE_33FJ256MC510) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710)                          \
    || defined(DEVICE_33FJ256MC710A)
#    define I2C_COUNT 2
#elif defined(DEVICE_24FJ64GA106) || defined(DEVICE_24FJ64GA108) || defined(DEVICE_24FJ64GA110) || defined(DEVICE_24FJ64GA406) || defined(DEVICE_24FJ64GA410)  \
    || defined(DEVICE_24FJ64GA412) || defined(DEVICE_24FJ64GB106) || defined(DEVICE_24FJ64GB108) || defined(DEVICE_24FJ64GB110) || defined(DEVICE_24FJ64GB406) \
    || defined(DEVICE_24FJ64GB410) || defined(DEVICE_24FJ64GB412) || defined(DEVICE_24FJ128DA106) || defined(DEVICE_24FJ128DA110)                              \
    || defined(DEVICE_24FJ128DA206) || defined(DEVICE_24FJ128DA210) || defined(DEVICE_24FJ128GA106) || defined(DEVICE_24FJ128GA108)                            \
    || defined(DEVICE_24FJ128GA110) || defined(DEVICE_24FJ128GA406) || defined(DEVICE_24FJ128GA410) || defined(DEVICE_24FJ128GA412)                            \
    || defined(DEVICE_24FJ128GA606) || defined(DEVICE_24FJ128GA610) || defined(DEVICE_24FJ128GB106) || defined(DEVICE_24FJ128GB108)                            \
    || defined(DEVICE_24FJ128GB110) || defined(DEVICE_24FJ128GB206) || defined(DEVICE_24FJ128GB210) || defined(DEVICE_24FJ128GB406)                            \
    || defined(DEVICE_24FJ128GB410) || defined(DEVICE_24FJ128GB412) || defined(DEVICE_24FJ128GB606) || defined(DEVICE_24FJ128GB610)                            \
    || defined(DEVICE_24FJ128GL405) || defined(DEVICE_24FJ128GL406) || defined(DEVICE_24FJ128GL408) || defined(DEVICE_24FJ128GL410)                            \
    || defined(DEVICE_24FJ128GU405) || defined(DEVICE_24FJ128GU406) || defined(DEVICE_24FJ128GU408) || defined(DEVICE_24FJ128GU410)                            \
    || defined(DEVICE_24FJ192GA106) || defined(DEVICE_24FJ192GA108) || defined(DEVICE_24FJ192GA110) || defined(DEVICE_24FJ192GB106)                            \
    || defined(DEVICE_24FJ192GB108) || defined(DEVICE_24FJ192GB110) || defined(DEVICE_24FJ256DA106) || defined(DEVICE_24FJ256DA110)                            \
    || defined(DEVICE_24FJ256DA206) || defined(DEVICE_24FJ256DA210) || defined(DEVICE_24FJ256GA106) || defined(DEVICE_24FJ256GA108)                            \
    || defined(DEVICE_24FJ256GA110) || defined(DEVICE_24FJ256GA406) || defined(DEVICE_24FJ256GA410) || defined(DEVICE_24FJ256GA412)                            \
    || defined(DEVICE_24FJ256GA606) || defined(DEVICE_24FJ256GA610) || defined(DEVICE_24FJ256GB106) || defined(DEVICE_24FJ256GB108)                            \
    || defined(DEVICE_24FJ256GB110) || defined(DEVICE_24FJ256GB206) || defined(DEVICE_24FJ256GB210) || defined(DEVICE_24FJ256GB406)                            \
    || defined(DEVICE_24FJ256GB410) || defined(DEVICE_24FJ256GB412) || defined(DEVICE_24FJ256GB606) || defined(DEVICE_24FJ256GB610)                            \
    || defined(DEVICE_24FJ256GL405) || defined(DEVICE_24FJ256GL406) || defined(DEVICE_24FJ256GL408) || defined(DEVICE_24FJ256GL410)                            \
    || defined(DEVICE_24FJ256GU405) || defined(DEVICE_24FJ256GU406) || defined(DEVICE_24FJ256GU408) || defined(DEVICE_24FJ256GU410)                            \
    || defined(DEVICE_24FJ512GA606) || defined(DEVICE_24FJ512GA610) || defined(DEVICE_24FJ512GB606) || defined(DEVICE_24FJ512GB610)                            \
    || defined(DEVICE_24FJ512GL405) || defined(DEVICE_24FJ512GL406) || defined(DEVICE_24FJ512GL408) || defined(DEVICE_24FJ512GL410)                            \
    || defined(DEVICE_24FJ512GU405) || defined(DEVICE_24FJ512GU406) || defined(DEVICE_24FJ512GU408) || defined(DEVICE_24FJ512GU410)                            \
    || defined(DEVICE_24FJ1024GA606) || defined(DEVICE_24FJ1024GA610) || defined(DEVICE_24FJ1024GB606) || defined(DEVICE_24FJ1024GB610)                        \
    || defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506)                      \
    || defined(DEVICE_33CH512MP412) || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP712)                          \
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
    || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306)                           \
    || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408)                            \
    || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)                            \
    || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710)                            \
    || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408)                        \
    || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708)                        \
    || defined(DEVICE_33CK1024MP710)
#    define I2C_COUNT 3
#else
#    define I2C_COUNT 0
#endif

#if defined(DEVICE_24FJ32GP202) || defined(DEVICE_24FJ32GP203) || defined(DEVICE_24FJ32GP205) || defined(DEVICE_24FJ32GU202) || defined(DEVICE_24FJ32GU203)    \
    || defined(DEVICE_24FJ32GU205) || defined(DEVICE_24FJ64GA202) || defined(DEVICE_24FJ64GA204) || defined(DEVICE_24FJ64GA406) || defined(DEVICE_24FJ64GA410) \
    || defined(DEVICE_24FJ64GA412) || defined(DEVICE_24FJ64GA702) || defined(DEVICE_24FJ64GA704) || defined(DEVICE_24FJ64GA705) || defined(DEVICE_24FJ64GB202) \
    || defined(DEVICE_24FJ64GB204) || defined(DEVICE_24FJ64GB406) || defined(DEVICE_24FJ64GB410) || defined(DEVICE_24FJ64GB412) || defined(DEVICE_24FJ64GL302) \
    || defined(DEVICE_24FJ64GL303) || defined(DEVICE_24FJ64GL305) || defined(DEVICE_24FJ64GL306) || defined(DEVICE_24FJ64GP202) || defined(DEVICE_24FJ64GP203) \
    || defined(DEVICE_24FJ64GP205) || defined(DEVICE_24FJ64GU202) || defined(DEVICE_24FJ64GU203) || defined(DEVICE_24FJ64GU205)                                \
    || defined(DEVICE_24FJ128GA202) || defined(DEVICE_24FJ128GA204) || defined(DEVICE_24FJ128GA406) || defined(DEVICE_24FJ128GA410)                            \
    || defined(DEVICE_24FJ128GA412) || defined(DEVICE_24FJ128GA606) || defined(DEVICE_24FJ128GA610) || defined(DEVICE_24FJ128GA702)                            \
    || defined(DEVICE_24FJ128GA704) || defined(DEVICE_24FJ128GA705) || defined(DEVICE_24FJ128GB202) || defined(DEVICE_24FJ128GB204)                            \
    || defined(DEVICE_24FJ128GB406) || defined(DEVICE_24FJ128GB410) || defined(DEVICE_24FJ128GB412) || defined(DEVICE_24FJ128GB606)                            \
    || defined(DEVICE_24FJ128GB610) || defined(DEVICE_24FJ128GL302) || defined(DEVICE_24FJ128GL303) || defined(DEVICE_24FJ128GL305)                            \
    || defined(DEVICE_24FJ128GL306) || defined(DEVICE_24FJ128GL405) || defined(DEVICE_24FJ128GL406) || defined(DEVICE_24FJ128GL408)                            \
    || defined(DEVICE_24FJ128GL410) || defined(DEVICE_24FJ128GU405) || defined(DEVICE_24FJ128GU406) || defined(DEVICE_24FJ128GU408)                            \
    || defined(DEVICE_24FJ128GU410) || defined(DEVICE_24FJ256GA406) || defined(DEVICE_24FJ256GA410) || defined(DEVICE_24FJ256GA412)                            \
    || defined(DEVICE_24FJ256GA606) || defined(DEVICE_24FJ256GA610) || defined(DEVICE_24FJ256GA702) || defined(DEVICE_24FJ256GA704)                            \
    || defined(DEVICE_24FJ256GA705) || defined(DEVICE_24FJ256GB406) || defined(DEVICE_24FJ256GB410) || defined(DEVICE_24FJ256GB412)                            \
    || defined(DEVICE_24FJ256GB606) || defined(DEVICE_24FJ256GB610) || defined(DEVICE_24FJ256GL405) || defined(DEVICE_24FJ256GL406)                            \
    || defined(DEVICE_24FJ256GL408) || defined(DEVICE_24FJ256GL410) || defined(DEVICE_24FJ256GU405) || defined(DEVICE_24FJ256GU406)                            \
    || defined(DEVICE_24FJ256GU408) || defined(DEVICE_24FJ256GU410) || defined(DEVICE_24FJ512GA606) || defined(DEVICE_24FJ512GA610)                            \
    || defined(DEVICE_24FJ512GB606) || defined(DEVICE_24FJ512GB610) || defined(DEVICE_24FJ512GL405) || defined(DEVICE_24FJ512GL406)                            \
    || defined(DEVICE_24FJ512GL408) || defined(DEVICE_24FJ512GL410) || defined(DEVICE_24FJ512GU405) || defined(DEVICE_24FJ512GU406)                            \
    || defined(DEVICE_24FJ512GU408) || defined(DEVICE_24FJ512GU410) || defined(DEVICE_24FJ1024GA606) || defined(DEVICE_24FJ1024GA610)                          \
    || defined(DEVICE_24FJ1024GB606) || defined(DEVICE_24FJ1024GB610) || defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDV128MP506)                         \
    || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CDVL64MC106)                      \
    || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP203S1)                            \
    || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP206S1)                            \
    || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP502S1)                            \
    || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP505S1)                            \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH64MP508S1)                            \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP203S1)                        \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP206S1)                        \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP502S1)                        \
    || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP505S1)                        \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH128MP508S1)                        \
    || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP206S1)                        \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP218S1)                        \
    || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP506S1)                        \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP205S1)                        \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP208S1)                        \
    || defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP306S1)                        \
    || defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP405) || defined(DEVICE_33CH512MP405S1)                        \
    || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP406S1) || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP408S1)                        \
    || defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP412) || defined(DEVICE_33CH512MP412S1)                        \
    || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP506S1)                        \
    || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH512MP605) || defined(DEVICE_33CH512MP605S1)                        \
    || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP606S1) || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP608S1)                        \
    || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP705S1) || defined(DEVICE_33CH512MP706) || defined(DEVICE_33CH512MP706S1)                        \
    || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP708S1) || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP710S1)                        \
    || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH512MP712S1) || defined(DEVICE_33CH1024MP305) || defined(DEVICE_33CH1024MP305S1)                      \
    || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP306S1) || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP308S1)                    \
    || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP405S1) || defined(DEVICE_33CH1024MP406) || defined(DEVICE_33CH1024MP406S1)                    \
    || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP408S1) || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP410S1)                    \
    || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP412S1) || defined(DEVICE_33CH1024MP605) || defined(DEVICE_33CH1024MP605S1)                    \
    || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP606S1) || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP608S1)                    \
    || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP705S1) || defined(DEVICE_33CH1024MP706) || defined(DEVICE_33CH1024MP706S1)                    \
    || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP708S1) || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP710S1)                    \
    || defined(DEVICE_33CH1024MP712) || defined(DEVICE_33CH1024MP712S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103)                          \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) \
    || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) \
    || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) \
    || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MC102)                               \
    || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC502)                            \
    || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK128MP202)                            \
    || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208)                            \
    || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506)                            \
    || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105)                            \
    || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505)                            \
    || defined(DEVICE_33CK256MC506) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205)                            \
    || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306)                            \
    || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408)                            \
    || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505)                            \
    || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606)                            \
    || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706) || defined(DEVICE_33CK256MP708)                            \
    || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306)                           \
    || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408)                            \
    || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)                            \
    || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710)                            \
    || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408)                        \
    || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708)                        \
    || defined(DEVICE_33CK1024MP710) || defined(DEVICE_33EP16GS202) || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504)                              \
    || defined(DEVICE_33EP16GS505) || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP32GS202) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) \
    || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) || defined(DEVICE_33EP64GS505) \
    || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) \
    || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705)                             \
    || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805)                            \
    || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003)                              \
    || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) \
    || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) \
    || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106)                                \
    || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006)                            \
    || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106)                            \
    || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006)                            \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106)
#    define I2C1CONbits I2C1CONLbits
#    define I2C2CONbits I2C2CONLbits
#    define I2C3CONbits I2C3CONLbits
#endif

#define i2c(d) MKDEV(DEV_CLASS_I2C, (d)-1)

#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)                           \
    || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    define I2C_FPGD 7692307  // 130ns
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    define I2C_FPGD 15384615  // 65ns
#endif

#if defined(ARCHI_dspic30f)
#    define I2C1BRG      I2CBRG
#    define I2C1CONbits  I2CCONbits
#    define I2C1STATbits I2CSTATbits
#    define I2C1TRN      I2CTRN
#    define I2C1RCV      I2CRCV
#endif

#ifdef __cplusplus
}
#endif

#endif  // I2C_PIC24_DSPIC30F_DSPIC33_H
