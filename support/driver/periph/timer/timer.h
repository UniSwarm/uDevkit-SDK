/**
 * @file timer.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 10, 2016, 11:04 PM
 *
 * @brief Timers support for rtprog
 */

#ifndef TIMER_H
#define TIMER_H

uint8_t timer_getFreeDevice();
void timer_releaseDevice(uint8_t device);

int timer_enable(uint8_t device);
int timer_disable(uint8_t device);

// timer mode
int timer_setPeriod(uint8_t device, uint32_t periodMs);
uint32_t timer_periodMs(uint8_t device);

// counter mode
int timer_setCounter(uint8_t device, uint16_t diviser);
uint16_t timer_counter(uint8_t device);

uint16_t timer_getValue16();

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
#include "timer_dspic.h"
#else
#error "Unsupported ARCHI"
#endif

#endif // TIMER_H
