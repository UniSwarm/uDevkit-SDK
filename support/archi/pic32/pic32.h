/**
 * @file pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date March 12, 2017, 11:35 AM
 *
 * @brief Architecture low level definitions for PIC32
 */

#ifndef PIC32_H
#define PIC32_H

#ifndef SIMULATOR
 #include <xc.h>
 #include <sys/attribs.h>

 #define nop() _nop()
 #define enable_interrupt() __builtin_enable_interrupts()
 #define disable_interrupt() __builtin_disable_interrupts()

#else
 #define nop() {}
 #define enable_interrupt() {}
 #define disable_interrupt() {}
#endif

#endif // PIC32_H
