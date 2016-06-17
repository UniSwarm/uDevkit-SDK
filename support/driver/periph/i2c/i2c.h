/**
 * @file i2c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 09, 2016, 18:47 PM
 * 
 * @brief I2C communication support driver
 */

#ifndef I2C_H
#define I2C_H

#include "driver/device.h"

#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)
 #include "i2c_dspic.h"
#else
 #error Unsuported ARCHI
#endif



#endif // I2C_H
