/**
 * @file pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date November 21, 2022, 01:34 PM
 *
 * @brief Archi low level functions
 */

#include "archi.h"

void __attribute__((noreturn)) archi_reset(void)
{
    unlockConfig();

    // set SWRST bit to arm reset
    RSWRSTSET = 1;

    // read RSWRST register to trigger reset
    (void)RSWRST;

    // prevent any unwanted code execution until reset occurs
    while (1)
    {
        nop();
    }
}

void archi_sleep(void)
{
    if (OSCCONbits.SLPEN != 1)
    {
        unlockConfig();
        // now change the OSCCON register
        OSCCONbits.SLPEN = 1;
        lockConfig();
    }
    // now go to sleep
    asm volatile("wait");
}

void archi_idle(void)
{
    if (OSCCONbits.SLPEN != 0)
    {
        unlockConfig();
        // now change the OSCCON register
        OSCCONbits.SLPEN = 0;
        lockConfig();
    }
    // now go to sleep
    asm volatile("wait");
}
