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

uint32_t sysclock_getPeriphClock()
{
    return sysfreq >> 1;
}

uint32_t sysclock_getCPUSystemClock()
{
    return sysfreq >> 1;
}
