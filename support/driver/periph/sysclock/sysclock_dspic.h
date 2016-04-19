/**
 * @file sysclock_dspic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog
 */

#include "sysclock.h"

#ifndef SYSCLOCK_DSPIC_H
#define SYSCLOCK_DSPIC_H

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

#if defined(ARCHI_dspic33ep)
// pre-diviser N
#define SYSCLOCK_N1_MIN 2
#define SYSCLOCK_N1_MAX 33
#define SYSCLOCK_FPLLI_MIN 800000
#define SYSCLOCK_FPLLI_MAX 8000000

#define SYSCLOCK_FSYS_MIN 120000000
#define SYSCLOCK_FSYS_MAX 340000000

#define SYSCLOCK_FOSC_MAX 120000000

#elif defined(ARCHI_dspic33fj)
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

int setSystemClockWPLL(uint32_t freq);

#endif // SYSCLOCK_DSPIC_H
