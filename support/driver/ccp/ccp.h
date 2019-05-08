/**
 * @file ccp.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019
 *
 * @date May 08, 2019, 09:40 AM
 *
 * @brief CCPs support for udevkit
 */

#ifndef CCP_H
#define CCP_H

#include <driver/device.h>

// ====== device assignation ======
#define ccp(d) MKDEV(DEV_CLASS_CCP, (d-1))
rt_dev_t ccp_getFreeDevice();
int ccp_open(rt_dev_t device);
int ccp_close(rt_dev_t device);

// ==== device enable/disable =====
int ccp_enable(rt_dev_t device);
int ccp_disable(rt_dev_t device);

int ccp_setHandler(rt_dev_t device, void (*handler)(void));

// ========= timer mode ===========
int ccp_setPeriodMs(rt_dev_t device, uint32_t periodMs);
uint32_t ccp_periodMs(rt_dev_t device);
int ccp_setPeriodUs(rt_dev_t device, uint32_t periodUs);
uint32_t ccp_periodUs(rt_dev_t device);
int ccp_setPeriod(rt_dev_t device, uint32_t period);
uint32_t ccp_period(rt_dev_t device);

#define ccp_clearValue(device) ccp_setValue((device), 0)
int ccp_setValue(rt_dev_t device, uint32_t value);
uint32_t ccp_getValue(rt_dev_t device);

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_dspic33ch) \
   || defined(ARCHI_dspic33ck)
 #include "ccp_pic24_dspic33.h"
#elif defined(ARCHI_pic32mm)
 #include "ccp_pic32.h"
#else
 #warning "Unsupported ARCHI"
#endif

#endif // CCP_H
