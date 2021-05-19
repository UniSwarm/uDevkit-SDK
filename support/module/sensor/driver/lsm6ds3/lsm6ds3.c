/**
 * @file lsm6ds3.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date October 13, 2017, 14:37 PM
 *
 * @brief LSM6DS3 3D accelerometer and 3D gyroscope sensor driver support
 */

#include "lsm6ds3.h"
#include "lsm6ds3_registers.h"

#include "driver/i2c.h"

rt_dev_t lsm6ds3_init(rt_dev_t i2c_bus, uint8_t i2c_addr)
{
    i2c_writereg(
        i2c_bus, i2c_addr, LSM6DS3_CTRL1_XL, 0b00100000, 0);  // accel enable in low power mode 26Hz, 2G, 400Hz filter
    i2c_writereg(i2c_bus, i2c_addr, LSM6DS3_CTRL2_G, 0b00100000, 0);  // gyro  enable in low power mode 26Hz, 245 dps

    return 0;  // TODO
}

int lsm6ds3_getAccel(rt_dev_t i2c_bus, uint8_t i2c_addr, uint16_t acc[])
{
    i2c_readregs(i2c_bus, i2c_addr, LSM6DS3_OUTX_L_XL, (uint8_t *)acc, 6, 0);

    return 0;
}

int lsm6ds3_getGyro(rt_dev_t i2c_bus, uint8_t i2c_addr, uint16_t gyro[])
{
    i2c_readregs(i2c_bus, i2c_addr, LSM6DS3_OUTX_L_G, (uint8_t *)gyro, 6, 0);

    return 0;
}
