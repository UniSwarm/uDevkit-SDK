/**
 * @file gpio_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date March 20, 2017, 20:38 AM
 *
 * @brief GPIO support for specific devices
 */

#ifndef GPIO_DEVICE_H
#define GPIO_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "gpio_pic24_dspic30f_dspic33.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)                       \
    || defined(ARCHI_pic32mzda)
#    include "gpio_pic32.h"
#endif

#ifdef GPIO_HAVE_PORTA
#    define GPIO_PORTA 0
#    define GPIO_PA00  (gpio_pin(GPIO_PORTA, 0))
#    define GPIO_PA01  (gpio_pin(GPIO_PORTA, 1))
#    define GPIO_PA02  (gpio_pin(GPIO_PORTA, 2))
#    define GPIO_PA03  (gpio_pin(GPIO_PORTA, 3))
#    define GPIO_PA04  (gpio_pin(GPIO_PORTA, 4))
#    define GPIO_PA05  (gpio_pin(GPIO_PORTA, 5))
#    define GPIO_PA06  (gpio_pin(GPIO_PORTA, 6))
#    define GPIO_PA07  (gpio_pin(GPIO_PORTA, 7))
#    define GPIO_PA08  (gpio_pin(GPIO_PORTA, 8))
#    define GPIO_PA09  (gpio_pin(GPIO_PORTA, 9))
#    define GPIO_PA10  (gpio_pin(GPIO_PORTA, 10))
#    define GPIO_PA11  (gpio_pin(GPIO_PORTA, 11))
#    define GPIO_PA12  (gpio_pin(GPIO_PORTA, 12))
#    define GPIO_PA13  (gpio_pin(GPIO_PORTA, 13))
#    define GPIO_PA14  (gpio_pin(GPIO_PORTA, 14))
#    define GPIO_PA15  (gpio_pin(GPIO_PORTA, 15))
#endif
#ifdef GPIO_HAVE_PORTB
#    define GPIO_PORTB 1
#    define GPIO_PB00  (gpio_pin(GPIO_PORTB, 0))
#    define GPIO_PB01  (gpio_pin(GPIO_PORTB, 1))
#    define GPIO_PB02  (gpio_pin(GPIO_PORTB, 2))
#    define GPIO_PB03  (gpio_pin(GPIO_PORTB, 3))
#    define GPIO_PB04  (gpio_pin(GPIO_PORTB, 4))
#    define GPIO_PB05  (gpio_pin(GPIO_PORTB, 5))
#    define GPIO_PB06  (gpio_pin(GPIO_PORTB, 6))
#    define GPIO_PB07  (gpio_pin(GPIO_PORTB, 7))
#    define GPIO_PB08  (gpio_pin(GPIO_PORTB, 8))
#    define GPIO_PB09  (gpio_pin(GPIO_PORTB, 9))
#    define GPIO_PB10  (gpio_pin(GPIO_PORTB, 10))
#    define GPIO_PB11  (gpio_pin(GPIO_PORTB, 11))
#    define GPIO_PB12  (gpio_pin(GPIO_PORTB, 12))
#    define GPIO_PB13  (gpio_pin(GPIO_PORTB, 13))
#    define GPIO_PB14  (gpio_pin(GPIO_PORTB, 14))
#    define GPIO_PB15  (gpio_pin(GPIO_PORTB, 15))
#endif
#ifdef GPIO_HAVE_PORTC
#    define GPIO_PORTC 2
#    define GPIO_PC00  (gpio_pin(GPIO_PORTC, 0))
#    define GPIO_PC01  (gpio_pin(GPIO_PORTC, 1))
#    define GPIO_PC02  (gpio_pin(GPIO_PORTC, 2))
#    define GPIO_PC03  (gpio_pin(GPIO_PORTC, 3))
#    define GPIO_PC04  (gpio_pin(GPIO_PORTC, 4))
#    define GPIO_PC05  (gpio_pin(GPIO_PORTC, 5))
#    define GPIO_PC06  (gpio_pin(GPIO_PORTC, 6))
#    define GPIO_PC07  (gpio_pin(GPIO_PORTC, 7))
#    define GPIO_PC08  (gpio_pin(GPIO_PORTC, 8))
#    define GPIO_PC09  (gpio_pin(GPIO_PORTC, 9))
#    define GPIO_PC10  (gpio_pin(GPIO_PORTC, 10))
#    define GPIO_PC11  (gpio_pin(GPIO_PORTC, 11))
#    define GPIO_PC12  (gpio_pin(GPIO_PORTC, 12))
#    define GPIO_PC13  (gpio_pin(GPIO_PORTC, 13))
#    define GPIO_PC14  (gpio_pin(GPIO_PORTC, 14))
#    define GPIO_PC15  (gpio_pin(GPIO_PORTC, 15))
#endif
#ifdef GPIO_HAVE_PORTD
#    define GPIO_PORTD 3
#    define GPIO_PD00  (gpio_pin(GPIO_PORTD, 0))
#    define GPIO_PD01  (gpio_pin(GPIO_PORTD, 1))
#    define GPIO_PD02  (gpio_pin(GPIO_PORTD, 2))
#    define GPIO_PD03  (gpio_pin(GPIO_PORTD, 3))
#    define GPIO_PD04  (gpio_pin(GPIO_PORTD, 4))
#    define GPIO_PD05  (gpio_pin(GPIO_PORTD, 5))
#    define GPIO_PD06  (gpio_pin(GPIO_PORTD, 6))
#    define GPIO_PD07  (gpio_pin(GPIO_PORTD, 7))
#    define GPIO_PD08  (gpio_pin(GPIO_PORTD, 8))
#    define GPIO_PD09  (gpio_pin(GPIO_PORTD, 9))
#    define GPIO_PD10  (gpio_pin(GPIO_PORTD, 10))
#    define GPIO_PD11  (gpio_pin(GPIO_PORTD, 11))
#    define GPIO_PD12  (gpio_pin(GPIO_PORTD, 12))
#    define GPIO_PD13  (gpio_pin(GPIO_PORTD, 13))
#    define GPIO_PD14  (gpio_pin(GPIO_PORTD, 14))
#    define GPIO_PD15  (gpio_pin(GPIO_PORTD, 15))
#endif
#ifdef GPIO_HAVE_PORTE
#    define GPIO_PORTE 4
#    define GPIO_PE00  (gpio_pin(GPIO_PORTE, 0))
#    define GPIO_PE01  (gpio_pin(GPIO_PORTE, 1))
#    define GPIO_PE02  (gpio_pin(GPIO_PORTE, 2))
#    define GPIO_PE03  (gpio_pin(GPIO_PORTE, 3))
#    define GPIO_PE04  (gpio_pin(GPIO_PORTE, 4))
#    define GPIO_PE05  (gpio_pin(GPIO_PORTE, 5))
#    define GPIO_PE06  (gpio_pin(GPIO_PORTE, 6))
#    define GPIO_PE07  (gpio_pin(GPIO_PORTE, 7))
#    define GPIO_PE08  (gpio_pin(GPIO_PORTE, 8))
#    define GPIO_PE09  (gpio_pin(GPIO_PORTE, 9))
#    define GPIO_PE10  (gpio_pin(GPIO_PORTE, 10))
#    define GPIO_PE11  (gpio_pin(GPIO_PORTE, 11))
#    define GPIO_PE12  (gpio_pin(GPIO_PORTE, 12))
#    define GPIO_PE13  (gpio_pin(GPIO_PORTE, 13))
#    define GPIO_PE14  (gpio_pin(GPIO_PORTE, 14))
#    define GPIO_PE15  (gpio_pin(GPIO_PORTE, 15))
#endif
#ifdef GPIO_HAVE_PORTF
#    define GPIO_PORTF 5
#    define GPIO_PF00  (gpio_pin(GPIO_PORTF, 0))
#    define GPIO_PF01  (gpio_pin(GPIO_PORTF, 1))
#    define GPIO_PF02  (gpio_pin(GPIO_PORTF, 2))
#    define GPIO_PF03  (gpio_pin(GPIO_PORTF, 3))
#    define GPIO_PF04  (gpio_pin(GPIO_PORTF, 4))
#    define GPIO_PF05  (gpio_pin(GPIO_PORTF, 5))
#    define GPIO_PF06  (gpio_pin(GPIO_PORTF, 6))
#    define GPIO_PF07  (gpio_pin(GPIO_PORTF, 7))
#    define GPIO_PF08  (gpio_pin(GPIO_PORTF, 8))
#    define GPIO_PF09  (gpio_pin(GPIO_PORTF, 9))
#    define GPIO_PF10  (gpio_pin(GPIO_PORTF, 10))
#    define GPIO_PF11  (gpio_pin(GPIO_PORTF, 11))
#    define GPIO_PF12  (gpio_pin(GPIO_PORTF, 12))
#    define GPIO_PF13  (gpio_pin(GPIO_PORTF, 13))
#    define GPIO_PF14  (gpio_pin(GPIO_PORTF, 14))
#    define GPIO_PF15  (gpio_pin(GPIO_PORTF, 15))
#endif
#ifdef GPIO_HAVE_PORTG
#    define GPIO_PORTG 6
#    define GPIO_PG00  (gpio_pin(GPIO_PORTG, 0))
#    define GPIO_PG01  (gpio_pin(GPIO_PORTG, 1))
#    define GPIO_PG02  (gpio_pin(GPIO_PORTG, 2))
#    define GPIO_PG03  (gpio_pin(GPIO_PORTG, 3))
#    define GPIO_PG04  (gpio_pin(GPIO_PORTG, 4))
#    define GPIO_PG05  (gpio_pin(GPIO_PORTG, 5))
#    define GPIO_PG06  (gpio_pin(GPIO_PORTG, 6))
#    define GPIO_PG07  (gpio_pin(GPIO_PORTG, 7))
#    define GPIO_PG08  (gpio_pin(GPIO_PORTG, 8))
#    define GPIO_PG09  (gpio_pin(GPIO_PORTG, 9))
#    define GPIO_PG10  (gpio_pin(GPIO_PORTG, 10))
#    define GPIO_PG11  (gpio_pin(GPIO_PORTG, 11))
#    define GPIO_PG12  (gpio_pin(GPIO_PORTG, 12))
#    define GPIO_PG13  (gpio_pin(GPIO_PORTG, 13))
#    define GPIO_PG14  (gpio_pin(GPIO_PORTG, 14))
#    define GPIO_PG15  (gpio_pin(GPIO_PORTG, 15))
#endif
#ifdef GPIO_HAVE_PORTH
#    define GPIO_PORTH 7
#    define GPIO_PH00  (gpio_pin(GPIO_PORTH, 0))
#    define GPIO_PH01  (gpio_pin(GPIO_PORTH, 1))
#    define GPIO_PH02  (gpio_pin(GPIO_PORTH, 2))
#    define GPIO_PH03  (gpio_pin(GPIO_PORTH, 3))
#    define GPIO_PH04  (gpio_pin(GPIO_PORTH, 4))
#    define GPIO_PH05  (gpio_pin(GPIO_PORTH, 5))
#    define GPIO_PH06  (gpio_pin(GPIO_PORTH, 6))
#    define GPIO_PH07  (gpio_pin(GPIO_PORTH, 7))
#    define GPIO_PH08  (gpio_pin(GPIO_PORTH, 8))
#    define GPIO_PH09  (gpio_pin(GPIO_PORTH, 9))
#    define GPIO_PH10  (gpio_pin(GPIO_PORTH, 10))
#    define GPIO_PH11  (gpio_pin(GPIO_PORTH, 11))
#    define GPIO_PH12  (gpio_pin(GPIO_PORTH, 12))
#    define GPIO_PH13  (gpio_pin(GPIO_PORTH, 13))
#    define GPIO_PH14  (gpio_pin(GPIO_PORTH, 14))
#    define GPIO_PH15  (gpio_pin(GPIO_PORTH, 15))
#endif
#ifdef GPIO_HAVE_PORTI
#    define GPIO_PORTI 8
#    define GPIO_PI00  (gpio_pin(GPIO_PORTI, 0))
#    define GPIO_PI01  (gpio_pin(GPIO_PORTI, 1))
#    define GPIO_PI02  (gpio_pin(GPIO_PORTI, 2))
#    define GPIO_PI03  (gpio_pin(GPIO_PORTI, 3))
#    define GPIO_PI04  (gpio_pin(GPIO_PORTI, 4))
#    define GPIO_PI05  (gpio_pin(GPIO_PORTI, 5))
#    define GPIO_PI06  (gpio_pin(GPIO_PORTI, 6))
#    define GPIO_PI07  (gpio_pin(GPIO_PORTI, 7))
#    define GPIO_PI08  (gpio_pin(GPIO_PORTI, 8))
#    define GPIO_PI09  (gpio_pin(GPIO_PORTI, 9))
#    define GPIO_PI10  (gpio_pin(GPIO_PORTI, 10))
#    define GPIO_PI11  (gpio_pin(GPIO_PORTI, 11))
#    define GPIO_PI12  (gpio_pin(GPIO_PORTI, 12))
#    define GPIO_PI13  (gpio_pin(GPIO_PORTI, 13))
#    define GPIO_PI14  (gpio_pin(GPIO_PORTI, 14))
#    define GPIO_PI15  (gpio_pin(GPIO_PORTI, 15))
#endif
#ifdef GPIO_HAVE_PORTJ
#    define GPIO_PORTJ 9
#    define GPIO_PJ00  (gpio_pin(GPIO_PORTJ, 0))
#    define GPIO_PJ01  (gpio_pin(GPIO_PORTJ, 1))
#    define GPIO_PJ02  (gpio_pin(GPIO_PORTJ, 2))
#    define GPIO_PJ03  (gpio_pin(GPIO_PORTJ, 3))
#    define GPIO_PJ04  (gpio_pin(GPIO_PORTJ, 4))
#    define GPIO_PJ05  (gpio_pin(GPIO_PORTJ, 5))
#    define GPIO_PJ06  (gpio_pin(GPIO_PORTJ, 6))
#    define GPIO_PJ07  (gpio_pin(GPIO_PORTJ, 7))
#    define GPIO_PJ08  (gpio_pin(GPIO_PORTJ, 8))
#    define GPIO_PJ09  (gpio_pin(GPIO_PORTJ, 9))
#    define GPIO_PJ10  (gpio_pin(GPIO_PORTJ, 10))
#    define GPIO_PJ11  (gpio_pin(GPIO_PORTJ, 11))
#    define GPIO_PJ12  (gpio_pin(GPIO_PORTJ, 12))
#    define GPIO_PJ13  (gpio_pin(GPIO_PORTJ, 13))
#    define GPIO_PJ14  (gpio_pin(GPIO_PORTJ, 14))
#    define GPIO_PJ15  (gpio_pin(GPIO_PORTJ, 15))
#endif
#ifdef GPIO_HAVE_PORTK
#    define GPIO_PORTK 10
#    define GPIO_PK00  (gpio_pin(GPIO_PORTK, 0))
#    define GPIO_PK01  (gpio_pin(GPIO_PORTK, 1))
#    define GPIO_PK02  (gpio_pin(GPIO_PORTK, 2))
#    define GPIO_PK03  (gpio_pin(GPIO_PORTK, 3))
#    define GPIO_PK04  (gpio_pin(GPIO_PORTK, 4))
#    define GPIO_PK05  (gpio_pin(GPIO_PORTK, 5))
#    define GPIO_PK06  (gpio_pin(GPIO_PORTK, 6))
#    define GPIO_PK07  (gpio_pin(GPIO_PORTK, 7))
#    define GPIO_PK08  (gpio_pin(GPIO_PORTK, 8))
#    define GPIO_PK09  (gpio_pin(GPIO_PORTK, 9))
#    define GPIO_PK10  (gpio_pin(GPIO_PORTK, 10))
#    define GPIO_PK11  (gpio_pin(GPIO_PORTK, 11))
#    define GPIO_PK12  (gpio_pin(GPIO_PORTK, 12))
#    define GPIO_PK13  (gpio_pin(GPIO_PORTK, 13))
#    define GPIO_PK14  (gpio_pin(GPIO_PORTK, 14))
#    define GPIO_PK15  (gpio_pin(GPIO_PORTK, 15))
#endif

#if GPIO_MAX_PORTWIDTH > 32
typedef uint32_t port_type;
#elif GPIO_MAX_PORTWIDTH > 16
typedef uint16_t port_type;
#else
typedef uint8_t port_type;
#endif

#ifdef __cplusplus
}
#endif

#endif  // GPIO_DEVICE_H
