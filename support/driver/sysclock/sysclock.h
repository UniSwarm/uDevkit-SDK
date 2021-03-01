/**
 * @file sysclock.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for udevkit
 */

#ifndef SYSCLOCK_H
#define SYSCLOCK_H

#include <stdint.h>
#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev)
 #include "sysclock_pic24_dspic33.h"
#elif defined(ARCHI_dspic30f)
 #include "sysclock_dspic30f.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
 #include "sysclock_dspic33c.h"
#elif defined(ARCHI_pic32mx)
 #include "sysclock_pic32mx.h"
#elif defined(ARCHI_pic32mm)
 #include "sysclock_pic32mm.h"
#elif defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) \
 || defined(ARCHI_pic32mk)
 #include "sysclock_pic32mz_mk.h"
#else
 typedef int SYSCLOCK_CLOCK;
 typedef int SYSCLOCK_SOURCE;
 #error Unsuported ARCHI for sysclock driver.
#endif

int sysclock_setClock(uint32_t freq);

// new API
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock);
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t div);

// source clock
int32_t sysclock_sourceFreq(SYSCLOCK_SOURCE source);
int sysclock_setSourceFreq(SYSCLOCK_SOURCE source, uint32_t freq);
SYSCLOCK_SOURCE sysclock_source(void);
int sysclock_switchSourceTo(SYSCLOCK_SOURCE source);

#endif // SYSCLOCK_H
