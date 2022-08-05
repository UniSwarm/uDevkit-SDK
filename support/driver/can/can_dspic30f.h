/**
 * @file can_dspic30f.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date May 06, 2016, 11:34 AM
 *
 * @brief CAN communication support driver for dsPIC30F
 *
 * Implementation based on Microchip document DS70070D :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70070D.pdf
 */

#ifndef CAN_dsPIC30F_H
#define CAN_dsPIC30F_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_30F4011) || defined(DEVICE_30F4011E) || defined(DEVICE_30F4012) || defined(DEVICE_30F4012E) || defined(DEVICE_30F4013)                      \
    || defined(DEVICE_30F4013E) || defined(DEVICE_30F5015) || defined(DEVICE_30F5015E) || defined(DEVICE_30F5016) || defined(DEVICE_30F6015)
#    define CAN_COUNT 1
#elif defined(DEVICE_30F5011) || defined(DEVICE_30F5011E) || defined(DEVICE_30F5013) || defined(DEVICE_30F5013E) || defined(DEVICE_30F6010)                    \
    || defined(DEVICE_30F6010A) || defined(DEVICE_30F6011) || defined(DEVICE_30F6011A) || defined(DEVICE_30F6012) || defined(DEVICE_30F6012A)                  \
    || defined(DEVICE_30F6013) || defined(DEVICE_30F6013A) || defined(DEVICE_30F6014) || defined(DEVICE_30F6014A)
#    define CAN_COUNT 2
#else
#    define CAN_COUNT 0
#endif

typedef enum
{
    CAN_RXFIFO_NOT_EMPTY = 0x01,   ///<
    CAN_TXFIFO_NOT_FULL = 0x01,    ///<
    CAN_RXFIFO_HALF_FULL = 0x02,   ///<
    CAN_TXFIFO_HALF_EMPTY = 0x02,  ///<
    CAN_RXFIFO_FULL = 0x04,        ///<
    CAN_TXFIFO_EMPTY = 0x04,       ///<
} CAN_FIFO_EVENTS;

#ifdef __cplusplus
}
#endif

#endif  // CAN_dsPIC30F_H
