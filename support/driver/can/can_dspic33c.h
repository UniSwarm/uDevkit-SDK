/**
 * @file can_dspic33c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date September 4 2018, 15:05 PM
 *
 * @brief CAN communication support driver for dsPIC33CH, dsPIC33CK with CAN-Fd extension
 *
 * Implementation based on Microchip document DS70005340A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-CAN-Flexible-Data-Rate-FD-Protocol-Module-70005340a.pdf
 */

#ifndef CAN_DSPIC33C_H
#define CAN_DSPIC33C_H

#if defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) \
 || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH64MP502) \
 || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) \
 || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) \
 || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) \
 || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) \
 || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP502) \
 || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) \
 || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
 || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
 #define CAN_COUNT 1
#elif defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) \
 || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
 #define CAN_COUNT 2
#else
 #define CAN_COUNT 0
#endif

#if defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) \
 || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP505) \
 || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP505) \
 || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH64MP502) \
 || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) \
 || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) \
 || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) \
 || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) \
 || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP502) \
 || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) \
 || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
 || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
 #define CAN_FIFO_COUNT 7
#else
 #define CAN_FIFO_COUNT 0
#endif

#endif // CAN_DSPIC33C_H
