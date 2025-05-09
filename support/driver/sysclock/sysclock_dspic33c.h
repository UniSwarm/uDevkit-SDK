/**
 * @file sysclock_dspic33c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date May 28, 2018, 02:28 PM
 *
 * @brief System clock support for udevkit for dsPIC33CH, dsPIC33CK
 *
 * Implementation based on Microchip documents DS70005255B and DS2070005319B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Oscillator-Module-with-High-Speed-PLL-70005255b.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33CH128MP5%20Datasheet%2070005319b.pdf
 */

#ifndef SYSCLOCK_DSPIC33C_H
#define SYSCLOCK_DSPIC33C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sysclock.h"

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_FOSC = 0x0,  ///< Fosc
    SYSCLOCK_CLOCK_SYSCLK,      ///< main sysclock, Fp
    SYSCLOCK_CLOCK_PBCLK,       ///< peripheral bus
    SYSCLOCK_CLOCK_REFCLK,      ///< reference clock module
    SYSCLOCK_CLOCK_FRC,         ///< FRC div
    SYSCLOCK_CLOCK_FPLLO,       ///< PLL outpout
    SYSCLOCK_CLOCK_VCO,         ///< PLL VCO
    SYSCLOCK_CLOCK_VCO2,        ///< PLL VCO / 2
    SYSCLOCK_CLOCK_VCO3,        ///< PLL VCO / 3
    SYSCLOCK_CLOCK_VCO4,        ///< PLL VCO / 4
    SYSCLOCK_CLOCK_AFPLLO,      ///< Auxiliary PLL outpout
    SYSCLOCK_CLOCK_AVCO,        ///< Auxiliary PLL VCO
    SYSCLOCK_CLOCK_AVCO2,       ///< Auxiliary PLL VCO / 2
    SYSCLOCK_CLOCK_AVCO3,       ///< Auxiliary PLL VCO / 3
    SYSCLOCK_CLOCK_AVCO4        ///< Auxiliary PLL VCO / 4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b000,     ///< Fast internal oscillator (FRC)
    SYSCLOCK_SRC_FRCPLL = 0b001,  ///< Fast internal oscillator (FRC) with PLL
    SYSCLOCK_SRC_POSC = 0b010,    ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_PPLL = 0b011,    ///< System PLL (SPLL)
    SYSCLOCK_SRC_LPRC = 0b101,    ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_BFRC = 0b110,    ///< Backup fast internal oscillator (BFRC)
    SYSCLOCK_SRC_FRCDIV = 0b111   ///< Fast internal oscillator (FRC) divided by FRCDIVN
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_LPRC   SYSCLOCK_SRC_LPRC
#define SYSCLOCK_SRC_POSC   SYSCLOCK_SRC_POSC
#define SYSCLOCK_SRC_PPLL   SYSCLOCK_SRC_PPLL
#define SYSCLOCK_SRC_BFRC   SYSCLOCK_SRC_BFRC
#define SYSCLOCK_SRC_FRC    SYSCLOCK_SRC_FRC
#define SYSCLOCK_SRC_FRCPLL SYSCLOCK_SRC_FRCPLL
#define SYSCLOCK_SRC_FRCDIV SYSCLOCK_SRC_FRCDIV
#define SYSCLOCK_SRC_MAX    7

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"FRC", "FRCPLL", "POSC", "PPLL", "", "LPRC", "BFRC", "FRCDIV"};
#endif

// periph clock assoc
#define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_SYSCLK  ///< CPU clock bus
#define SYSCLOCK_CLOCK_CAN   SYSCLOCK_CLOCK_VCO2    ///< CAN clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_PMP   SYSCLOCK_CLOCK_PBCLK   ///< PMP clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_PBCLK   ///< I2C clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_PBCLK   ///< UART clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_PBCLK   ///< SPI clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_PBCLK   ///< TIMER clock bus mapped to peripheral bus
#define SYSCLOCK_CLOCK_CCP   SYSCLOCK_CLOCK_PBCLK   ///< TIMER clock bus mapped to peripheral bus

/*
 *                  Fplli                    FVco                            FPllo
 *        _________   |    _______             |                               |
 *  Fin  |         |  v   |       |     _____  |    __________     __________  |  ____
 * ----->| /PREDIV |----->|       |    |     | v   |          |   |          | v |    |
 *       |_________|      |  PFD  |--->| VCO |-+-->| POSTDIV1 |-->| POSTDIV2 |-->| /2 |--> Fsys
 *                     +->|       |    |_____| |   |__________|   |__________|   |____|
 *                     |  |_______|            |
 *                     |        _______        |
 *                     |       |       |       |
 *                     +-------|   /M  |-------+
 *                             |_______|
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_PLLM_MIN  > FPllo > SYSCLOCK_PLLM_MAX
 */

#if defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)

#    define FRC_BASE_FREQ  8000000  //     8 MHz
#    define OSCTUN_D       3760     // +/- 0.047%
#    define LPRC_BASE_FREQ 32000    //    32 kHz
#    define BFRC_BASE_FREQ 8000000  //     8 MHz

#    define SYSCLOCK_PREDIV_MIN 1
#    define SYSCLOCK_PREDIV_MAX 8
#    define SYSCLOCK_FPLLI_MIN  8000000   //    8 MHz
#    define SYSCLOCK_FPLLI_MAX  64000000  //   64 MHz

#    define SYSCLOCK_FVCO_MIN 400000000   //  400 MHz
#    define SYSCLOCK_FVCO_MAX 1600000000  // 1600 MHz

#    define SYSCLOCK_POSTDIV1_MIN 1
#    define SYSCLOCK_POSTDIV1_MAX 7
#    define SYSCLOCK_POSTDIV2_MIN 1
#    define SYSCLOCK_POSTDIV2_MAX 7
// POSTDIV1 >= POSTDIV2

#    define SYSCLOCK_PLLM_MIN 16
#    define SYSCLOCK_PLLM_MAX 200

#else
#    error Unsuported ARCHI
#endif

#if defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                           \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1)                    \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)                    \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306S1)                    \
    || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406S1) || defined(DEVICE_33CH512MP408S1)                    \
    || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP412S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1)                    \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606S1) || defined(DEVICE_33CH512MP608S1)                    \
    || defined(DEVICE_33CH512MP705S1) || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708S1) || defined(DEVICE_33CH512MP710S1)                    \
    || defined(DEVICE_33CH512MP712S1) || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306S1) || defined(DEVICE_33CH1024MP308S1)                 \
    || defined(DEVICE_33CH1024MP405S1) || defined(DEVICE_33CH1024MP406S1) || defined(DEVICE_33CH1024MP408S1) || defined(DEVICE_33CH1024MP410S1)                \
    || defined(DEVICE_33CH1024MP412S1) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606S1) || defined(DEVICE_33CH1024MP608S1)                \
    || defined(DEVICE_33CH1024MP705S1) || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708S1) || defined(DEVICE_33CH1024MP710S1)                \
    || defined(DEVICE_33CH1024MP712S1) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105)                            \
    || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) \
    || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102) \
    || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) \
    || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
    || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103)                              \
    || defined(DEVICE_33CK128MC105) || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503)                            \
    || defined(DEVICE_33CK128MC505) || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203)                            \
    || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502)                            \
    || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508)                            \
    || defined(DEVICE_33CK256MC102) || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106)                            \
    || defined(DEVICE_33CK256MC502) || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506)                            \
    || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206)                            \
    || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308)                            \
    || defined(DEVICE_33CK256MP405) || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410)                            \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506)                            \
    || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605) || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608)                            \
    || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706) || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710)                            \
    || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308)                           \
    || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406) || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410)                            \
    || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705)                            \
    || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708) || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK512MPT608)                           \
    || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406) || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410)                        \
    || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706) || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
#    define SYSCLOCK_FSYS_MAX 100000000  //  100 MHz
#    define SYSCLOCK_FOSC_MAX 200000000  //  200 MHz
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208)  \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP218) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506)                            \
    || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208)                            \
    || defined(DEVICE_33CH512MP305) || defined(DEVICE_33CH512MP306) || defined(DEVICE_33CH512MP308) || defined(DEVICE_33CH512MP405)                            \
    || defined(DEVICE_33CH512MP406) || defined(DEVICE_33CH512MP408) || defined(DEVICE_33CH512MP410) || defined(DEVICE_33CH512MP412)                            \
    || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH512MP605)                            \
    || defined(DEVICE_33CH512MP606) || defined(DEVICE_33CH512MP608) || defined(DEVICE_33CH512MP705) || defined(DEVICE_33CH512MP706)                            \
    || defined(DEVICE_33CH512MP708) || defined(DEVICE_33CH512MP710) || defined(DEVICE_33CH512MP712) || defined(DEVICE_33CH1024MP305)                           \
    || defined(DEVICE_33CH1024MP306) || defined(DEVICE_33CH1024MP308) || defined(DEVICE_33CH1024MP405) || defined(DEVICE_33CH1024MP406)                        \
    || defined(DEVICE_33CH1024MP408) || defined(DEVICE_33CH1024MP410) || defined(DEVICE_33CH1024MP412) || defined(DEVICE_33CH1024MP605)                        \
    || defined(DEVICE_33CH1024MP606) || defined(DEVICE_33CH1024MP608) || defined(DEVICE_33CH1024MP705) || defined(DEVICE_33CH1024MP706)                        \
    || defined(DEVICE_33CH1024MP708) || defined(DEVICE_33CH1024MP710) || defined(DEVICE_33CH1024MP712)
#    define SYSCLOCK_FSYS_MAX 90000000   //   90 MHz
#    define SYSCLOCK_FOSC_MAX 180000000  //  180 MHz
#endif
#define SYSCLOCK_FSYS_MIN 1000000  //   1 MHz

#if defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                           \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1)                    \
    || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1)                    \
    || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP305S1) || defined(DEVICE_33CH512MP306S1)                    \
    || defined(DEVICE_33CH512MP308S1) || defined(DEVICE_33CH512MP405S1) || defined(DEVICE_33CH512MP406S1) || defined(DEVICE_33CH512MP408S1)                    \
    || defined(DEVICE_33CH512MP410S1) || defined(DEVICE_33CH512MP412S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1)                    \
    || defined(DEVICE_33CH512MP508S1) || defined(DEVICE_33CH512MP605S1) || defined(DEVICE_33CH512MP606S1) || defined(DEVICE_33CH512MP608S1)                    \
    || defined(DEVICE_33CH512MP705S1) || defined(DEVICE_33CH512MP706S1) || defined(DEVICE_33CH512MP708S1) || defined(DEVICE_33CH512MP710S1)                    \
    || defined(DEVICE_33CH512MP712S1) || defined(DEVICE_33CH1024MP305S1) || defined(DEVICE_33CH1024MP306S1) || defined(DEVICE_33CH1024MP308S1)                 \
    || defined(DEVICE_33CH1024MP405S1) || defined(DEVICE_33CH1024MP406S1) || defined(DEVICE_33CH1024MP408S1) || defined(DEVICE_33CH1024MP410S1)                \
    || defined(DEVICE_33CH1024MP412S1) || defined(DEVICE_33CH1024MP605S1) || defined(DEVICE_33CH1024MP606S1) || defined(DEVICE_33CH1024MP608S1)                \
    || defined(DEVICE_33CH1024MP705S1) || defined(DEVICE_33CH1024MP706S1) || defined(DEVICE_33CH1024MP708S1) || defined(DEVICE_33CH1024MP710S1)                \
    || defined(DEVICE_33CH1024MP712S1)
#    define SYSCLOCK_NO_OSCTUNE
#endif

int sysclock_setPLLClock(uint32_t freq, uint8_t src);
uint32_t sysclock_getPLLClock(void);

uint32_t sysclock_getAPLLClock(void);

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_DSPIC33C_H
