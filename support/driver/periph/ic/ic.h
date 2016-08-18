/**
 * @file ic.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 18, 2016, 15:40 PM 
 * 
 * @brief Input Compare support driver
 */

#ifndef IC_H
#define IC_H

#include "driver/device.h"

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "ic_pic24e_dspic33e.h"
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "ic_pic24f_dspic33f_dspic30f.h"
#else
 #error Unsuported ARCHI
#endif



#endif // IC_H
