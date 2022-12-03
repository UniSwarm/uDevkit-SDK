/**
 * @file qei.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface (QEI) support driver
 */

#ifndef QEI_H
#define QEI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "qei_device.h"

// ====== device assignation ======
#define qei(d) MKDEV(DEV_CLASS_QEI, (d)-1)
rt_dev_t qei_getFreeDevice(void);
int qei_open(rt_dev_t device);
int qei_close(rt_dev_t device);

// ==== device enable/disable =====
int qei_enable(rt_dev_t device);
int qei_disable(rt_dev_t device);

// ======== device settings =======
#define QEI_AB_INV 0x02
#define QEI_FILTER 0x04
#define QEI_I_INV  0x08
#define QEI_I_EN   0x10
#define QEI_X4MODE 0x20
int qei_setConfig(rt_dev_t device, uint16_t config);
int qei_setInputFilterConfig(rt_dev_t device, uint16_t divider);
int qei_setModuloCountMode(rt_dev_t device, int32_t minimum, int32_t maximum);

// ======= device write/read ======
qei_type qei_value(rt_dev_t device);
int qei_setValue(rt_dev_t device, qei_type value);
int qei_setHomeValue(rt_dev_t device, qei_type home);

#ifdef __cplusplus
}
#endif

#endif  // QEI_H
