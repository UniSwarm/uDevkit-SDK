/**
 * @file qei.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver
 */

#ifndef QEI_H
#define QEI_H

#include "driver/device.h"

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "qei_pic24f_dspic30f_dspic33f.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "qei_pic24e_dspic33e.h"
#else
 #warning Unsuported ARCHI
#endif

// ====== device assignation ======
rt_dev_t qei_getFreeDevice();
void qei_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int qei_enable(rt_dev_t device);
int qei_disable(rt_dev_t device);

// ======== device settings =======
int qei_setConfig(rt_dev_t device, uint16_t config);

// ======= device write/read ======
#ifdef QEI_32B
uint32_t qei_getValue(rt_dev_t device);
int qei_setHomeValue(rt_dev_t device, uint32_t config);
#else
uint16_t qei_getValue(rt_dev_t device);
int qei_setHomeValue(rt_dev_t device, uint16_t config);
#endif

#endif // QEI_H
