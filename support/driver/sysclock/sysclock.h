/**
 * @file sysclock.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for udevkit
 */

#ifndef SYSCLOCK_H
#define SYSCLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sysclock_device.h"

int sysclock_setClock(uint32_t freq);

// new API
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock);
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t divisor);

// source clock
int32_t sysclock_sourceFreq(SYSCLOCK_SOURCE source);
int sysclock_setSourceFreq(SYSCLOCK_SOURCE source, uint32_t freq);
SYSCLOCK_SOURCE sysclock_source(void);
int sysclock_switchSourceTo(SYSCLOCK_SOURCE source);

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_H
