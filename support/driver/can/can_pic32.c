/**
 * @file can_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2017
 *
 * @date December 8 2017, 09:10 AM
 *
 * @brief CAN support for rtprog for PIC32MK, PIC32MX, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61154C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61154C.pdf
 */

#include "can.h"

#include <driver/sysclock.h>
#include <archi.h>

#if !defined (CAN_COUNT) || CAN_COUNT==0
  #warning "No can on the current device or unknow device"
#endif

#define CAN_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned eid : 1;
            unsigned : 5;
        };
        uint8_t val;
    };
} can_status;

struct can_dev
{
    uint8_t mode;
    CAN_VERSION canVersion;
    uint32_t bitRate;
    uint8_t propagSeg;
    uint8_t s1Seg;
    uint8_t s2Seg;
    can_status flags;
};

struct can_dev cans[] = {
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#if CAN_COUNT>=2
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=3
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=4
    {
        .bitRate = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free can device number and open it
 * @return can device number
 */
rt_dev_t can_getFreeDevice()
{
#if CAN_COUNT>=1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CAN_COUNT; i++)
        if (cans[i].flags.used == 0)
            break;

    if (i == CAN_COUNT)
        return NULLDEV;
    device = MKDEV(DEV_CLASS_CAN, i);

    can_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open an can from his can rt_dev_t
 * @param can can rt_dev_t id
 * @return 0 if ok, -1 in case of error
 */
int can_open(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;
    if (cans[can].flags.used == 1)
        return -1;

    cans[can].flags.used = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close and release an can
 * @param device can device number
 * @return 0 if ok, -1 in case of error
 */
int can_closeDevice(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    can_disable(device);

    cans[can].flags.val = CAN_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified can device
 * @param device can device number
 * @return 0 if ok, -1 in case of error
 */
int can_enable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    cans[can].flags.enabled = 1;

    switch (can)
    {
    case 0:
        // TODO
        break;
#if CAN_COUNT>=2
    case 1:
        // TODO
        break;
#endif
    }

    return 0;
}

/**
 * @brief Disable the specified can device
 * @param device can device number
 * @return 0 if ok, -1 in case of error
 */
int can_disable(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return -1;

    cans[can].flags.enabled = 0;

    switch (can)
    {
    case 0:
        _CAN1IE = 0;       // disable can global interrupt
        C1CONbits.ON = 0;  // disable can
        break;
#if CAN_COUNT>=2
    case 1:
        _CAN2IE = 0;       // disable can global interrupt
        C2CONbits.ON = 0;  // disable can
        break;
#endif
    }

    return 0;
}

/**
 * @brief Sets configuration (can version and mode) of the specified can device
 * @param device can device number
 * @param mode CAN mode of operation
 * @param canVersion version of CAN bus
 * @return 0 if ok, -1 in case of error
 */
int can_setConfig(rt_dev_t device, uint8_t mode, CAN_VERSION canVersion)
{
    uint8_t enabled = 0;

    // check parameters

    // disable can if it was already enabled
    // TODO

    // baud rate computation

    if (enabled == 1)
        can_enable(device);

    return 0;
}
uint8_t can_mode(rt_dev_t device);
uint8_t can_canVersion(rt_dev_t device);

int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
    uint8_t can = MINOR(device);
    uint8_t bitRateDiv;
    uint8_t quantum;
    if (can >= CAN_COUNT)
        return 0;

    if (propagSeg > 8 || s1Seg > 8 || s2Seg > 8)
        return -1;
    quantum = propagSeg + s1Seg + s2Seg + 1;
    if (quantum < 8 || quantum > 25)
        return -1;

    // CAN Bit Timing (8-25 Tq) segments computation
    // | Sync | Propag seg | Phase seg 1 | Phase seg 2 |
    // | 1 Tq |   1-8 Tq   |   1-8 Tq    |   1-8 Tq    |
    //                              sample point
    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;

    bitRateDiv = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN) / (quantum * 2);

    switch (can)
    {
    case 0:
        C1CONbits.REQOP = 4;
        while (C1CONbits.OPMOD != 4);

        C1CFGbits.SJW    = 1;          // Synchronization Jump Width (1-4)
        C1CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C1CFGbits.SEG1PH = s1Seg;      // Phase Buffer Segment 1 (1-8)
        C1CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C1CFGbits.SEG2PH = s2Seg;      // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C1CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#if CAN_COUNT>=2
    case 1:
        C2CONbits.REQOP = 4;
        while (C2CONbits.OPMOD != 4);

        C2CFGbits.SJW    = 1;          // Synchronization Jump Width (1-4)
        C2CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C2CFGbits.SEG1PH = s1Seg;      // Phase Buffer Segment 1 (1-8)
        C2CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C2CFGbits.SEG2PH = s2Seg;      // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C2CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
#if CAN_COUNT>=3
    case 2:
        C3CONbits.REQOP = 4;
        while (C3CONbits.OPMOD != 4);

        C3CFGbits.SJW    = 1;          // Synchronization Jump Width (1-4)
        C3CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C3CFGbits.SEG1PH = s1Seg;      // Phase Buffer Segment 1 (1-8)
        C3CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C3CFGbits.SEG2PH = s2Seg;      // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C3CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
#if CAN_COUNT>=4
    case 3:
        C4CONbits.REQOP = 4;
        while (C4CONbits.OPMOD != 4);

        C4CFGbits.SJW    = 1;          // Synchronization Jump Width (1-4)
        C4CFGbits.PRSEG  = propagSeg;  // Propagation Time Segment (1-8)
        C4CFGbits.SEG1PH = s1Seg;      // Phase Buffer Segment 1 (1-8)
        C4CFGbits.SEG2PHTS = 1;        // Phase Buffer Segment 2 is freely programmable
        C4CFGbits.SEG2PH = s2Seg;      // Phase Buffer Segment 2 (1-8) SEG2PH ≤ SEG1PH
        C4CFGbits.BRP    = bitRateDiv; // bit rate divisor (1-64) * 2
        break;
#endif
    }

    return 0;
}

/**
 * @brief Returns the curent bit rate in bits/s
 * @param device CAN device number
 * @return bit rate in bits/s if ok, 0 in case of error
 */
uint32_t can_bitRate(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].bitRate;
#else
    return 0;
#endif
}

/**
 * @brief Gets the effective bit rate in hertz
 * @param device CAN device number
 * @return speed of receive and transmit in bits/s, 0 in case of error
 */
uint32_t can_effectiveBitRate(rt_dev_t device)
{
    uint32_t baudSpeed;
    uint16_t uBrg;

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    // TODO

    return baudSpeed;
}

uint8_t can_propagSeg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].propagSeg;
#else
    return 0;
#endif
}

uint8_t can_s1Seg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].s1Seg;
#else
    return 0;
#endif
}

uint8_t can_s2Seg(rt_dev_t device)
{
#if CAN_COUNT>=1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].s2Seg;
#else
    return 0;
#endif
}
