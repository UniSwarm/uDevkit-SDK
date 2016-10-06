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



// ======= specific include =======
#if defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
 #include "ic_pic24e_dspic33e.h"
#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj)
 #include "ic_pic24f_dspic33f_dspic30f.h"
#elif defined(ARCHI_pic32mm) || defined(ARCHI_pic32mx) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
 #include "ic_pic32.h"
#else
 #error Unsuported ARCHI
#endif

#endif // IC_H
