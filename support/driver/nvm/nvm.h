/**
 * @file nvm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date novembre 10, 2016, 18:01
 *
 * @brief NVM (non volatile memory) support drivers
 */

#ifndef NVM_H
#define NVM_H

#include "driver/device.h"

// ====== device assignation ======
rt_dev_t nvm_getFreeDevice();
void nvm_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int nvm_enable(rt_dev_t device);
int nvm_disable(rt_dev_t device);


#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24fv) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj)
 #include "nvm_pic24_dspic30f_dspic33.h"
#else
 #error Unsuported ARCHI
#endif

#endif // NVM_H
