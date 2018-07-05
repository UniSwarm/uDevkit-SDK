/**
 * @file gpio_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date March 20, 2017, 20:38 AM
 *
 * @brief GPIO support for specific devices
 */

#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) \
 || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
  #include "gpio_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) \
 || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "gpio_pic32.h"
#endif

#ifdef GPIO_HAVE_PORTA
    #define GPIO_PORTA 0
#endif
#ifdef GPIO_HAVE_PORTB
    #define GPIO_PORTB 1
#endif
#ifdef GPIO_HAVE_PORTC
    #define GPIO_PORTC 2
#endif
#ifdef GPIO_HAVE_PORTD
    #define GPIO_PORTD 3
#endif
#ifdef GPIO_HAVE_PORTE
    #define GPIO_PORTE 4
#endif
#ifdef GPIO_HAVE_PORTF
    #define GPIO_PORTF 5
#endif
#ifdef GPIO_HAVE_PORTG
    #define GPIO_PORTG 6
#endif
#ifdef GPIO_HAVE_PORTH
    #define GPIO_PORTH 7
#endif
#ifdef GPIO_HAVE_PORTI
    #define GPIO_PORTI 8
#endif
#ifdef GPIO_HAVE_PORTJ
    #define GPIO_PORTJ 9
#endif
#ifdef GPIO_HAVE_PORTK
    #define GPIO_PORTK 10
#endif

#if GPIO_MAX_PORTWIDTH>32
  typedef uint32_t port_type;
#elif GPIO_MAX_PORTWIDTH>16
  typedef uint16_t port_type;
#else
  typedef uint8_t port_type;
#endif

#endif // GPIO_DEVICE_H
