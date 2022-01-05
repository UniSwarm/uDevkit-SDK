/**
 * @file can_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
 *
 * @date April 28 2019, 23:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */

#ifndef CAN_SIM_H
#define CAN_SIM_H

#include <driver/device.h>

#include <stdint.h>

typedef struct
{
    uint32_t bitRate;
    uint8_t propagSeg;
    uint8_t s1Seg;
    uint8_t s2Seg;
    uint8_t enabled;
    uint8_t used;
    uint8_t mode;
    char bus[20];
} can_dev;

typedef struct
{
    uint32_t can_id;
    uint8_t can_dlc;
    uint8_t flag;
    char data[8];
} can_sim_frame;

#define CAN_SIM_MODULE 0x0014

#define CAN_SIM_CONFIG 0x0001
#define CAN_SIM_WRITE  0x0002
#define CAN_SIM_READ   0x0003

#ifndef SIMULATOR
#    define can_sim_setBus(device, bus) 0
#else
int can_sim_setBus(rt_dev_t device, char *bus);
int can_sim_isConnected(rt_dev_t device);
#endif

#endif  // CAN_SIM_H
