/**
 * @file gpio.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 20, 2017, 20:38 AM
 *
 * @brief GPIO support driver
 */

#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_device.h"

// Bit interface
#define gpio_pin(port, pin) MKDEV(DEV_CLASS_GPIO, (((port) << GPIO_MAX_PORTWIDTHU) + ((pin)&GPIO_MAX_PORTWIDTHMASK)))
void gpio_setBit(rt_dev_t device);
void gpio_clearBit(rt_dev_t device);
void gpio_toggleBit(rt_dev_t device);

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH,
    GPIO_TOGGLE
} GPIO_VALUE;
void gpio_writeBit(rt_dev_t device, GPIO_VALUE value);
GPIO_VALUE gpio_readBit(rt_dev_t device);

typedef enum
{
    GPIO_INPUT = 0x00,
    GPIO_OUTPUT = 0x01,
    GPIO_OPENDRAIN = 0x02,
    GPIO_PULLUP = 0x04,
    GPIO_PULLDOWN = 0x08,
    GPIO_CNPOSITIVE = 0x10,
    GPIO_CNNEGATIVE = 0x20
} GPIO_CONFIG;
int gpio_setBitConfig(rt_dev_t device, uint16_t config);

// Port interface
#define gpio_port(port) MKDEV(DEV_CLASS_GPIO, ((port) << GPIO_MAX_PORTWIDTHU))
void gpio_writePort(rt_dev_t device, port_type value);
port_type gpio_readPort(rt_dev_t device);
int gpio_setPortConfig(rt_dev_t device, uint16_t config);

// Port callback handler
int gpio_setChangeHandler(rt_dev_t device, void (*handler)(GPIO_VALUE));

#ifdef __cplusplus
}
#endif

#endif  // GPIO_H
