/**
 * @file can_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2018-2019
 *
 * @date April 28 2019, 23:01 PM
 *
 * @brief CAN udevkit simulator support for simulation purpose
 */
 
#ifndef CAN_SIM_H
#define CAN_SIM_H

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
} can_dev;

#define CAN_SIM_MODULE 0x0014

#define CAN_SIM_CONFIG 0x0001
#define CAN_SIM_WRITE  0x0002
#define CAN_SIM_READ   0x0003

#endif // CAN_SIM_H
