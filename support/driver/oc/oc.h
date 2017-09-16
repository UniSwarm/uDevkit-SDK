/**
 * @file oc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver
 */

#ifndef OC_H
#define OC_H

#include <driver/device.h>

// ======== device assignation ========
#define oc(d) MKDEV(DEV_CLASS_OC, (d)-1)
rt_dev_t oc_getFreeDevice();
int oc_open(rt_dev_t device);
int oc_close(rt_dev_t device);

// ====== device enable/disable =======
int oc_enable(rt_dev_t device);
int oc_disable(rt_dev_t device);

// ========== device settings =========
#define OC_MODE_INVALID           0x00 ///< OC Off
#define OC_MODE_PWM               0x01 ///< OC in PWM mode, edge aligned
#define OC_MODE_PWM_CENTER        0x02 ///< OC in PWM mode, center aligned

#define OC_MODE_SINGLE_LOW        0x10 ///< OC force output pin low on R value match event
#define OC_MODE_SINGLE_HIGH       0x11 ///< OC force output pin high on R value match event
#define OC_MODE_CONTINOUS_TOGGLE  0x12 ///< OC toggle output pin on R value match event

#define OC_MODE_SINGLE_LOWHIGH    0x20 ///< OC force output pin high on R match and force to low on RS (one time)
#define OC_MODE_CONTINOUS_LOWHIGH 0x21 ///< Same as OC_MODE_SINGLE_LOWHIGH but infinite

int oc_setMode(rt_dev_t device, uint8_t mode);
uint8_t oc_mode(rt_dev_t device);

int oc_setRVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal);
uint32_t oc_rVal(rt_dev_t device);
uint32_t oc_rsVal(rt_dev_t device);

// ========= specific includes ========
#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "oc_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) \
   || defined(ARCHI_dspic33fj)
 #include "oc_pic24f_dspic30f_dspic33f.h"
#elif defined(ARCHI_pic24fj)
 #if defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102) || defined(DEVICE_24FJ32MC101) \
  || defined(DEVICE_24FJ32MC102) || defined(DEVICE_24FJ32MC104)
  #include "oc_pic24f_dspic30f_dspic33f.h"
 #else
  #include "oc_pic24e_dspic33e.h"
 #endif
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) \
   || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "oc_pic32.h"
#else
 #warning Unsuported ARCHI
#endif

#endif // OC_H
