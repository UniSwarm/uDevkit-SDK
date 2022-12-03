/**
 * @file can_device.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
 *
 * @date December 3, 2022, 11:56 AM
 *
 * @brief CAN support for specific devices
 */

#ifndef CAN_DEVICE_H
#define CAN_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <driver/device.h>

#if defined(ARCHI_dspic30f)
#    include "can_dspic30f.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "can_dspic33c.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)                          \
    || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
#    include "can_pic24_dspic33.h"
#elif defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)                     \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
// PIC32MK with CANFD
#    include "can_pic32_fd.h"
#elif defined(ARCHI_pic32mx) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
#    include "can_pic32.h"
#else
#    define CAN_COUNT 0
typedef enum
{
    CAN_RXFIFO_NOT_EMPTY,
    CAN_TXFIFO_NOT_FULL,
    CAN_RXFIFO_HALF_FULL,
    CAN_TXFIFO_HALF_EMPTY,
    CAN_RXFIFO_FULL,
    CAN_TXFIFO_EMPTY,
    CAN_RXFIFO_OVERFLOW,
} CAN_FIFO_EVENTS;
#endif

typedef enum
{
    CAN_FIFO00 = 0,
    CAN_FIFO01 = 1,
    CAN_FIFO02 = 2,
    CAN_FIFO03 = 3,
    CAN_FIFO04 = 4,
    CAN_FIFO05 = 5,
    CAN_FIFO06 = 6,
    CAN_FIFO07 = 7,
    CAN_FIFO08 = 8,
    CAN_FIFO09 = 9,
    CAN_FIFO10 = 10,
    CAN_FIFO11 = 11,
    CAN_FIFO12 = 12,
    CAN_FIFO13 = 13,
    CAN_FIFO14 = 14,
    CAN_FIFO15 = 15,
    CAN_FIFO16 = 16,
    CAN_FIFO17 = 17,
    CAN_FIFO18 = 18,
    CAN_FIFO19 = 19,
    CAN_FIFO20 = 20,
    CAN_FIFO21 = 21,
    CAN_FIFO22 = 22,
    CAN_FIFO23 = 23,
    CAN_FIFO24 = 24,
    CAN_FIFO25 = 25,
    CAN_FIFO26 = 26,
    CAN_FIFO27 = 27,
    CAN_FIFO28 = 28,
    CAN_FIFO29 = 29,
    CAN_FIFO30 = 30,
    CAN_FIFO31 = 31,
} CAN_FIFO_ID;

typedef enum
{
    CAN_FILTER00 = 0,
    CAN_FILTER01 = 1,
    CAN_FILTER02 = 2,
    CAN_FILTER03 = 3,
    CAN_FILTER04 = 4,
    CAN_FILTER05 = 5,
    CAN_FILTER06 = 6,
    CAN_FILTER07 = 7,
    CAN_FILTER08 = 8,
    CAN_FILTER09 = 9,
    CAN_FILTER10 = 10,
    CAN_FILTER11 = 11,
    CAN_FILTER12 = 12,
    CAN_FILTER13 = 13,
    CAN_FILTER14 = 14,
    CAN_FILTER15 = 15,
    CAN_FILTER16 = 16,
    CAN_FILTER17 = 17,
    CAN_FILTER18 = 18,
    CAN_FILTER19 = 19,
    CAN_FILTER20 = 20,
    CAN_FILTER21 = 21,
    CAN_FILTER22 = 22,
    CAN_FILTER23 = 23,
    CAN_FILTER24 = 24,
    CAN_FILTER25 = 25,
    CAN_FILTER26 = 26,
    CAN_FILTER27 = 27,
    CAN_FILTER28 = 28,
    CAN_FILTER29 = 29,
    CAN_FILTER30 = 30,
    CAN_FILTER31 = 31,
} CAN_FILTER_ID;

#ifdef __cplusplus
}
#endif

#endif  // CAN_DEVICE_H
