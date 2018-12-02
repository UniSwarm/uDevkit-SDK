/**
 * @file can.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2017-2018
 *
 * @date December 8 2017, 09:10 AM
 *
 * @brief CAN low level support driver for udevkit
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
typedef enum
{
    CAN_MODE_NORMAL = 0x0,      ///< CAN normal mode of operation
    CAN_MODE_NORMAL_FD,         ///< CAN normal FD mode of operation
    CAN_MODE_LISTENONLY,        ///< CAN only listen mode
    CAN_MODE_LISTENALL,         ///< CAN listen all without taking care of adresses
    CAN_MODE_LOOPBACK,          ///< CAN loopback mode for test purpose and self diagnostics
    CAN_MODE_DISABLED,          ///< CAN disabled
    CAN_MODE_CONFIGURATION      ///< CAN disabled
} CAN_MODE;
int can_setMode(rt_dev_t device, CAN_MODE mode);
CAN_MODE can_mode(rt_dev_t device);

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg);
uint32_t can_bitRate(rt_dev_t device);
uint32_t can_effectiveBitRate(rt_dev_t device);
uint8_t can_propagSeg(rt_dev_t device);
uint8_t can_s1Seg(rt_dev_t device);
uint8_t can_s2Seg(rt_dev_t device);

// ===== mailbox interface =====
typedef enum
{
    CAN_VERS1    = 0x00,     ///< CAN version 1 with standard 11 bits identifier
    CAN_VERS2A   = 0x01,     ///< CAN version 2A, extended identifier are error
    CAN_VERS2BP  = 0x02,     ///< CAN version 2B pasive, extended ignored
    CAN_VERS2BA  = 0x03,     ///< CAN version 2B active, work with extended 29 bits
                             /// identifier and standard 11 bits identifier
    CAN_RTR      = 0x04      ///< Remote transmit request
} CAN_FLAGS;

typedef struct {
    uint32_t id;
    CAN_FLAGS flags;
    uint8_t size;
} CAN_MSG_HEADER;

int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data);
int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data);

#if defined(ARCHI_dspic30f)
 #include "can_dspic30f.h"
#elif defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
 #include "can_dspic33c.h"
#elif defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev)
 #include "can_pic24_dspic33.h"
#elif defined(ARCHI_pic32mx) || defined(ARCHI_pic32mk) || defined(ARCHI_pic32mzec) \
 || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 #include "can_pic32.h"
#endif

#endif // CAN_H
