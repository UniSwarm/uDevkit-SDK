/**
 * @file ic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Input Compare support driver
 */

#ifndef IC_H
#define IC_H

#include <driver/device.h>

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

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "ic_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) \
 || defined(ARCHI_dspic33fj)
#elif defined(ARCHI_pic24fj)
 #if defined(DEVICE_24FJ16MC101) || defined(DEVICE_24FJ16MC102) || defined(DEVICE_24FJ32MC101) \
  || defined(DEVICE_24FJ32MC102) || defined(DEVICE_24FJ32MC104)
  #include "ic_pic24f_dspic30f_dspic33f.h"
 #else
  #include "ic_pic24e_dspic33e.h"
 #endif
 #include "ic_pic24f_dspic30f_dspic33f.h"
#elif defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) \
   || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "ic_pic32.h"
#else
 #warning Unsuported ARCHI
#endif

#endif // IC_H
