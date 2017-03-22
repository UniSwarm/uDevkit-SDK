/**
 * @file gpio.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date March 20, 2017, 20:38 AM
 *
 * @brief GPIO support driver
 */

#ifndef GPIO_H
#define GPIO_H

void gpio_setBit(rt_dev_t device);
void gpio_clearBit(rt_dev_t device);
void gpio_invBit(rt_dev_t device);

#define GPIO_LOW           (0x00)
#define GPIO_HIGHT         (0x01)
#define GPIO_TRISTATE      (0x02)
void gpio_writeBit(rt_dev_t device, uint8_t value);
uint8_t gpio_readBit(rt_dev_t device);

#define GPIO_INPUT         (0x01)
#define GPIO_OUTPUT        (0x02)
#define GPIO_OPENDRAIN     (0x04)
int gpio_setBitConfig(rt_dev_t device, uint16_t config);

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
  #include "gpio_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) \
 || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "gpio_pic32.h"
#endif

#define gpio_pin(port, pin) MKDEV(DEV_CLASS_GPIO, (((port)<<GPIO_MAX_PORTWIDTHU) + ((pin) & GPIO_MAX_PORTWIDTHMASK));
#define gpio_port(port)     MKDEV(DEV_CLASS_GPIO, ((port)<<GPIO_MAX_PORTWIDTHU));

#if GPIO_MAX_PORTWIDTH>32
  typedef uint32_t port_type;
#elif GPIO_MAX_PORTWIDTH>16
  typedef uint16_t port_type;
#else
  typedef uint8_t port_type;
#endif

void gpio_writePort(rt_dev_t device, port_type value);
port_type gpio_readPort(rt_dev_t device);
int gpio_setPortConfig(rt_dev_t device, uint16_t config);

#endif // GPIO_H
