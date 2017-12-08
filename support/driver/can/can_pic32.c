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
    uint32_t baudSpeed;
    uint8_t mode;
    CAN_VERSION canVersion;
    can_status flags;
};

struct can_dev cans[] = {
    {
        .baudSpeed = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#if CAN_COUNT>=2
    {
        .baudSpeed = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=3
    {
        .baudSpeed = 0,
        .flags = {{.val = CAN_FLAG_UNUSED}}
    },
#endif
#if CAN_COUNT>=4
    {
        .baudSpeed = 0,
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
 * @brief Sets configuration (speed of receive and transmit, can version and mode) of the specified can device
 * @param device can device number
 * @param baudSpeed speed of receive and transmit in bauds (bits / s)
 * @return 0 if ok, -1 in case of error
 */
int can_setConfig(rt_dev_t device, uint8_t mode, CAN_VERSION canVersion, uint32_t baudSpeed)
{
    uint32_t systemClockPeriph;
    uint16_t uBrg;
    uint8_t hs = 0;
    uint8_t enabled = 0;

    // check parameters

    // disable can if it was already enabled
    // TODO

    // baud rate computation

    if (enabled == 1)
        can_enable(device);

    return 0;
}

/**
 * @brief Gets the true baud speed of the specified can device
 * @param device can device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t can_baudSpeed(rt_dev_t device)
{
    uint32_t baudSpeed;
    uint16_t uBrg;

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    // TODO

    return baudSpeed;
}

/**
 * @brief Gets the effective baud speed of the specified can device
 * @param device can device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t can_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
        return 0;

    return cans[can].baudSpeed;
}
