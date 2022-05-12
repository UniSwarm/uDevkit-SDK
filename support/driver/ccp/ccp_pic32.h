/**
 * @file ccp_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2022
 *
 * @date December 17, 2018, 23:00 PM
 *
 * @brief CCP capture/compare/PWM/Timer support driver for PIC32MM
 *
 * Implementation based on Microchip document DS60001381A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001381a.pdf
 */

#ifndef CCP_PIC32_H
#define CCP_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL020)                       \
    || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028)                    \
    || defined(DEVICE_32MM0064GPL036)
#    define CCP_COUNT 3
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) || defined(DEVICE_32MM0064GPM064)                     \
    || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064)                    \
    || defined(DEVICE_32MM0256GPM028) || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
#    define CCP_COUNT 9
#else
#    define CCP_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // CCP_PIC32_H
