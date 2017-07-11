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

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev)
 #include "sysclock_pic24_dspic33.h"
#elif defined(ARCHI_dspic30f)
 #include "sysclock_dspic30.h"
#elif defined(ARCHI_pic32mx)
 #include "sysclock_pic32mx.h"
#elif defined(ARCHI_pic32mm)
 #include "sysclock_pic32mm.h"
#elif defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) \
 || defined(ARCHI_pic32mk)
 #include "sysclock_pic32mz_mk.h"
#else
 #error Unsuported ARCHI
#endif

int sysclock_setClock(uint32_t freq);
uint32_t sysclock_getClock();
uint32_t sysclock_getCPUClock();

#endif // SYSCLOCK_H
