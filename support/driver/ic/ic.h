/**
 * @file ic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Input Compare support driver
 */

#ifndef IC_H
#define IC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ic_device.h"

// ====== device assignation ======
#define ic(d) MKDEV(DEV_CLASS_IC, (d)-1)
rt_dev_t ic_getFreeDevice(void);
int ic_open(rt_dev_t device);
int ic_close(rt_dev_t device);

// ==== device enable/disable =====
int ic_enable(rt_dev_t device);
int ic_disable(rt_dev_t device);

// ======== device settings =======
int ic_setMode(rt_dev_t device, uint8_t mode);
uint8_t ic_mode(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // IC_H
