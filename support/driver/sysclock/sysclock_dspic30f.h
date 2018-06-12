/**
 * @file sysclock_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for udevkit for dsPIC30F
 *
 * Implementation based on Microchip documents DS70054E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70054e.pdf
 */

#include "sysclock.h"

#ifndef SYSCLOCK_DSPIC30F_H
#define SYSCLOCK_DSPIC30F_H

// bus clock
typedef enum {
    SYSCLOCK_CLOCK_SYSCLK = 0x0,    ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK            ///< peripherical bus
} SYSCLOCK_CLOCK;

// check VERSION 1 - 3 of osc module
#if defined(DEVICE_30F6010) || defined(DEVICE_30F6011) || defined(DEVICE_30F6012) \
 || defined(DEVICE_30F6013) || defined(DEVICE_30F6014)
 #define SYSCLOCK_VERSION 1
#elif defined(DEVICE_30F2010) || defined(DEVICE_30F4011) || defined(DEVICE_30F4012) \
 || defined(DEVICE_30F5011) || defined(DEVICE_30F5013)
 #define SYSCLOCK_VERSION 2
#else
 #define SYSCLOCK_VERSION 3
#endif

#if defined(DEVICE_30F1010) || defined(DEVICE_30F2020) || defined(DEVICE_30F2023)
 #define SYSCLOCK_NOPOST
#endif

#if SYSCLOCK_VERSION >= 2
 #define SYSCLOCK_PLL_FRC  // FRC can be used as input of PLL
 #define SYSCLOCK_FRC_TUNE // FRC tune
#endif
#if SYSCLOCK_VERSION >= 3
 #define SYSCLOCK_PLL_HS   // HS can be used as input of PLL
#endif

// clock source
typedef enum {
#if SYSCLOCK_VERSION >= 3
    SYSCLOCK_SRC_PLL    = 0b111, ///< System PLL (SPLL)
#endif
    SYSCLOCK_SRC_LPRC   = 0b11,  ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_POSC   = 0b10,  ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_FRC    = 0b01,  ///< Fast internal oscillator (FRC)
    SYSCLOCK_SRC_SOSC   = 0b00,  ///< Secondary oscillator (SOSC)
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_LPRC   SYSCLOCK_SRC_LPRC
#define SYSCLOCK_SRC_SOSC   SYSCLOCK_SRC_SOSC
#define SYSCLOCK_SRC_POSC   SYSCLOCK_SRC_POSC
#define SYSCLOCK_SRC_FRC    SYSCLOCK_SRC_FRC
#if SYSCLOCK_VERSION >= 3
 #define SYSCLOCK_SRC_PLL    SYSCLOCK_SRC_PLL
#endif
#define SYSCLOCK_SRC_MAX    7

#ifdef SYSCLOCK_DEBUG
 static const char *sysclock_sources_str[] = { "SOSC", "FRC", "POSC", "LPRC", "", "", "", "PLL" };
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
 *                  FPLLo
 *          _______   |   _____ 
 *         |   *M  |  v  |     |
 * Fplli-->|  PLL  |---->| / N |---> Fsys
 *         |_______|     |_____|
 *                   
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 *
 *  M = {4, 8, 16}
 *  N = {1, 4, 16, 64}
 */

// pre-diviser N
#define SYSCLOCK_FPLLI_MIN 4000000  // 4    MHz
#define SYSCLOCK_FPLLI_MAX 8330000  // 8.33 MHz

#define SYSCLOCK_FSYS_MAX 40000000  // 40   MHz

#define SYSCLOCK_FOSC_MAX 40000000  // 40   MHz

int sysclock_setClockWPLL(uint32_t freq);

#endif // SYSCLOCK_DSPIC30F_H
