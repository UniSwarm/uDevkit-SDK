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

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
#include "qei_dspic.h"
#else
#error Unsuported ARCHI
#endif

rt_dev_t qei_getFreeDevice();
void qei_releaseDevice(rt_dev_t device);

int qei_enable(rt_dev_t device);
int qei_disable(rt_dev_t device);

int qei_setConfig(rt_dev_t device, uint16_t config);

#ifdef QEI_32B
uint32_t qei_getValue(rt_dev_t device);
int qei_setHomeValue(rt_dev_t device, uint32_t config);
#else
uint16_t qei_getValue(rt_dev_t device);
int qei_setHomeValue(rt_dev_t device, uint16_t config);
#endif

#endif // QEI_H
