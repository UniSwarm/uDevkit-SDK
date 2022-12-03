/**
 * @file ccp.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2022
 *
 * @date May 08, 2019, 09:40 AM
 *
 * @brief CCPs support for udevkit
 */

#ifndef CCP_H
#define CCP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ccp_device.h"

// ====== device assignation ======
#define ccp(d) MKDEV(DEV_CLASS_CCP, ((d)-1))
rt_dev_t ccp_getFreeDevice(void);
int ccp_open(rt_dev_t device);
int ccp_close(rt_dev_t device);

// ==== device enable/disable =====
int ccp_enable(rt_dev_t device);
int ccp_disable(rt_dev_t device);

int ccp_setHandler(rt_dev_t device, void (*handler)(void));

typedef enum
{
    CCP_MODE_TIMER = 0x0,  ///< CCP in timer mode
    CCP_MODE_PWM = 0x1,    ///< CCP in PWM mode
    CCP_MODE_PWMC = 0x2,   ///< CCP in center PWM mode
    CCP_MODE_OCH = 0x3,    ///< CCP in output compare mode, output high
    CCP_MODE_OCL = 0x4,    ///< CCP in output compare mode, output low
    CCP_MODE_OCT = 0x5,    ///< CCP in output compare mode, output toggle
} CCP_MODE;
int ccp_setMode(rt_dev_t device, CCP_MODE mode);

int ccp_setCompare(rt_dev_t device, uint16_t cmpA, uint16_t cmpB);

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

#ifdef __cplusplus
}
#endif

#endif  // CCP_H
