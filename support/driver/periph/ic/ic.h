/**
 * @file ic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 18, 2016, 15:40 PM 
 * 
 * @brief Input Compare support driver
 */

#ifndef IC_H
#define IC_H

#include "driver/device.h"

// ====== device assignation ======
rt_dev_t ic_getFreeDevice();
void ic_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int ic_enable(rt_dev_t device);
int ic_disable(rt_dev_t device);

// ======== device settings =======
#define IC_MODE_INVALID    0x00
#define IC_MODE_PWM        0x01
int ic_setMode(rt_dev_t device, uint8_t mode);
uint8_t ic_mode(rt_dev_t device);

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "ic_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "ic_pic24f_dspic33f_dspic30f.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
 #include "ic_pic32.h"
#else
 #error Unsuported ARCHI
#endif

#endif // IC_H
