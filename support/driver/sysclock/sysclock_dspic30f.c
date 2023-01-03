/**
 * @file sysclock_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for udevkit for dsPIC30F
 *
 * Implementation based on Microchip documents DS70054E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70054e.pdf
 */

#include "sysclock.h"

#include <archi.h>

#include "board.h"

static uint32_t _sysclock_sysfreq = 0;
static uint32_t _sysclock_sosc = 0;
static uint32_t _sysclock_posc = 0;

#ifdef SYSCLOCK_SRC_PLL
static uint32_t _sysclock_pll = 0;
#endif

/**
 * @brief Gets the actual frequency on a particular peripheral bus clock
 * @param busClock id of the bus clock (1 periph bus clock), 0 for sysclock
 * @return bus frequency in Hz, 1 in case of error to not cause divide by 0
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    if (_sysclock_sysfreq == 0)
    {
        _sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());
    }

    if (busClock == SYSCLOCK_CLOCK_SYSCLK)
    {
        return _sysclock_sysfreq;
    }

    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
#ifndef SYSCLOCK_NOPOST
        uint16_t div = OSCCONbits.POST << 1;  // (0, 4, 16, 64)
        return _sysclock_sysfreq >> div;
#else
        return _sysclock_sysfreq;
#endif
    }
    return 1;
}

/**
 * @brief Change the divisor of the busClock given as argument.
 * @param busClock id of the bus clock or ref clock (SYSCLOCK_CLOCK_REFCLK or
 * SYSCLOCK_CLOCK_PBCLK, SYSCLOCK_CLOCK_FRC)
 * @param div divisor to set
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t div)
{
#ifndef SYSCLOCK_NOPOST
    uint16_t udiv;
    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        if (div == 1)
        {
            udiv = 0b00;
        }
        else if (div == 4)
        {
            udiv = 0b01;
        }
        else if (div == 16)
        {
            udiv = 0b10;
        }
        else if (div == 64)
        {
            udiv = 0b11;
        }
        else
        {
            return -1;
        }
        OSCCONbits.POST = udiv;
        return 0;
    }
#endif

    return -1;  // bad index
}

/**
 * @brief Return the actual frequency of the clock source
 * @param source clock id to request
 * @return frequency of 'source' clock, 0 in case of disabled clock, -1 in case of error
 */
int32_t sysclock_sourceFreq(SYSCLOCK_SOURCE source)
{
    switch (source)
    {
        case SYSCLOCK_SRC_LPRC:
            return 512000;  // 512kHz LPRC

        case SYSCLOCK_SRC_SOSC:
            return _sysclock_sosc;  // external secondary oscillator

        case SYSCLOCK_SRC_POSC:
            return _sysclock_posc;  // external primary oscillator

        case SYSCLOCK_SRC_FRC:
            return 8000000;  // FRC  // TODO integrate OSCTUNE

#ifdef SYSCLOCK_SRC_PLL
        case SYSCLOCK_SRC_PLL:
            return _sysclock_pll;  // FRC  // TODO integrate OSCTUNE
#endif
    }
    return -1;
}

/**
 * @brief Change a frequency of a source if it can be modified
 * @param source clock id to change
 * @return 0 in case of success, -1 in case of error
 */
int sysclock_setSourceFreq(SYSCLOCK_SOURCE source, uint32_t freq)
{
    if (source == SYSCLOCK_SRC_SOSC)
    {
        _sysclock_sosc = freq;
        return 0;
    }
    if (source == SYSCLOCK_SRC_POSC)
    {
        _sysclock_posc = freq;
        return 0;
    }
    return -1;
}

/**
 * @brief Return the actual clock source for system clock
 * @return SYSCLOCK_SOURCE enum corresponding to actual clock source
 */
SYSCLOCK_SOURCE sysclock_source(void)
{
    SYSCLOCK_SOURCE source = (SYSCLOCK_SOURCE)OSCCONbits.COSC;
    return source;
}

/**
 * @brief Switch the source clock of sysclock to another one and wait for the change effective
 * @param source id to switch to
 * @return 0 if ok, -1 in case of error
 */
int sysclock_switchSourceTo(SYSCLOCK_SOURCE source)
{
    // TODO implement me
    return -1;
}

int sysclock_setClock(uint32_t freq)
{
    // TODO implement me
    return -1;
}
