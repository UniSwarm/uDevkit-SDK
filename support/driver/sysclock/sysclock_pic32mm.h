/**
 * @file sysclock_pic32mm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date July 11, 2017, 18:30 PM
 *
 * @brief System clock support for udevkit for PIC32MM family
 *
 * Implementation based on Microchip document DS60001329B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001329b.pdf
 */

#ifndef SYSCLOCK_PIC32MM_H
#define SYSCLOCK_PIC32MM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sysclock.h"

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_SYSCLK = 0x0,  ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK,         ///< peripheral bus
    SYSCLOCK_CLOCK_REFCLK         ///< reference clock module
} SYSCLOCK_CLOCK;

// periph clock assoc
#define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_SYSCLK  ///< CPU clock bus
#define SYSCLOCK_CLOCK_USB   SYSCLOCK_CLOCK_USBCLK  ///< USB clock bus
#define SYSCLOCK_CLOCK_CAN   SYSCLOCK_CLOCK_PBCLK   ///< CAN clock bus mapped to peripheral bus 5
#define SYSCLOCK_CLOCK_PMP   SYSCLOCK_CLOCK_PBCLK   ///< PMP clock bus mapped to peripheral bus 2
#define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_PBCLK   ///< I2C clock bus mapped to peripheral bus 2
#define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_PBCLK   ///< UART clock bus mapped to peripheral bus 2
#define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_PBCLK   ///< SPI clock bus mapped to peripheral bus 2
#define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_PBCLK   ///< TIMER clock bus mapped to peripheral bus 3
#define SYSCLOCK_CLOCK_OC    SYSCLOCK_CLOCK_PBCLK   ///< OC clock bus mapped to peripheral bus 3
#define SYSCLOCK_CLOCK_IC    SYSCLOCK_CLOCK_PBCLK   ///< IC clock bus mapped to peripheral bus 3

// clock source
typedef enum
{
    SYSCLOCK_SRC_LPRC = 0b101,  ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_SOSC = 0b100,  ///< Secondary oscillator (SOSC)
    SYSCLOCK_SRC_POSC = 0b010,  ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_SPLL = 0b001,  ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC = 0b000    ///< Fast internal oscillator (FRC)
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_LPRC SYSCLOCK_SRC_LPRC
#define SYSCLOCK_SRC_SOSC SYSCLOCK_SRC_SOSC
#define SYSCLOCK_SRC_POSC SYSCLOCK_SRC_POSC
#define SYSCLOCK_SRC_SPLL SYSCLOCK_SRC_SPLL
#define SYSCLOCK_SRC_FRC  SYSCLOCK_SRC_FRC
#define SYSCLOCK_SRC_MAX  5

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"FRC", "SPLL", "POSC", "", "SOSC", "LPRC"};
#endif

/*  main PLL
 *        __          _____         _____
 * FRC-->|  \  Fplli |     | Fvco  |     | FSLL
 *       |   |------>| x M |------>| /Ny |------>
 * Posc->|__/        |_____|       |_____|
 *     PLLICLK
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FVCO_MIN  > Fvco  > SYSCLOCK_FVCO_MAX
 *  SYSCLOCK_FPLLO_MIN > FSLL > SYSCLOCK_FPLLO_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 *  M = {2, 3, 4, 6, 8, 12, 24} runtime editable
 *  Ny = {1, 2, 4, 8, 16, 32, 64, 256} runtime editable
 */

// pre-diviser N
#define SYSCLOCK_NX_MIN 1
#define SYSCLOCK_NX_MAX 8

#define SYSCLOCK_FPLLI_MIN 2000000    //   2 MHz
#define SYSCLOCK_FPLLI_MAX 24000000   //  24 MHz
#define SYSCLOCK_FVCO_MIN  160000000  //  16 MHz
#define SYSCLOCK_FVCO_MAX  960000000  //  96 MHz

#define SYSCLOCK_FSLL_MIN 20000000   //   2 MHz
#define SYSCLOCK_FSLL_MAX 960000000  //  96 MHz

#define SYSCLOCK_FSYS_MAX 25000000

int sysclock_setPLLClock(uint32_t freq, uint8_t src);

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_PIC32MM_H
