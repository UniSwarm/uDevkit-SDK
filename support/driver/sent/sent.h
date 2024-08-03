/**
 * @file sent.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 03:36 PM
 *
 * @brief SENT support for udevkit
 */

#ifndef SENT_H
#define SENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sent_device.h"

// ====== device assignation ======
#define sent(d) MKDEV(DEV_CLASS_SENT, ((d) - 1))
rt_dev_t sent_getFreeDevice(void);
int sent_open(rt_dev_t device);
int sent_close(rt_dev_t device);
bool sent_isOpened(rt_dev_t device);

// ==== device enable/disable =====
int sent_enable(rt_dev_t device);
int sent_disable(rt_dev_t device);
bool sent_isEnabled(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // SENT_H
