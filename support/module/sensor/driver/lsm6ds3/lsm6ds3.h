/**
 * @file lsm6ds3.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 13, 2017, 14:37 PM
 *
 * @brief LSM6DS3 3D accelerometer and 3D gyroscope sensor driver support
 */

#ifndef LSM6DS3_H
#define LSM6DS3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/device.h"

rt_dev_t lsm6ds3_init(rt_dev_t i2c_bus, uint8_t i2c_addr);
int lsm6ds3_getAccel(rt_dev_t i2c_bus, uint8_t i2c_addr, uint16_t acc[]);
int lsm6ds3_getGyro(rt_dev_t i2c_bus, uint8_t i2c_addr, uint16_t gyro[]);

// sensor registers
#define LSM6DS3_DEFAULT_ADDRESS 0xD6
//#define LSM6DS3_DEVICE_ID           0x69

#ifdef __cplusplus
}
#endif

#endif  // LSM6DS3_H
