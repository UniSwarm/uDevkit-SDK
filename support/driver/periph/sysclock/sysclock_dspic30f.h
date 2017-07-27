/**
 * @file sysclock_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for dsPIC30F
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

// TODO check all of them

// clock source
typedef enum {
    SYSCLOCK_SRC_LPRC   = 0b101, ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_SOSC   = 0b100, ///< SOSC
    SYSCLOCK_SRC_POSC   = 0b010, ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_PPLL   = 0b011, ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC    = 0b000, ///< Fast internal oscilator (FRC)
    SYSCLOCK_SRC_FRCPLL = 0b001, ///< Fast internal oscilator (FRC)
    SYSCLOCK_SRC_FRC16  = 0b110, ///< Fast internal oscilator (FRC) divided by 16
    SYSCLOCK_SRC_FRCDIV = 0b111  ///< Fast internal oscilator (FRC) divided by FRCDIV
} SYSCLOCK_SOURCE;

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
