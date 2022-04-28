/**
 * @file sysclock_pic32mz_mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date March 01, 2016, 22:10 PM
 *
 * @brief System clock support for udevkit for PIC32MZ family (DA, EC and EF)
 * and PIC32MK
 *
 * Implementation based on Microchip document DS60001250B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001250B.pdf
 */

#ifndef SYSCLOCK_PIC32MZ_MK_H
#define SYSCLOCK_PIC32MZ_MK_H

#include "sysclock.h"

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_SYSCLK = 0x0,  ///< main sysclock
    SYSCLOCK_CLOCK_PBCLK1,        ///< peripheral bus 1
    SYSCLOCK_CLOCK_PBCLK2,        ///< peripheral bus 2
    SYSCLOCK_CLOCK_PBCLK3,        ///< peripheral bus 3
    SYSCLOCK_CLOCK_PBCLK4,        ///< peripheral bus 4
    SYSCLOCK_CLOCK_PBCLK5,        ///< peripheral bus 5
    SYSCLOCK_CLOCK_PBCLK6,        ///< peripheral bus 6
    SYSCLOCK_CLOCK_PBCLK7,        ///< peripheral bus 7
    SYSCLOCK_CLOCK_PBCLK8,        ///< peripheral bus 8
    SYSCLOCK_CLOCK_REFCLOCK1,     ///< Refrence clock 1
    SYSCLOCK_CLOCK_REFCLOCK2,     ///< Refrence clock 2
    SYSCLOCK_CLOCK_REFCLOCK3,     ///< Refrence clock 3
    SYSCLOCK_CLOCK_REFCLOCK4,     ///< Refrence clock 4
} SYSCLOCK_CLOCK;

// periph clock assoc
#if defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
#    define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_PBCLK7  ///< CPU clock bus
#    define SYSCLOCK_CLOCK_USB   SYSCLOCK_CLOCK_USBCLK  ///< USB clock bus
#    define SYSCLOCK_CLOCK_CAN   SYSCLOCK_CLOCK_PBCLK5  ///< CAN clock bus mapped to peripheral bus 5
#    define SYSCLOCK_CLOCK_PMP   SYSCLOCK_CLOCK_PBCLK2  ///< PMP clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_PBCLK2  ///< I2C clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_PBCLK2  ///< UART clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_PBCLK2  ///< SPI clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_PBCLK3  ///< TIMER clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_OC    SYSCLOCK_CLOCK_PBCLK3  ///< OC clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_IC    SYSCLOCK_CLOCK_PBCLK3  ///< IC clock bus mapped to peripheral bus 3

#elif defined(ARCHI_pic32mk)
#    define SYSCLOCK_CLOCK_CPU SYSCLOCK_CLOCK_PBCLK7  ///< CPU clock bus
#    define SYSCLOCK_CLOCK_USB SYSCLOCK_CLOCK_USBCLK  ///< USB clock bus
#    if defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                   \
        || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#        define SYSCLOCK_CLOCK_CAN SYSCLOCK_CLOCK_REFCLOCK4  ///< CAN clock bus mapped to refclock4
#    else
#        define SYSCLOCK_CLOCK_CAN SYSCLOCK_CLOCK_PBCLK5  ///< CAN clock bus mapped to peripheral bus 5
#    endif
#    define SYSCLOCK_CLOCK_PMP     SYSCLOCK_CLOCK_PBCLK2  ///< PMP clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_I2C     SYSCLOCK_CLOCK_PBCLK2  ///< I2C clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_UART1_2 SYSCLOCK_CLOCK_PBCLK2  ///< UART 1 to 2 clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_UART3_6 SYSCLOCK_CLOCK_PBCLK3  ///< UART 3 to 6 clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_SPI1_2  SYSCLOCK_CLOCK_PBCLK2  ///< SPI 1 to 2 clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_SPI3_6  SYSCLOCK_CLOCK_PBCLK3  ///< SPI 3 to 6 clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_TIMER   SYSCLOCK_CLOCK_PBCLK2  ///< TIMER clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_OC1_9   SYSCLOCK_CLOCK_PBCLK2  ///< OC 1 to 9 clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_OC10_16 SYSCLOCK_CLOCK_PBCLK3  ///< OC 10 to 16 clock bus mapped to peripheral bus 3
#    define SYSCLOCK_CLOCK_IC1_9   SYSCLOCK_CLOCK_PBCLK2  ///< IC 1 to 9 clock bus mapped to peripheral bus 2
#    define SYSCLOCK_CLOCK_IC10_16 SYSCLOCK_CLOCK_PBCLK3  ///< IC 10 to 16 clock bus mapped to peripheral bus 3

#endif

// clock source
typedef enum
{
#if defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
    SYSCLOCK_SRC_FRC2 = 0b111,  ///< sysclock from Fast RC Oscillator (FRC) divided by FRCDIV
    SYSCLOCK_SRC_BFRC = 0b110,  ///< backup FRC, cannot be choose by user
#endif
    SYSCLOCK_SRC_LPRC = 0b101,  ///< Low-Power RC (LPRC) Oscillator
#if defined(ARCHI_pic32mk)
    SYSCLOCK_SRC_UPLL = 0b011,  ///< USB PLL (UPLL)
#endif
    SYSCLOCK_SRC_SOSC = 0b100,  ///< Secondary oscillator (SOSC)
    SYSCLOCK_SRC_POSC = 0b010,  ///< Primary Oscillator (POSC) HS and EC
    SYSCLOCK_SRC_SPLL = 0b001,  ///< System PLL (SPLL)
    SYSCLOCK_SRC_FRC = 0b000    ///< same as SYSCLOCK_SRC_FRC
} SYSCLOCK_SOURCE;

typedef enum
{
    SYSCLOCK_REFCLK_SRC_REFCLKI = 0b1000,
    SYSCLOCK_REFCLK_SRC_SPLL = 0b0111,
    SYSCLOCK_REFCLK_SRC_UPLL = 0b0110,
    SYSCLOCK_REFCLK_SRC_SOSC = 0b0101,
    SYSCLOCK_REFCLK_SRC_LPRC = 0b0100,
    SYSCLOCK_REFCLK_SRC_FRC = 0b0011,
    SYSCLOCK_REFCLK_SRC_POSC = 0b0010,
    SYSCLOCK_REFCLK_SRC_PBCLK1 = 0b0001,
    SYSCLOCK_REFCLK_SRC_SYSCLOCK = 0b0000
} SYSCLOCK_REFCLK_SRC;

#if defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
#    define SYSCLOCK_SRC_FRC2 SYSCLOCK_SRC_FRC2
#    define SYSCLOCK_SRC_BFRC SYSCLOCK_SRC_BFRC
#elif defined(ARCHI_pic32mk)
#    define SYSCLOCK_SRC_UPLL SYSCLOCK_SRC_UPLL
#endif
#define SYSCLOCK_SRC_LPRC SYSCLOCK_SRC_LPRC
#define SYSCLOCK_SRC_POSC SYSCLOCK_SRC_POSC
#define SYSCLOCK_SRC_SPLL SYSCLOCK_SRC_SPLL
#define SYSCLOCK_SRC_FRC  SYSCLOCK_SRC_FRC
#define SYSCLOCK_SRC_MAX  7

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"FRC", "SPLL", "POSC", "UPLL", "SOSC", "LPRC", "BFRC", "FRC2"};
#endif

/*  main PLL
 *        __         _____         _____         _____
 * FRC-->|  \  Fin  |     | Fplli |     | Fvco  |     | Fpllo
 *       |   |----->| /Nx |------>| x M |------>| /Ny |------>
 * Posc->|__/       |_____|       |_____|       |_____|
 *     PLLICLK
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FVCO_MIN  > Fvco  > SYSCLOCK_FVCO_MAX
 *  SYSCLOCK_FPLLO_MIN > Fpllo > SYSCLOCK_FPLLO_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 *  Nx = {1-8} runtime editable
 *  M = {1-128} runtime editable
 *  Ny = {2, 4, 8, 16, 32} runtime editable
 */

#if defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
// pre-diviser N
#    define SYSCLOCK_NX_MIN 1
#    define SYSCLOCK_NX_MAX 8

#    define SYSCLOCK_FPLLI_MIN 5000000    //   5 MHz
#    define SYSCLOCK_FPLLI_MAX 64000000   //  64 MHz
#    define SYSCLOCK_FVCO_MIN  350000000  // 350 MHz
#    define SYSCLOCK_FVCO_MAX  700000000  // 700 MHz
#    define SYSCLOCK_FPLLO_MIN 10000000   //  10 MHz
#    define SYSCLOCK_FPLLO_MAX 200000000  // 200 MHz

#    define SYSCLOCK_FSYS_MIN 8000000
#    define SYSCLOCK_FSYS_MAX 200000000

#    define SYSCLOCK_FOSC_MAX 200000000

#elif defined(ARCHI_pic32mk)
// pre-diviser N
#    define SYSCLOCK_NX_MIN 1
#    define SYSCLOCK_NX_MAX 8

#    define SYSCLOCK_FPLLI_MIN 5000000    //   5 MHz
#    define SYSCLOCK_FPLLI_MAX 64000000   //  64 MHz
#    define SYSCLOCK_FVCO_MIN  350000000  // 350 MHz
#    define SYSCLOCK_FVCO_MAX  700000000  // 700 MHz
#    define SYSCLOCK_FPLLO_MIN 10000000   //  10 MHz
#    define SYSCLOCK_FPLLO_MAX 120000000  // 120 MHz

#    define SYSCLOCK_FSYS_MIN 8000000
#    define SYSCLOCK_FSYS_MAX 120000000

#    define SYSCLOCK_FOSC_MAX 120000000
#endif

int sysclock_setPLLClock(uint32_t freq, uint8_t src);
uint32_t sysclock_getPLLClock(void);

#endif  // SYSCLOCK_PIC32MZ_MK_H
