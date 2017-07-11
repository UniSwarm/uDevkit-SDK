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
