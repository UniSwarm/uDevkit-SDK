/**
 * @file a6.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date June 25, 2016, 15:30 PM
 *
 * @brief A6 communication support
 */

#ifndef A6_H
#define A6_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/device.h"

int a6_init(rt_dev_t uart, rt_dev_t txen, uint8_t inverted);

ssize_t a6_write(const char *data, size_t size);
ssize_t a6_read(char *data, size_t size_max);

void a6_writeShort(uint16_t channel, uint16_t value);

void a6_task(void);

#ifdef __cplusplus
}
#endif

#endif  // A6_H
