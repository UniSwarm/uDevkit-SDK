/**
 * @file sysclock_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 17, 2016, 11:45 PM
 *
 * @brief System clock support for rtprog sim
 */

#include <stdint.h>

#include "sysclock.h"

uint32_t sysfreq;

int sysclock_setClock(uint32_t fosc)
{
    sysfreq = fosc;
    return 0;
}

uint32_t sysclock_getClock()
{
    return sysfreq;
}

uint32_t sysclock_getCPUSystemClock()
{
    return sysfreq >> 1;
}

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    // TODO
    return sysfreq / 2;
}
#else
uint32_t sysclock_periphFreq()
{
    return sysfreq >> 1;
}
#endif

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
int sysclock_setPeriphClockDiv(SYSCLOCK_CLOCK busClock, uint8_t div)
{
    // TODO
    return 0;
}

SYSCLOCK_SOURCE sysclock_source()
{
    // TODO
    return 0;
}

int sysclock_switchSourceTo(SYSCLOCK_SOURCE source)
{
    // TODO
    return 0;
}
#endif
