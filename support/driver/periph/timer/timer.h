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

#include "driver/device.h"

rt_dev_t timer_getFreeDevice();
void timer_releaseDevice(rt_dev_t device);

int timer_enable(rt_dev_t device);
int timer_disable(rt_dev_t device);

// timer mode
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs);
uint32_t timer_periodMs(rt_dev_t device);

// counter mode
int timer_setCounter(rt_dev_t device, uint16_t diviser);
uint16_t timer_counter(rt_dev_t device);

#define timer_clearValue(device) timer_setValue((device), 0)
int timer_setValue(rt_dev_t device, uint16_t value);
uint16_t timer_getValue(rt_dev_t device);

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
#include "timer_pic24f_dspic33f_dspic30f.h"
#else
#error "Unsupported ARCHI"
#endif

#endif // TIMER_H
