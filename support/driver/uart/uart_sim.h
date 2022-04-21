/**
 * @file uart_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date November 05, 2016, 17:51 PM
 *
 * @brief Uart simulator support for udevkit for simulation purpose
 */

#ifndef UART_SIM_H
#define UART_SIM_H

#include <stdint.h>

typedef struct
{
    uint32_t baudSpeed;
    uint8_t bitStop;
    uint8_t bitParity;
    uint8_t bitLength;
    uint8_t enabled;
} uart_dev;

#define UART_SIM_MODULE 0x0010

#define UART_SIM_CONFIG 0x0001
#define UART_SIM_WRITE  0x0002
#define UART_SIM_READ   0x0003

#endif  // UART_SIM_H
