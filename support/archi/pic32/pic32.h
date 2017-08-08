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

 #ifndef __XC32
  #define __prog__
  #define nop() {}
  #define enable_interrupt() {}
  #define disable_interrupt() {}
 #else
  #define nop() _nop()
  #define enable_interrupt() __builtin_enable_interrupts()
  #define disable_interrupt() __builtin_disable_interrupts()
 #endif
 #include <xc.h>
 #include <sys/attribs.h>

 #define unlockConfig() SYSKEY = 0; SYSKEY = 0xAA996655; SYSKEY = 0x556699AA;
 #define lockConfig() SYSKEY = 0x33333333;

 #define unlockIoConfig() unlockConfig(); CFGCONbits.IOLOCK = 0;
 #define lockIoConfig() lockConfig(); CFGCONbits.IOLOCK = 1;

#else
 #define nop() {}
 #define enable_interrupt() {}
 #define disable_interrupt() {}

 #define unlockConfig() {}
 #define lockConfig() {}

 #define unlockIoConfig() {}
 #define lockIoConfig() {}
#endif

#define unlockClockConfig() unlockConfig()
#define lockClockConfig() lockConfig()

#endif // PIC32_H
