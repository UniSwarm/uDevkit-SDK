/**
 * @file can.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2017
 *
 * @date December 8 2017, 09:10 AM
 *
 * @brief CAN low level support driver for rtprog
 */

#ifndef CAN_H
#define CAN_H

#include <driver/device.h>

// ====== bus assignation ======
#define can(d) MKDEV(DEV_CLASS_CAN, (d)-1)
rt_dev_t can_getFreeDevice();
int can_open(rt_dev_t device);
int can_close(rt_dev_t device);

// ==== bus enable/disable =====
int can_enable(rt_dev_t device);
int can_disable(rt_dev_t device);

// ======== bus settings =======
typedef enum {
    CAN_VERSION_1 = 0x0,        ///< CAN version 1 with standard 11 bits identifier
    CAN_VERSION_2A,             ///< CAN version 2A, extended identifier are error
    CAN_VERSION_2B_PASSIVE,     ///< CAN version 2B, extended ignored
    CAN_VERSION_2B_ACTIVE       ///< CAN version 2B, work with extended 29 bits
                                /// identifier and standard 11 bits identifier
} CAN_VERSION;
int can_setConfig(rt_dev_t device, uint8_t mode, CAN_VERSION canVersion);
uint8_t can_mode(rt_dev_t device);
uint8_t can_canVersion(rt_dev_t device);

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg);
uint32_t can_bitRate(rt_dev_t device);
uint32_t can_effectiveBitRate(rt_dev_t device);
uint8_t can_propagSeg(rt_dev_t device);
uint8_t can_s1Seg(rt_dev_t device);
uint8_t can_s2Seg(rt_dev_t device);

// ===== mailbox interface =====
// TODO

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev)
 #include "can_pic24_dspic33.h"
#elif defined(ARCHI_dspic30f)
 #include "can_dspic30f.h"
#elif defined(ARCHI_pic32mx) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) \
 || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "can_pic32.h"
#endif

#endif // CAN_H
