/**
 * @file sysclock_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip documents DS70186D, DS70580C, DS70005131A, DS70307E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70216D.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70580C.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005131a.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70307E.pdf
 */

#include "sysclock.h"

#ifndef SYSCLOCK_PIC24_DSPIC33_H
#define SYSCLOCK_PIC24_DSPIC33_H

// bus clock
typedef enum {
    SYSCLOCK_CLOCK_SYSCLK = 0x0,    ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK,           ///< peripherical bus
    SYSCLOCK_CLOCK_REFCLK,          ///< reference clock module
    SYSCLOCK_CLOCK_FRC              ///< FRC div
} SYSCLOCK_CLOCK;

// clock source
typedef enum {
    SYSCLOCK_SRC_LPRC   = 0b101, ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_SOSC   = 0b100, ///< Secondary oscillator (SOSC)
    SYSCLOCK_SRC_POSC   = 0b010, ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_PPLL   = 0b011, ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC    = 0b000, ///< Fast internal oscillator (FRC)
    SYSCLOCK_SRC_FRCPLL = 0b001, ///< Fast internal oscillator (FRC) with PLL
    SYSCLOCK_SRC_FRC16  = 0b110, ///< Fast internal oscillator (FRC) divided by 16
    SYSCLOCK_SRC_FRCDIV = 0b111  ///< Fast internal oscillator (FRC) divided by FRCDIV
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_LPRC   SYSCLOCK_SRC_LPRC
#define SYSCLOCK_SRC_SOSC   SYSCLOCK_SRC_SOSC
#define SYSCLOCK_SRC_POSC   SYSCLOCK_SRC_POSC
#define SYSCLOCK_SRC_PPLL   SYSCLOCK_SRC_PPLL
#define SYSCLOCK_SRC_FRC    SYSCLOCK_SRC_FRC
#define SYSCLOCK_SRC_FRCPLL SYSCLOCK_SRC_FRCPLL
#define SYSCLOCK_SRC_FRC16  SYSCLOCK_SRC_FRC16
#define SYSCLOCK_SRC_FRCDIV SYSCLOCK_SRC_FRCDIV
#define SYSCLOCK_SRC_MAX    7

#ifdef SYSCLOCK_DEBUG
 static const char *sysclock_sources_str[] = { "FRC", "FRCPLL", "POSC", "PPLL", "SOSC", "LPRC", "FRC16", "FRCDIV" };
#endif

// periph clock assoc
#define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_SYSCLK ///< CPU clock bus
#define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_PBCLK  ///< CAN clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_PMP    SYSCLOCK_CLOCK_PBCLK  ///< PMP clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_PBCLK  ///< I2C clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_PBCLK  ///< UART clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_PBCLK  ///< SPI clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_PBCLK  ///< TIMER clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_OC     SYSCLOCK_CLOCK_PBCLK  ///< OC clock bus mapped to peripherical bus
#define SYSCLOCK_CLOCK_IC     SYSCLOCK_CLOCK_PBCLK  ///< IC clock bus mapped to peripherical bus

/*
 *               Fplli                     Fsys
 *        ______   |    _______              |
 *  Fin  |      |  v   |       |     _____   |
 * ----->| /N1  |----->|       |    |     |  v
 *       |______|      |  PFD  |--->| VCO |-+-->
 *                  +->|       |    |_____| |
 *                  |  |_______|            |
 *                  |        _______        |
 *                  |       |       |       |
 *                  +-------|   /M  |-------+
 *                          |_______|
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 */

#if defined(DEVICE_33FJ16GP101) || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16MC101) \
 || defined(DEVICE_33FJ16MC102) || defined(DEVICE_33FJ32GP101) || defined(DEVICE_33FJ32GP102) \
 || defined(DEVICE_33FJ32GP104) || defined(DEVICE_33FJ32MC101) || defined(DEVICE_33FJ32MC102) \
 || defined(DEVICE_33FJ32MC104)
 #define SYSCLOCK_PLL4 // fixed x4 PLL
#endif

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
// pre-diviser N
 #define SYSCLOCK_N1_MIN 2
 #define SYSCLOCK_N1_MAX 33
 #define SYSCLOCK_FPLLI_MIN 800000
 #define SYSCLOCK_FPLLI_MAX 8000000

 #define SYSCLOCK_FSYS_MIN 120000000
 #define SYSCLOCK_FSYS_MAX 340000000

 #define SYSCLOCK_FOSC_MAX 120000000

#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic33fj)
 #ifndef SYSCLOCK_PLL4
  #define SYSCLOCK_N1_MIN 2
  #define SYSCLOCK_N1_MAX 33
  #define SYSCLOCK_FPLLI_MIN 800000
  #define SYSCLOCK_FPLLI_MAX 8000000
 
  #define SYSCLOCK_FSYS_MIN 100000000
  #define SYSCLOCK_FSYS_MAX 200000000
 
  #define SYSCLOCK_FOSC_MAX 80000000

 #else
  #define SYSCLOCK_FPLLI_MIN 3000000
  #define SYSCLOCK_FPLLI_MAX 8000000

  #define SYSCLOCK_FSYS_MIN 1000000
  #define SYSCLOCK_FSYS_MAX 32000000
  #define SYSCLOCK_FOSC_MAX 16000000
 #endif
#else
 #error Unsuported ARCHI
#endif

#if defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) \
 || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) \
 || defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506) \
 || defined(DEVICE_33EP128GS702) || defined(DEVICE_33EP128GS704) || defined(DEVICE_33EP128GS705) \
 || defined(DEVICE_33EP128GS706) || defined(DEVICE_33EP128GS708) || defined(DEVICE_33EP128GS804) \
 || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806) || defined(DEVICE_33EP128GS808) \
 || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204) || defined(DEVICE_33EP128MC206) \
 || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506) \
 || defined(DEVICE_33EP16GS502) || defined(DEVICE_33EP16GS504) || defined(DEVICE_33EP16GS505) \
 || defined(DEVICE_33EP16GS506) || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) \
 || defined(DEVICE_33EP256GM310) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706) \
 || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504) \
 || defined(DEVICE_33EP256GP506) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) \
 || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) \
 || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) \
 || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) \
 || defined(DEVICE_33EP32GP504) || defined(DEVICE_33EP32GS502) || defined(DEVICE_33EP32GS504) \
 || defined(DEVICE_33EP32GS505) || defined(DEVICE_33EP32GS506) || defined(DEVICE_33EP32MC202) \
 || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) \
 || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP512GM304) \
 || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) || defined(DEVICE_33EP512GM604) \
 || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP502) \
 || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506) || defined(DEVICE_33EP512GP806) \
 || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) || defined(DEVICE_33EP512MC206) \
 || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) \
 || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814) \
 || defined(DEVICE_33EP64GP502) || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504) \
 || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64GS502) || defined(DEVICE_33EP64GS504) \
 || defined(DEVICE_33EP64GS505) || defined(DEVICE_33EP64GS506) || defined(DEVICE_33EP64GS708) \
 || defined(DEVICE_33EP64GS804) || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) \
 || defined(DEVICE_33EP64GS808) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) \
 || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) \
 || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) \
 || defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM004) || defined(DEVICE_33EV128GM006) \
 || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106) \
 || defined(DEVICE_33EV256GM002) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006) \
 || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM104) || defined(DEVICE_33EV256GM106) \
 || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) \
 || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) \
 || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM004) || defined(DEVICE_33EV64GM006) \
 || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106) \
 || defined(DEVICE_33FJ06GS001) || defined(DEVICE_33FJ06GS101) || defined(DEVICE_33FJ06GS101A) \
 || defined(DEVICE_33FJ06GS102) || defined(DEVICE_33FJ06GS102A) || defined(DEVICE_33FJ06GS202) \
 || defined(DEVICE_33FJ06GS202A) || defined(DEVICE_33FJ09GS302) || defined(DEVICE_33FJ16GS402) \
 || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ16GS502) || defined(DEVICE_33FJ16GS504) \
 || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608) \
 || defined(DEVICE_33FJ32GS610) || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64GS606) \
 || defined(DEVICE_33FJ64GS608) || defined(DEVICE_33FJ64GS610)
 #define SYSCLOCK_HAVE_REFCLOCKO
#endif

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) \
 || defined(ARCHI_pic24hj)
 #define FRC_BASE_FREQ 7370000
 #if defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) \
  || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) \
  || defined(DEVICE_33EP512MU814) || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814) \
  || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512GU814)
  #define OSCTUN_D 27637
 #else
  #define OSCTUN_D 3464
 #endif
#elif defined(ARCHI_dspic33fj)
 #if defined(DEVICE_33FJ06GS101) || defined(DEVICE_33FJ06GS101A) || defined(DEVICE_33FJ06GS102) \
  || defined(DEVICE_33FJ06GS102A) || defined(DEVICE_33FJ06GS202) || defined(DEVICE_33FJ06GS202A) \
  || defined(DEVICE_33FJ09GS302) || defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) \
  || defined(DEVICE_33FJ128GP206) || defined(DEVICE_33FJ128GP206A) || defined(DEVICE_33FJ128GP306) \
  || defined(DEVICE_33FJ128GP306A) || defined(DEVICE_33FJ128GP310) || defined(DEVICE_33FJ128GP310A) \
  || defined(DEVICE_33FJ128GP706) || defined(DEVICE_33FJ128GP706A) || defined(DEVICE_33FJ128GP708) \
  || defined(DEVICE_33FJ128GP708A) || defined(DEVICE_33FJ128GP710) || defined(DEVICE_33FJ128GP710A) \
  || defined(DEVICE_33FJ128GP802) || defined(DEVICE_33FJ128GP804) || defined(DEVICE_33FJ128MC202) \
  || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC506) || defined(DEVICE_33FJ128MC506A) \
  || defined(DEVICE_33FJ128MC510) || defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC706) \
  || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC708) || defined(DEVICE_33FJ128MC708A) \
  || defined(DEVICE_33FJ128MC710) || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ128MC802) \
  || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ12GP201) || defined(DEVICE_33FJ12GP202) \
  || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202) || defined(DEVICE_33FJ16GP304) \
  || defined(DEVICE_33FJ16GS402) || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ16GS502) \
  || defined(DEVICE_33FJ16GS504) || defined(DEVICE_33FJ16MC304) || defined(DEVICE_33FJ256GP506) \
  || defined(DEVICE_33FJ256GP506A) || defined(DEVICE_33FJ256GP510) || defined(DEVICE_33FJ256GP510A) \
  || defined(DEVICE_33FJ256GP710) || defined(DEVICE_33FJ256GP710A) || defined(DEVICE_33FJ256MC510) \
  || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710) || defined(DEVICE_33FJ256MC710A) \
  || defined(DEVICE_33FJ32GP202) || defined(DEVICE_33FJ32GP204) || defined(DEVICE_33FJ32GP302) \
  || defined(DEVICE_33FJ32GP304) || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC204) \
  || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) || defined(DEVICE_33FJ64GP202) \
  || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP206) || defined(DEVICE_33FJ64GP206A) \
  || defined(DEVICE_33FJ64GP306) || defined(DEVICE_33FJ64GP306A) || defined(DEVICE_33FJ64GP310) \
  || defined(DEVICE_33FJ64GP310A) || defined(DEVICE_33FJ64GP706) || defined(DEVICE_33FJ64GP706A) \
  || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A) || defined(DEVICE_33FJ64GP710) \
  || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64GP804) \
  || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC506) \
  || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508) || defined(DEVICE_33FJ64MC508A) \
  || defined(DEVICE_33FJ64MC510) || defined(DEVICE_33FJ64MC510A) || defined(DEVICE_33FJ64MC706) \
  || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710) || defined(DEVICE_33FJ64MC710A) \
  || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804)
  #define FRC_BASE_FREQ 7370000
  #define OSCTUN_D 27637 // +/- 0.375%
 #elif defined(DEVICE_33FJ16GP101) || defined(DEVICE_33FJ16GP102) || defined(DEVICE_33FJ16MC101) \
    || defined(DEVICE_33FJ16MC102) || defined(DEVICE_33FJ32GP101) || defined(DEVICE_33FJ32GP102) \
    || defined(DEVICE_33FJ32GP104) || defined(DEVICE_33FJ32MC101) || defined(DEVICE_33FJ32MC102) \
    || defined(DEVICE_33FJ32MC104)
  #define FRC_BASE_FREQ 7370000
  #define OSCTUN_D 3464 // +/- 0.047%
  #elif defined(DEVICE_33FJ128GP202) || defined(DEVICE_33FJ128GP204) || defined(DEVICE_33FJ128GP206) \
     || defined(DEVICE_33FJ128GP206A) || defined(DEVICE_33FJ128GP306) || defined(DEVICE_33FJ128GP306A) \
     || defined(DEVICE_33FJ128GP310) || defined(DEVICE_33FJ128GP310A) || defined(DEVICE_33FJ128GP706) \
     || defined(DEVICE_33FJ128GP706A) || defined(DEVICE_33FJ128GP708) || defined(DEVICE_33FJ128GP708A) \
     || defined(DEVICE_33FJ128GP710) || defined(DEVICE_33FJ128GP710A) || defined(DEVICE_33FJ128GP802) \
     || defined(DEVICE_33FJ128GP804) || defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) \
     || defined(DEVICE_33FJ128MC506) || defined(DEVICE_33FJ128MC506A) || defined(DEVICE_33FJ128MC510) \
     || defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC706) || defined(DEVICE_33FJ128MC706A) \
     || defined(DEVICE_33FJ128MC708) || defined(DEVICE_33FJ128MC708A) || defined(DEVICE_33FJ128MC710) \
     || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ128MC802) || defined(DEVICE_33FJ128MC804) \
     || defined(DEVICE_33FJ12GP201) || defined(DEVICE_33FJ12GP202) || defined(DEVICE_33FJ12MC201) \
     || defined(DEVICE_33FJ12MC202) || defined(DEVICE_33FJ16GP304) || defined(DEVICE_33FJ16MC304) \
     || defined(DEVICE_33FJ256GP506) || defined(DEVICE_33FJ256GP506A) || defined(DEVICE_33FJ256GP510) \
     || defined(DEVICE_33FJ256GP510A) || defined(DEVICE_33FJ256GP710) || defined(DEVICE_33FJ256GP710A) \
     || defined(DEVICE_33FJ256MC510) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710) \
     || defined(DEVICE_33FJ256MC710A) || defined(DEVICE_33FJ32GP202) || defined(DEVICE_33FJ32GP204) \
     || defined(DEVICE_33FJ32GP302) || defined(DEVICE_33FJ32GP304) || defined(DEVICE_33FJ32MC202) \
     || defined(DEVICE_33FJ32MC204) || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) \
     || defined(DEVICE_33FJ64GP202) || defined(DEVICE_33FJ64GP204) || defined(DEVICE_33FJ64GP206) \
     || defined(DEVICE_33FJ64GP206A) || defined(DEVICE_33FJ64GP306) || defined(DEVICE_33FJ64GP306A) \
     || defined(DEVICE_33FJ64GP310) || defined(DEVICE_33FJ64GP310A) || defined(DEVICE_33FJ64GP706) \
     || defined(DEVICE_33FJ64GP706A) || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A) \
     || defined(DEVICE_33FJ64GP710) || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64GP802) \
     || defined(DEVICE_33FJ64GP804) || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) \
     || defined(DEVICE_33FJ64MC506) || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508) \
     || defined(DEVICE_33FJ64MC508A) || defined(DEVICE_33FJ64MC510) || defined(DEVICE_33FJ64MC510A) \
     || defined(DEVICE_33FJ64MC706) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710) \
     || defined(DEVICE_33FJ64MC710A) || defined(DEVICE_33FJ64MC802) || defined(DEVICE_33FJ64MC804)
  #define FRC_BASE_FREQ 7370000
  #define OSCTUN_D 27637 // +/- 0.375%
 #elif defined(DEVICE_33FJ16GS402) || defined(DEVICE_33FJ16GS404) || defined(DEVICE_33FJ32GS406) \
    || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608) || defined(DEVICE_33FJ32GS610) \
    || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608) \
    || defined(DEVICE_33FJ64GS610)
  #define FRC_BASE_FREQ 7370000
  #define OSCTUN_D 6913 // +/- 0.0938%
 #endif
#elif defined(ARCHI_pic24fj) || defined(ARCHI_pic24fj)
 #define FRC_BASE_FREQ 8000000
 #define OSCTUN_D 4000
#endif

int sysclock_setPLLClock(uint32_t freq, uint8_t src);

#endif // SYSCLOCK_PIC24_DSPIC30F_DSPIC33_H
