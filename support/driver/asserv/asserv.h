/**
 * @file asserv.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 15:10  
 * 
 * @brief Support for motor control with positionning
 */

#ifndef ASSERV_H
#define ASSERV_H

#include <stdint.h>

void asserv_init();

void asserv_locTask();

int asserv_getXPos();
int asserv_getYPos();
int asserv_getTPos();

#endif // ASSERV_H
