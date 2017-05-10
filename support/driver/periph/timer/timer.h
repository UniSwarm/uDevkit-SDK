/**
 * @file timer.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 10, 2016, 11:04 PM
 *
 * @brief Timers support for rtprog
 */

#ifndef TIMER_H
#define TIMER_H

#include <driver/device.h>

// ====== device assignation ======
#define timer(d) MKDEV(DEV_CLASS_TIMER, (d-1))
rt_dev_t timer_getFreeDevice();
int timer_open(rt_dev_t device);
int timer_close(rt_dev_t device);

// ==== device enable/disable =====
int timer_enable(rt_dev_t device);
int timer_disable(rt_dev_t device);

int timer_setHandler(rt_dev_t device, void (*handler)(void));

// ========= timer mode ===========
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs);
uint32_t timer_periodMs(rt_dev_t device);
int timer_setPeriodUs(rt_dev_t device, uint32_t periodUs);
uint32_t timer_periodUs(rt_dev_t device);
int timer_setPeriod(rt_dev_t device, uint32_t period);
uint32_t timer_period(rt_dev_t device);

// ======== counter mode ==========
int timer_setCounter(rt_dev_t device, uint16_t diviser);

#define timer_clearValue(device) timer_setValue((device), 0)
int timer_setValue(rt_dev_t device, uint16_t value);
uint16_t timer_getValue(rt_dev_t device);

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "timer_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) \
   || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
 #include "timer_pic32.h"
#else
#error "Unsupported ARCHI"
#endif

#endif // TIMER_H
