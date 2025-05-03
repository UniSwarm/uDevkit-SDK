/**
 * @file gpio_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date May 3, 2025, 04:34 PM
 *
 * @brief GPIO support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip document DS70005539B:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 */

#ifndef GPIO_DSPIC33A_PIC32A_H
#define GPIO_DSPIC33A_PIC32A_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32AK1216GC41036) || defined(DEVICE_32AK1216GC41048) || defined(DEVICE_32AK1216GC41064) || defined(DEVICE_32AK3208GC41036)                   \
    || defined(DEVICE_32AK3208GC41048) || defined(DEVICE_32AK3208GC41064) || defined(DEVICE_32AK6416GC41036) || defined(DEVICE_32AK6416GC41048)                \
    || defined(DEVICE_32AK6416GC41064) || defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105)                            \
    || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102) || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) \
    || defined(DEVICE_33AK128MC102) || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)                            \
    || defined(DEVICE_33AK256MC205) || defined(DEVICE_33AK256MC206) || defined(DEVICE_33AK256MC208) || defined(DEVICE_33AK256MC505)                            \
    || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MPS205) || defined(DEVICE_33AK256MPS206)                          \
    || defined(DEVICE_33AK256MPS208) || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506) || defined(DEVICE_33AK256MPS508)                        \
    || defined(DEVICE_33AK512MC205) || defined(DEVICE_33AK512MC206) || defined(DEVICE_33AK512MC208) || defined(DEVICE_33AK512MC505)                            \
    || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508) || defined(DEVICE_33AK512MPS205) || defined(DEVICE_33AK512MPS206)                          \
    || defined(DEVICE_33AK512MPS208) || defined(DEVICE_33AK512MPS505) || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_PORT_COUNT 4
#    define GPIO_PORT_MAX   4
#elif defined(DEVICE_33AK256MC210) || defined(DEVICE_33AK256MC510) || defined(DEVICE_33AK256MPS210) || defined(DEVICE_33AK256MPS510)                           \
    || defined(DEVICE_33AK512MC210) || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS210) || defined(DEVICE_33AK512MPS510)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 7
#    define GPIO_PORT_MAX   7
#elif defined(DEVICE_33AK256MPS212) || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MPS212) || defined(DEVICE_33AK512MPS512)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_HAVE_PORTH
#    define GPIO_PORT_COUNT 8
#    define GPIO_PORT_MAX   8
#endif

#define GPIO_MAX_PORTWIDTH     16
#define GPIO_MAX_PORTWIDTHU    4
#define GPIO_MAX_PORTWIDTHMASK 0x0F

#define GPIO_HAVE_CHANGENOTIFICATION  // have change notification on pins
#define GPIO_HAVE_OPENDRAIN           // have open drain output config

#ifdef __cplusplus
}
#endif

#endif  // GPIO_DSPIC33A_PIC32A_H
