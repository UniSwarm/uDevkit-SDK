/**
 * @file sysclock_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip documents DS70186D, DS70580C, DS70005131A, DS70307E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70216D.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70580C.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005131a.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70307E.pdf
 */

#include "sysclock.h"

#ifndef SYSCLOCK_PIC24_DSPIC33_H
#define SYSCLOCK_PIC24_DSPIC33_H

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

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
// pre-diviser N
  #define SYSCLOCK_N1_MIN 2
  #define SYSCLOCK_N1_MAX 33
  #define SYSCLOCK_FPLLI_MIN 800000
  #define SYSCLOCK_FPLLI_MAX 8000000

  #define SYSCLOCK_FSYS_MIN 120000000
  #define SYSCLOCK_FSYS_MAX 340000000

  #define SYSCLOCK_FOSC_MAX 120000000

#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
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

int sysclock_setClockWPLL(uint32_t freq);
uint32_t sysclock_getPeriphClock();

#endif // SYSCLOCK_PIC24_DSPIC30F_DSPIC33_H
