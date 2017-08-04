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
    SYSCLOCK_SRC_SOSC   = 0b100, ///< SOSC
    SYSCLOCK_SRC_POSC   = 0b010, ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_PPLL   = 0b011, ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC    = 0b000, ///< Fast internal oscilator (FRC)
    SYSCLOCK_SRC_FRCPLL = 0b001, ///< Fast internal oscilator (FRC) with PLL
    SYSCLOCK_SRC_FRC16  = 0b110, ///< Fast internal oscilator (FRC) divided by 16
    SYSCLOCK_SRC_FRCDIV = 0b111  ///< Fast internal oscilator (FRC) divided by FRCDIV
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
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
  #define SYSCLOCK_N1_MIN 2
  #define SYSCLOCK_N1_MAX 33
  #define SYSCLOCK_FPLLI_MIN 800000
  #define SYSCLOCK_FPLLI_MAX 8000000

  #define SYSCLOCK_FSYS_MIN 100000000
  #define SYSCLOCK_FSYS_MAX 200000000

  #define SYSCLOCK_FOSC_MAX 80000000

#else
 #error Unsuported ARCHI
#endif

int sysclock_setClockWPLL(uint32_t freq);

#endif // SYSCLOCK_PIC24_DSPIC30F_DSPIC33_H
