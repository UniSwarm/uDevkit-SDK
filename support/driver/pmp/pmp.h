/**
 * @file pmp.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date August 1, 2025, 05:01 PM
 * 
 * @brief Parallel Master Port (PMP) support driver
 */

#ifndef PMP_H
#define PMP_H

#include "pmp_device.h"

// ====== bus assignation ======
#define pmp(d) MKDEV(DEV_CLASS_CAN, (d)-1)
rt_dev_t pmp_getFreeDevice(void);
int pmp_open(rt_dev_t device);
int pmp_close(rt_dev_t device);
bool pmp_isOpened(rt_dev_t device);

// ==== bus enable/disable =====
int pmp_enable(rt_dev_t device);
int pmp_disable(rt_dev_t device);
bool pmp_isEnabled(rt_dev_t device);

#ifdef SIMULATOR
#    include "pmp_sim.h"
#endif

#ifdef __cplusplus
}
#endif

#endif // PMP_H
