/**
 * @file oc.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 18, 2016, 15:40 PM 
 * 
 * @brief Output Compare support driver
 */

#ifndef OC_H
#define OC_H

#include "driver/device.h"

#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "oc_pic24e_dspic33e.h"
#if defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "oc_pic24f_dspic33f_dspic30f.h"
#else
 #error Unsuported ARCHI
#endif



#endif // OC_H
