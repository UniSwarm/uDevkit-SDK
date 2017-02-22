/**
 * @file a6.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 25, 2016, 15:30 PM
 *
 * @brief A6 communication support
 */

#ifndef A6_H
#define A6_H

#include "driver/device.h"

int a6_init();

ssize_t a6_write(const char *data, size_t size);
ssize_t a6_read(char *data, size_t size_max);

void a6_writeShort(uint16_t channel, uint16_t value);

#endif // A6_H
