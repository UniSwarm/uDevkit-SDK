/**
 * @file oc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver
 */

#ifndef OC_H
#define OC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "oc_device.h"

// ======== device assignation ========
#define oc(d) MKDEV(DEV_CLASS_OC, (d)-1)
rt_dev_t oc_getFreeDevice(void);
int oc_open(rt_dev_t device);
int oc_close(rt_dev_t device);
bool oc_isOpened(rt_dev_t device);

// ====== device enable/disable =======
int oc_enable(rt_dev_t device);
int oc_disable(rt_dev_t device);
bool oc_isEnabled(rt_dev_t device);

// ========== device settings =========
#define OC_MODE_INVALID    0x00  ///< OC Off
#define OC_MODE_PWM        0x01  ///< OC in PWM mode, edge aligned
#define OC_MODE_PWM_CENTER 0x02  ///< OC in PWM mode, center aligned

#define OC_MODE_SINGLE_LOW       0x10  ///< OC force output pin low on R value match event
#define OC_MODE_SINGLE_HIGH      0x11  ///< OC force output pin high on R value match event
#define OC_MODE_CONTINOUS_TOGGLE 0x12  ///< OC toggle output pin on R value match event

#define OC_MODE_SINGLE_LOWHIGH    0x20  ///< OC force output pin high on R match and force to low on RS (one time)
#define OC_MODE_CONTINOUS_LOWHIGH 0x21  ///< Same as OC_MODE_SINGLE_LOWHIGH but infinite

int oc_setMode(rt_dev_t device, uint8_t mode);
uint8_t oc_mode(rt_dev_t device);

int oc_setRVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal);
uint32_t oc_rVal(rt_dev_t device);
uint32_t oc_rsVal(rt_dev_t device);

#ifdef __cplusplus
}
#endif

#endif  // OC_H
