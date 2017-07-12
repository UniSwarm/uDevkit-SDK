/**
 * @file sysclock_pic32mx.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for PIC32MX family
 */

#include "sysclock.h"

#ifndef SYSCLOCK_PIC32MX_H
#define SYSCLOCK_PIC32MX_H

#if defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) \
 || defined(DEVICE_32MX120F032B) || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) \
 || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C) \
 || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX130F128L) \
 || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B) \
 || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) \
 || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX154F128D) \
 || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D) \
 || defined(DEVICE_32MX170F512H) || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D) \
 || defined(DEVICE_32MX175F256B) || defined(DEVICE_32MX175F256D)
 #define SYSCLOCK_NOUSB
#endif

// bus clock
typedef enum {
    SYSCLOCK_CLOCK_SYSCLK = 0x0,    ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK,           ///< periphericals bus
    SYSCLOCK_CLOCK_REFCLK           ///< reference clock module
#if defined(ARCHI_pic32mk)
    SYSCLOCK_SRC_UPLL  = 0b011,     ///< USB PLL (UPLL)
#endif
} SYSCLOCK_CLOCK;
uint32_t sysclock_getPeriphClock(SYSCLOCK_CLOCK busClock);
int sysclock_setPeriphClockDiv(SYSCLOCK_CLOCK busClock, uint8_t div);

// periph clock assoc
#define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_SYSCLK ///< CPU clock bus
#define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_PBCLK  ///< CAN clock bus mapped to periphericals bus 5
#define SYSCLOCK_CLOCK_PMP    SYSCLOCK_CLOCK_PBCLK  ///< PMP clock bus mapped to periphericals bus 2
#define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_PBCLK  ///< I2C clock bus mapped to periphericals bus 2
#define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_PBCLK  ///< UART clock bus mapped to periphericals bus 2
#define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_PBCLK  ///< SPI clock bus mapped to periphericals bus 2
#define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_PBCLK  ///< TIMER clock bus mapped to periphericals bus 3
#define SYSCLOCK_CLOCK_OC     SYSCLOCK_CLOCK_PBCLK  ///< OC clock bus mapped to periphericals bus 3
#define SYSCLOCK_CLOCK_IC     SYSCLOCK_CLOCK_PBCLK  ///< IC clock bus mapped to periphericals bus 3

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
SYSCLOCK_SOURCE sysclock_source();
int sysclock_switchSourceTo(SYSCLOCK_SOURCE source);

/*
 *               Fplli                    Fsys
 *        _____   |   _______      _____   |
 *  Fin  |     |  v  |       |    |     |  v
 * ----->| /Nx |---->|  x M  |--->| /Ny |---->
 *       |_____|     |_______|    |_____|
 *                      PLL
 *  Fin from
 *  Posc or FRC
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 *  Nx = {1, 2, 3, 4, 5, 6, 10, 12} -> fixed in fuses, not runtime editable
 *  M = {15, 16, 17, 18, 19, 20, 21, 24}
 */

// pre-diviser N
#define SYSCLOCK_NX_MIN 2
#define SYSCLOCK_NX_MAX 33
#define SYSCLOCK_FPLLI_MIN 4000000
#define SYSCLOCK_FPLLI_MAX 5000000

#define SYSCLOCK_FSYS_MIN 8000000
#define SYSCLOCK_FSYS_MAX 80000000

#define SYSCLOCK_FOSC_MAX 120000000

int sysclock_setClockWPLL(uint32_t freq);

#endif // SYSCLOCK_PIC32MX_H
