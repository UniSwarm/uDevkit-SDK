/**
 * @file timer.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date April 10, 2016, 11:04 PM
 *
 * @brief Timers support for udevkit
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "timer_device.h"

// ====== device assignation ======
#define timer(d) MKDEV(DEV_CLASS_TIMER, ((d)-1))
rt_dev_t timer_getFreeDevice(void);
int timer_open(rt_dev_t device);
int timer_close(rt_dev_t device);
bool timer_isOpened(rt_dev_t device);

// ==== device enable/disable =====
int timer_enable(rt_dev_t device);
int timer_disable(rt_dev_t device);
bool timer_isEnabled(rt_dev_t device);

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
uint16_t timer_value(rt_dev_t device);

// ======= dynamic clock =======
void timer_reconfig(void);

#ifdef __cplusplus
}
#endif

#endif  // TIMER_H
