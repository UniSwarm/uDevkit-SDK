/**
 * @file biss.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 02:39 PM
 *
 * @brief BISS support for udevkit
 */

#ifndef BISS_H
#define BISS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "biss_device.h"

// ====== device assignation ======
#define biss(d) MKDEV(DEV_CLASS_BISS, ((d) - 1))
rt_dev_t biss_getFreeDevice(void);
int biss_open(rt_dev_t device);
int biss_close(rt_dev_t device);
bool biss_isOpened(rt_dev_t device);

// ==== device enable/disable =====
int biss_enable(rt_dev_t device);
int biss_disable(rt_dev_t device);
bool biss_isEnabled(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // BISS_H
