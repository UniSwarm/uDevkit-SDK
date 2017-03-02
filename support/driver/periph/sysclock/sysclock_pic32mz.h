/**
 * @file sysclock_pic32mz.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for PIC32MZ family (DA, EC and EF)
 */

#include "sysclock.h"

#ifndef SYSCLOCK_PIC32MZ_H
#define SYSCLOCK_PIC32MZ_H

// bus clock
typedef enum {
    SYSCLOCK_CLOCK_SYSCLK = 0x0,
    SYSCLOCK_CLOCK_PBCLK1,
    SYSCLOCK_CLOCK_PBCLK2,
    SYSCLOCK_CLOCK_PBCLK3,
    SYSCLOCK_CLOCK_PBCLK4,
    SYSCLOCK_CLOCK_PBCLK5,
    SYSCLOCK_CLOCK_PBCLK6,
    SYSCLOCK_CLOCK_PBCLK7,
    SYSCLOCK_CLOCK_PBCLK8
} SYSCLOCK_CLOCK;
uint32_t sysclock_getPeriphClock(uint8_t busClock);

// periph clock assoc
#define SYSCLOCK_CLOCK_USB    SYSCLOCK_CLOCK_USBCLK
#define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_PBCLK5
#define SYSCLOCK_CLOCK_PMP    SYSCLOCK_CLOCK_PBCLK2
#define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_PBCLK2
#define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_PBCLK2
#define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_PBCLK2
#define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_PBCLK3
#define SYSCLOCK_CLOCK_OC     SYSCLOCK_CLOCK_PBCLK3
#define SYSCLOCK_CLOCK_IC     SYSCLOCK_CLOCK_PBCLK3

/*  main PLL
 *               Fplli       Fvco        Fpllo
 *        _____   |   _______  |   _____   |
 *  Fin  |     |  v  |       | v  |     |  v
 * ----->| /Nx |---->|  x M  |--->| /Ny |---->
 *       |_____|     |_______|    |_____|
 *                      PLL
 *  Fin from
 *  Posc or FRC (PLLICLK to choose)
 *
 *  SYSCLOCK_FPLLI_MIN > Fplli > SYSCLOCK_FPLLI_MAX
 *  SYSCLOCK_FPLLO_MIN > Fpllo > SYSCLOCK_FPLLO_MAX
 *  SYSCLOCK_FSYS_MIN  > Fsys  > SYSCLOCK_FSYS_MAX
 *  Nx = {1-8} runtime editable
 *  M = {1-128} runtime editable
 *  Ny = {2, 4, 8, 16, 32} runtime editable
 */

// pre-diviser N
#define SYSCLOCK_NX_MIN 1
#define SYSCLOCK_NX_MAX 8

#define SYSCLOCK_FPLLI_MIN   5000000    //   5 MHz
#define SYSCLOCK_FPLLI_MAX  64000000    //  64 MHz
#define SYSCLOCK_FVCO_MIN  350000000    // 350 MHz
#define SYSCLOCK_FVCO_MAX  700000000    // 700 MHz
#define SYSCLOCK_FPLLO_MIN  10000000    //  10 MHz
#define SYSCLOCK_FPLLO_MAX 200000000    // 200 MHz

#define SYSCLOCK_FSYS_MIN 8000000
#define SYSCLOCK_FSYS_MAX 200000000

#define SYSCLOCK_FOSC_MAX 120000000

int sysclock_setClockWPLL(uint32_t freq);

#endif // SYSCLOCK_PIC32MZ_H
