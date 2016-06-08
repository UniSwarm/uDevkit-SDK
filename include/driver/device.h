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

// dev_t definition and macro helpers
typedef uint16_t dev_t;
#define MAJOR(dev)      ((uint8_t) ((dev) >> 8))
#define MINOR(dev)      ((uint8_t) ((dev) & 0x00FF))
#define MKDEV(ma,mi)    (((ma) << 8) | (mi))
#define NULLDEV         (0)

// device classes
#define DEV_CLASS_UART  0x02
#define DEV_CLASS_I2C   0x03
#define DEV_CLASS_SPI   0x04

#define DEV_CLASS_QEI   0x11

#endif // DEVICE_H
