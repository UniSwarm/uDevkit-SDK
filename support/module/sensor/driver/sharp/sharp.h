/**
 * @file sharp.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date avril 28, 2016, 13:34  
 * 
 * @brief Conversion functions for Sharp analog distance sensor
 */

#ifndef SHARP_H
#define SHARP_H

#include <stdint.h>

#define Voltage			1
#define NearSharp		2
#define FarSharp		4
#define LongFarSharp	8

uint16_t sharp_convert(uint16_t v, uint8_t type);

#endif // SHARP_H
