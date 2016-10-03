/**
 * @file oc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver
 */

#ifndef OC_H
#define OC_H

#include "driver/device.h"

// ====== device assignation ======
rt_dev_t oc_getFreeDevice();
void oc_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int oc_enable(rt_dev_t device);
int oc_disable(rt_dev_t device);

// ======== device settings =======
#define OC_MODE_INVALID    0x00
#define OC_MODE_PWM        0x01
int oc_setMode(rt_dev_t device, uint8_t mode);
uint8_t oc_mode(rt_dev_t device);

int oc_setRVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal);
uint32_t oc_rVal(rt_dev_t device);
uint32_t oc_rsVal(rt_dev_t device);

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "oc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "oc_pic24f_dspic33f_dspic30f.h"
#else
 #error Unsuported ARCHI
#endif

#endif // OC_H
