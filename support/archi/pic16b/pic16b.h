/**
 * @file pic16b.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date March 12, 2017, 11:35 AM
 *
 * @brief Architecture low level definitions for 16 bits dsPIC and PIC
 */

#ifndef PIC16B_H
#define PIC16B_H

#ifndef SIMULATOR

 #ifndef __XC16
  #define __prog__
 #endif
 #include <xc.h>

 #define nop() __builtin_nop()

 #if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_pic24ep) \
  || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
  #define enable_interrupt() INTCON2bits.GIE=1
  #define disable_interrupt() INTCON2bits.GIE=0

 #elif defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_pic24f) \
    || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj)
  #define enable_interrupt() __builtin_disi(0)
  #define disable_interrupt() __builtin_disi(0x3FFF)
 #endif

 #define archi_init() {}

#else
 #define nop() {}
 #define enable_interrupt() {}
 #define disable_interrupt() {}
#endif

#define REGSIZE 2
typedef unsigned short rt_reg_t;
typedef unsigned long rt_reg_ptr_t;

#endif // PIC16B_H
