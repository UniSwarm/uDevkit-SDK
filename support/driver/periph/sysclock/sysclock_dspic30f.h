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
uint32_t sysclock_getPeriphClock();

#endif // SYSCLOCK_DSPIC30F_H
