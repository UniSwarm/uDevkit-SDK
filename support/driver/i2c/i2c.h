/**
 * @file i2c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date June 09, 2016, 18:47 PM
 *
 * @brief I2C communication support driver
 */

#ifndef I2C_H
#define I2C_H

#include <driver/device.h>

// ====== device assignation ======
// i2c(d) different switch archi, define in archi specific headers
rt_dev_t i2c_getFreeDevice();
int i2c_open(rt_dev_t device);
int i2c_close(rt_dev_t device);

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
uint8_t i2c_getc(rt_dev_t device);

// ===== high level functions =====
#define I2C_REG8           0x00
#define I2C_REG16          0x01
#define I2C_REGADDR8       0x00
#define I2C_REGADDR16      0x02
#define I2C_READ_RESTART   0x00
#define I2C_READ_STOPSTART 0x04
uint16_t i2c_readreg(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t flags);
ssize_t i2c_readregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags);
int i2c_writereg(rt_dev_t device, uint16_t address, uint16_t reg, uint16_t value, uint8_t flags);
int i2c_writeregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags);

// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) \
 || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33ch) \
 || defined(ARCHI_dspic33ck)
 #include "i2c_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) \
|| defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "i2c_pic32.h"
#else
 #warning Unsuported ARCHI
#endif

#endif // I2C_H
