/**
 * @file device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 7, 2016, 11:47 PM
 *
 * @brief Low level periph assignement handler
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>
#include <stdlib.h>

#if !defined(_SIZE_T_DEFINED) && !defined(__SIZE_TYPE__) && !defined(_SIZE_T) && !defined(_SIZET) && !defined(_BSD_SIZE_T_DEFINED_)
#define _SIZE_T_DEFINED
#define _SIZE_T
#define _SIZET
#define __SIZE_TYPE__
#define _BSD_SIZE_T_DEFINED_
 typedef uint16_t size_t;
#endif

#if !defined(_SSIZE_T_DEFINED) && !defined(_SSIZE_T) && !defined(_SSIZE_T_) && !defined(__have_typedef_ssize_t) \
 && !defined(_SSIZET) && !defined(_BSD_SSIZE_T_DEFINED_) && !defined(__ssize_t_defined) && !defined(_SSIZE_T_DECLARED)
#define _SSIZE_T_DEFINED
#define __ssize_t_defined
#define _SSIZE_T
#define _SSIZE_T_
#define __have_typedef_ssize_t
#define _SSIZET
#define _SSIZE_T_DECLARED
#define _BSD_SSIZE_T_DEFINED_
 typedef int16_t ssize_t;
#endif

// dev_t definition and macro helpers
typedef uint16_t rt_dev_t;
typedef uint8_t rt_dev_t_class;
#define MAJOR(dev)      ((rt_dev_t_class) ((dev) >> 8))
#define MINOR(dev)      ((uint8_t) ((dev) & 0x00FF))
#define MKDEV(ma,mi)    (((ma) << 8) | (mi))
#define NULLDEV         ((rt_dev_t_class) (0))

// ===== device classes =====
#define DEV_CLASS_TIMER         ((rt_dev_t_class) (0x01))
// base communication classes
#define DEV_CLASS_UART          ((rt_dev_t_class) (0x02))
#define DEV_CLASS_UART_SOFT     ((rt_dev_t_class) (DEV_CLASS_UART+1))
#define DEV_CLASS_I2C           ((rt_dev_t_class) (0x04))
#define DEV_CLASS_I2C_SOFT      ((rt_dev_t_class) (DEV_CLASS_I2C+1))
#define DEV_CLASS_SPI           ((rt_dev_t_class) (0x06))
#define DEV_CLASS_SPI_SOFT      ((rt_dev_t_class) (DEV_CLASS_SPI+1))
#define DEV_CLASS_USB_SERIAL    ((rt_dev_t_class) (0x08))

// special classes
#define DEV_CLASS_QEI           ((rt_dev_t_class) (0x11))
#define DEV_CLASS_OC            ((rt_dev_t_class) (0x12))
#define DEV_CLASS_IC            ((rt_dev_t_class) (0x13))
#define DEV_CLASS_PWM           ((rt_dev_t_class) (0x14))
#define DEV_CLASS_MOTOR         ((rt_dev_t_class) (0x15))

// ===== device functions =====
ssize_t device_write(rt_dev_t device, const char *data, size_t size);
ssize_t device_read(rt_dev_t device, char *data, size_t size_max);

#endif // DEVICE_H
