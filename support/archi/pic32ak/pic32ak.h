/**
 * @file pic32ak.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date May 3, 2025, 10:22 PM
 *
 * @brief Architecture low level definitions for PIC32AK
 */

#ifndef PIC32AK_H
#define PIC32AK_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIMULATOR
#    include <xc.h>

#    define nop()         __builtin_nop()
#    define archi_reset() __asm__ volatile("reset")
#    define archi_sleep() __builtin_pwrsav(0)
#    define archi_idle()  __builtin_pwrsav(1)

#    define archi_init()                                                                                                                                       \
        {                                                                                                                                                      \
        }

#    define unlockIoConfig()                                                                                                                                   \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            RPCONbits.IOLOCK = 0;                                                                                                                              \
        } while (0)
#    define lockIoConfig()                                                                                                                                     \
        do                                                                                                                                                     \
        {                                                                                                                                                      \
            RPCONbits.IOLOCK = 1;                                                                                                                              \
        } while (0)

#    define enable_interrupt()  __builtin_enable_interrupts()
#    define disable_interrupt() __builtin_disable_interrupts()

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
#endif

#define REGSIZE 4
typedef unsigned int rt_reg_t;
typedef unsigned int rt_reg_ptr_t;

#ifdef __cplusplus
}
#endif

#endif  // PIC32AK_H
