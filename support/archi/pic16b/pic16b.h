/**
 * @file pic16b.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 12, 2017, 11:35 AM
 *
 * @brief Architecture low level definitions for 16 bits dsPIC and PIC
 */

#ifndef PIC16B_H
#define PIC16B_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __XC16
#    define __prog__
#    define __eds__
#    define __pack_upper_byte
#endif

#ifndef SIMULATOR
#    include <xc.h>

#    define nop()         __builtin_nop()
#    define archi_reset() __asm__ volatile("reset")
#    define archi_sleep() __builtin_pwrsav(0)
#    define archi_idle()  __builtin_pwrsav(1)

#    if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#        define enable_interrupt()  INTCON2bits.GIE = 1
#        define disable_interrupt() INTCON2bits.GIE = 0

#        define unlockClockConfig()                                                                                                                            \
            do                                                                                                                                                 \
            {                                                                                                                                                  \
                OSCCONH = 0x78;                                                                                                                                \
                OSCCONH = 0x9A;                                                                                                                                \
            } while (0)
#        define lockClockConfig()                                                                                                                              \
            {                                                                                                                                                  \
            }

#        define unlockIoConfig()                                                                                                                               \
            do                                                                                                                                                 \
            {                                                                                                                                                  \
                OSCCONL = 0x46;                                                                                                                                \
                OSCCONL = 0x57;                                                                                                                                \
                RPCONbits.IOLOCK = 0;                                                                                                                          \
            } while (0)
#        define lockIoConfig()                                                                                                                                 \
            do                                                                                                                                                 \
            {                                                                                                                                                  \
                OSCCONL = 0x46;                                                                                                                                \
                OSCCONL = 0x57;                                                                                                                                \
                RPCONbits.IOLOCK = 1;                                                                                                                          \
            } while (0)

#    elif defined(ARCHI_dspic30f) || defined(ARCHI_dspic33fj) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj)
#        define enable_interrupt()  __builtin_disi(0)
#        define disable_interrupt() __builtin_disi(0x3FFF)
#    endif

#    define archi_init()                                                                                                                                       \
        {                                                                                                                                                      \
        }

#else
#    define nop()                                                                                                                                              \
        {                                                                                                                                                      \
        }
#    define archi_reset()                                                                                                                                      \
        {                                                                                                                                                      \
        }
#    define archi_sleep()                                                                                                                                      \
        {                                                                                                                                                      \
        }
#    define archi_idle()                                                                                                                                       \
        {                                                                                                                                                      \
        }
#    define enable_interrupt()                                                                                                                                 \
        {                                                                                                                                                      \
        }
#    define disable_interrupt()                                                                                                                                \
        {                                                                                                                                                      \
        }
#    define unlockClockConfig()                                                                                                                                \
        {                                                                                                                                                      \
        }
#    define lockClockConfig()                                                                                                                                  \
        {                                                                                                                                                      \
        }
#    define unlockIoConfig()                                                                                                                                   \
        {                                                                                                                                                      \
        }
#    define lockIoConfig()                                                                                                                                     \
        {                                                                                                                                                      \
        }
#endif

#define REGSIZE 2
typedef unsigned short rt_reg_t;
typedef unsigned long rt_reg_ptr_t;

#ifdef __cplusplus
}
#endif

#endif  // PIC16B_H
