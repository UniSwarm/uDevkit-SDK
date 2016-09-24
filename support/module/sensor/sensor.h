/**
 * @file sensor.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date September 24, 2016, 14:56 PM
 *
 * @brief Sensor module to handle various types of sensors for RTProg
 */

#ifndef SENSOR_H
#define SENSOR_H

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

uint8_t sensor_count();
Sensor *sensor_get(uint8_t s);
uint8_t sensor_add(Sensor *sensor);

#endif // SENSOR_H