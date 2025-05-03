/**
 * @file dspic33ak.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date May 3, 2025, 06:01 PM
 *
 * @brief Architecture low level definitions for dsPIC33AK
 */

#ifndef DSPIC33AK_H
#define DSPIC33AK_H

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
#endif

#define REGSIZE 4
typedef unsigned int rt_reg_t;
typedef unsigned int rt_reg_ptr_t;

#ifdef __cplusplus
}
#endif

#endif  // DSPIC33AK_H
