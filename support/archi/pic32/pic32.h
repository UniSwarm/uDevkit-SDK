/**
 * @file pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 12, 2017, 11:35 AM
 *
 * @brief Architecture low level definitions for PIC32
 */

#ifndef PIC32_H
#define PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIMULATOR

#    include <sys/attribs.h>
#    include <sys/kmem.h>
#    ifndef __XC32
#        define __prog__
#        define nop()                                                                                                                                          \
            {                                                                                                                                                  \
            }
#        define enable_interrupt()                                                                                                                             \
            {                                                                                                                                                  \
            }
#        define disable_interrupt()                                                                                                                            \
            {                                                                                                                                                  \
            }
#        define __ISR(a, b)

#    else  // !__XC32
#        define nop()               _nop()
#        define enable_interrupt()  __builtin_enable_interrupts()
#        define disable_interrupt() __builtin_disable_interrupts()
#    endif  // __XC32
#    include <xc.h>

#    define unlockConfig()                                                                                                                                     \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            SYSKEY = 0;                                                                                                                                        \
            SYSKEY = 0xAA996655;                                                                                                                               \
            SYSKEY = 0x556699AA;                                                                                                                               \
        } while (0)

#    define lockConfig()                                                                                                                                       \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            SYSKEY = 0x33333333;                                                                                                                               \
        } while (0)

#    define unlockIoConfig()                                                                                                                                   \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            unlockConfig();                                                                                                                                    \
            CFGCONbits.IOLOCK = 0;                                                                                                                             \
            lockConfig();                                                                                                                                      \
        } while (0)
#    define lockIoConfig()                                                                                                                                     \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            unlockConfig();                                                                                                                                    \
            CFGCONbits.IOLOCK = 1;                                                                                                                             \
            lockConfig();                                                                                                                                      \
        } while (0)

#else  // SIMULATOR
#    define nop()                                                                                                                                              \
        {                                                                                                                                                      \
        }
#    define enable_interrupt()                                                                                                                                 \
        {                                                                                                                                                      \
        }
#    define disable_interrupt()                                                                                                                                \
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

#    define unlockConfig()                                                                                                                                     \
        {                                                                                                                                                      \
        }
#    define lockConfig()                                                                                                                                       \
        {                                                                                                                                                      \
        }

#    define unlockIoConfig()                                                                                                                                   \
        {                                                                                                                                                      \
        }
#    define lockIoConfig()                                                                                                                                     \
        {                                                                                                                                                      \
        }
#endif  // SIMULATOR

#define unlockClockConfig() unlockConfig()
#define lockClockConfig()   lockConfig()

#define REGSIZE 4
typedef unsigned int rt_reg_t;
typedef unsigned int rt_reg_ptr_t;

#ifdef __cplusplus
}
#endif

#endif  // PIC32_H
