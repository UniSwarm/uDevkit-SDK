/**
 * @file qei.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver
 */

#ifndef QEI_H
#define QEI_H

#include <driver/device.h>

// ======= specific include =======
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)
 #include "qei_pic24f_dspic33f.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "qei_pic24e_dspic33e.h"
#elif defined(ARCHI_dspic30f)
 #include "qei_dspic30f.h"
#elif defined(ARCHI_pic32mk)
 #include "qei_pic32mk.h"
#else
 #warning Unsuported ARCHI
#endif

#ifdef QEI_32B
  typedef uint32_t qei_type;
#else
  typedef uint16_t qei_type;
#endif

// ====== device assignation ======
#define qei(d) MKDEV(DEV_CLASS_QEI, (d)-1)
rt_dev_t qei_getFreeDevice();
int qei_open(rt_dev_t device);
int qei_close(rt_dev_t device);

// ==== device enable/disable =====
int qei_enable(rt_dev_t device);
int qei_disable(rt_dev_t device);

// ======== device settings =======
#define QEI_AB_INV   0x02
#define QEI_FILTER   0x04
#define QEI_I_INV    0x08
#define QEI_I_EN     0x10
#define QEI_X4MODE   0x20
int qei_setConfig(rt_dev_t device, uint16_t config);

// ======= device write/read ======
qei_type qei_getValue(rt_dev_t device);
int qei_setHomeValue(rt_dev_t device, qei_type home);

#endif // QEI_H
