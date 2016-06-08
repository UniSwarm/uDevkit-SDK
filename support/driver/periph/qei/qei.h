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

dev_t qei_getFreeDevice();
void qei_releaseDevice(dev_t device);

int qei_enable(dev_t device);
int qei_disable(dev_t device);

int qei_setConfig(dev_t device, uint16_t config);

#ifdef QEI_32B
uint32_t qei_getValue(dev_t device);
int qei_setHomeValue(dev_t device, uint32_t config);
#else
uint16_t qei_getValue(dev_t device);
int qei_setHomeValue(dev_t device, uint16_t config);
#endif

#endif // QEI_H
