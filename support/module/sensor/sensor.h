/**
 * @file sensor.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date September 24, 2016, 14:56 PM
 *
 * @brief Sensor module to handle various types
 * of sensors for uDevkit-SDK
 */

#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sensor_driver.h"
#ifdef USE_sharp
#    include "driver/sharp/sharp.h"
#endif
#ifdef USE_VL6180X
#    include "driver/VL6180X/VL6180X.h"
#endif

#define SENSOR_TYPE_DISTANCE
#define SENSOR_TYPE_LIGHT
#define SENSOR_TYPE_SOUND

#define SENSOR_TYPE_VOLTAGE
#define SENSOR_TYPE_CURRENT

typedef struct
{
    uint8_t type;
    uint8_t model;
    uint32_t sample_period;
} Sensor;

uint8_t sensor_count(void);
Sensor *sensor_get(uint8_t s);
uint8_t sensor_add(Sensor *sensor);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_H
