/**
 * @file i2c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 09, 2016, 18:47 PM
 * 
 * @brief I2C communication support driver
 */

#ifndef I2C_H
#define I2C_H

#include "driver/device.h"

// ====== device assignation ======
rt_dev_t i2c_getFreeDevice();
void i2c_releaseDevice(rt_dev_t device);

// ==== device enable/disable =====
int i2c_enable(rt_dev_t device);
int i2c_disable(rt_dev_t device);

// ======== device settings =======
#define I2C_BAUD_100K 100000
#define I2C_BAUD_400K 400000
#define I2C_BAUD_1M 1000000
int i2c_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
uint32_t i2c_baudSpeed(rt_dev_t device);
uint32_t i2c_effectiveBaudSpeed(rt_dev_t device);

int i2c_setAddressWidth(rt_dev_t device, uint8_t addressWidth);
uint8_t i2c_addressWidth(rt_dev_t device);

// ======== device control ========
int i2c_start(rt_dev_t device);
int i2c_restart(rt_dev_t device);
int i2c_stop(rt_dev_t device);
int i2c_idle(rt_dev_t device);
int i2c_ack(rt_dev_t device);
int i2c_nack(rt_dev_t device);

// ======= device write/read ======
int i2c_putc(rt_dev_t device, const char data);
char i2c_getc(rt_dev_t device);
ssize_t i2c_write(rt_dev_t device, const char *data, size_t size);
ssize_t i2c_read(rt_dev_t device, char *data, size_t size_max);

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "i2c_pic24f_dspic33f_dspic30f.h"
#else
 #error Unsuported ARCHI
#endif

#endif // I2C_H
