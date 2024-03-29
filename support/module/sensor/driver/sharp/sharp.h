/**
 * @file sharp.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date avril 28, 2016, 13:34
 *
 * @brief Conversion functions for Sharp analog distance sensor
 */

#ifndef SHARP_H
#define SHARP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define Voltage      1
#define NearSharp    2
#define FarSharp     4
#define LongFarSharp 8

uint16_t sharp_convert(uint16_t v, uint8_t type);

#ifdef __cplusplus
}
#endif

#endif  // SHARP_H
