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

int setSystemClock(uint32_t fosc)
{
    sysfreq = fosc;
    return 0;
}

uint32_t getSystemClock()
{
    return sysfreq;
}

uint32_t getSystemClockPeriph()
{
    return sysfreq >> 1;
}

uint32_t getSystemClockCPU()
{
    return sysfreq >> 1;
}
