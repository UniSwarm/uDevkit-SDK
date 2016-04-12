/**
 * @file sysclock.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 05:12 PM
 * 
 * @brief System clock support for rtprog
 */

#ifndef SYSCLOCK_H
#define SYSCLOCK_H

#include <stdint.h>

#include "board.h"
#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
 #include "sysclock_dspic.h"
#else
 #error Unsuported ARCHI
#endif

int setSystemClock(uint32_t freq);
uint32_t getSystemClock();
uint32_t getSystemClockPeriph();
uint32_t getSystemClockCPU();

#endif // SYSCLOCK_H
