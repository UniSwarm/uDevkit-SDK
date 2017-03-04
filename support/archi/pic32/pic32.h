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
#endif

#define nop() _nop()
#define enable_interrupt() __builtin_enable_interrupts()
#define disable_interrupt() __builtin_disable_interrupts()

#endif // PIC32_H
