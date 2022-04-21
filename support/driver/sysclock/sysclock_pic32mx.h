/**
 * @file sysclock_pic32mx.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for udevkit for PIC32MX family
 *
 * Implementation based on Microchip document DS61112H :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61112H.pdf
 */

#include "sysclock.h"

#ifndef SYSCLOCK_PIC32MX_H
#    define SYSCLOCK_PIC32MX_H

#    if defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B)                           \
        || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F064B)                        \
        || defined(DEVICE_32MX130F064C) || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX130F128L)                        \
        || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B) || defined(DEVICE_32MX150F256L)                        \
        || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX150F256H)                        \
        || defined(DEVICE_32MX154F128D) || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D)                        \
        || defined(DEVICE_32MX170F512H) || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D) || defined(DEVICE_32MX175F256B)                        \
        || defined(DEVICE_32MX175F256D)
#        define SYSCLOCK_NOUSB
#    endif

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_SYSCLK = 0x0,  ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK,         ///< peripherals bus
    SYSCLOCK_CLOCK_REFCLK,        ///< reference clock module
#    ifndef SYSCLOCK_NOUSB
    SYSCLOCK_SRC_UPLL = 0b011,  ///< USB PLL (UPLL)
#    endif
} SYSCLOCK_CLOCK;

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_SYSCLK  ///< CPU clock bus
#    define SYSCLOCK_CLOCK_CAN   SYSCLOCK_CLOCK_PBCLK   ///< CAN clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_PMP   SYSCLOCK_CLOCK_PBCLK   ///< PMP clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_PBCLK   ///< I2C clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_PBCLK   ///< UART clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_PBCLK   ///< SPI clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_PBCLK   ///< TIMER clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_OC    SYSCLOCK_CLOCK_PBCLK   ///< OC clock bus mapped to peripheral bus
#    define SYSCLOCK_CLOCK_IC    SYSCLOCK_CLOCK_PBCLK   ///< IC clock bus mapped to peripheral bus

// clock source
typedef enum
{
    SYSCLOCK_SRC_LPRC = 0b101,    ///< Low-Power RC (LPRC) Oscillator
    SYSCLOCK_SRC_SOSC = 0b100,    ///< Secondary oscillator (SOSC)
    SYSCLOCK_SRC_POSC = 0b010,    ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_PPLL = 0b011,    ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC = 0b000,     ///< Fast internal oscillator (FRC)
    SYSCLOCK_SRC_FRCPLL = 0b001,  ///< Fast internal oscillator (FRC)
    SYSCLOCK_SRC_FRC16 = 0b110,   ///< Fast internal oscillator (FRC) divided by 16
    SYSCLOCK_SRC_FRCDIV = 0b111   ///< Fast internal oscillator (FRC) divided by FRCDIV
} SYSCLOCK_SOURCE;
#    define SYSCLOCK_SRC_LPRC   SYSCLOCK_SRC_LPRC
#    define SYSCLOCK_SRC_SOSC   SYSCLOCK_SRC_SOSC
#    define SYSCLOCK_SRC_POSC   SYSCLOCK_SRC_POSC
#    define SYSCLOCK_SRC_PPLL   SYSCLOCK_SRC_PPLL
#    define SYSCLOCK_SRC_FRC    SYSCLOCK_SRC_FRC
#    define SYSCLOCK_SRC_FRCPLL SYSCLOCK_SRC_FRCPLL
#    define SYSCLOCK_SRC_FRC16  SYSCLOCK_SRC_FRC16
#    define SYSCLOCK_SRC_FRCDIV SYSCLOCK_SRC_FRCDIV
#    define SYSCLOCK_SRC_MAX    7

#    ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"FRC", "FRCPLL", "POSC", "PPLL", "SOSC", "LPRC", "FRC16", "FRCDIV"};
#    endif

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
#    define SYSCLOCK_NX_MIN    2
#    define SYSCLOCK_NX_MAX    33
#    define SYSCLOCK_FPLLI_MIN 4000000
#    define SYSCLOCK_FPLLI_MAX 5000000

#    define SYSCLOCK_FVCO_MIN 60000000   //  60 MHz
#    define SYSCLOCK_FVCO_MAX 120000000  // 120 MHz

// compute SYSCLOCK_FOSC_MAX, the maximum sysclock frequency
#    if defined(DEVICE_32MX320F032H) || defined(DEVICE_32MX420F032H)
#        define SYSCLOCK_FOSC_MAX 40000000  //  40 MHz
#    elif defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B)                         \
        || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C)                        \
        || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX150F128B) || defined(DEVICE_32MX150F128C)                        \
        || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX130F256B)                        \
        || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F256B)                        \
        || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX210F016C) || defined(DEVICE_32MX170F512H) || defined(DEVICE_32MX170F512L)                        \
        || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B) || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D)                        \
        || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F064C) || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX250F128B)                        \
        || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX230F128L) || defined(DEVICE_32MX250F128D)                        \
        || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX250F256L)                        \
        || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D) || defined(DEVICE_32MX270F256DB) || defined(DEVICE_32MX270F512H)                       \
        || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX550F256H)                        \
        || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX570F512L)
#        define SYSCLOCK_FOSC_MAX 50000000  //  50 MHz
#    elif defined(DEVICE_32MX154F128D) || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX155F128B) || defined(DEVICE_32MX155F128D)                         \
        || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D) || defined(DEVICE_32MX175F256B) || defined(DEVICE_32MX175F256D)                        \
        || defined(DEVICE_32MX254F128D) || defined(DEVICE_32MX254F128B) || defined(DEVICE_32MX255F128B) || defined(DEVICE_32MX255F128D)                        \
        || defined(DEVICE_32MX274F256B) || defined(DEVICE_32MX274F256D) || defined(DEVICE_32MX275F256B) || defined(DEVICE_32MX275F256D)
#        define SYSCLOCK_FOSC_MAX 72000000  //  72 MHz
#    elif defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F256H)                         \
        || defined(DEVICE_32MX340F512H) || defined(DEVICE_32MX320F128L) || defined(DEVICE_32MX340F128L) || defined(DEVICE_32MX360F256L)                        \
        || defined(DEVICE_32MX360F512L) || defined(DEVICE_32MX440F512H) || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX460F256L)                        \
        || defined(DEVICE_32MX460F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F128H)                        \
        || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX564F064L)                        \
        || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064H)                        \
        || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX695F512H)                        \
        || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512L)                        \
        || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F512H)                        \
        || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX764F128L) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512L)                        \
        || defined(DEVICE_32MX795F512L) || defined(DEVICE_32MX440F128H) || defined(DEVICE_32MX440F256H)
#        define SYSCLOCK_FOSC_MAX 80000000  //  80 MHz
#    elif defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F128L)                         \
        || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX370F512L)                        \
        || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F128HB)                       \
        || defined(DEVICE_32MX450F128L) || defined(DEVICE_32MX450F256H) || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX470F512H)                        \
        || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX470F512LB)
#        define SYSCLOCK_FOSC_MAX 120000000  //  120 MHz
#    else
#        error undef device
#    endif

int sysclock_setClockWPLL(uint32_t freq);

#endif  // SYSCLOCK_PIC32MX_H
