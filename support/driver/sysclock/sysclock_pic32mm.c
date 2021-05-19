/**
 * @file sysclock_pic32mm.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date July 11, 2017, 18:30 PM
 *
 * @brief System clock support for udevkit for PIC32MM family
 *
 * Implementation based on Microchip document DS60001329B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001329b.pdf
 */

#include "sysclock.h"

#include "board.h"
#include <archi.h>

uint32_t sysclock_sysfreq = 0;
uint32_t sysclock_sosc = 0;
uint32_t sysclock_posc = 0;
uint32_t sysclock_pll = 0;

/**
 * @brief Gets the actual frequency on a particular peripheral bus clock
 * @param busClock id of the bus clock
 * @return bus frequency in Hz
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    if (sysclock_sysfreq == 0)
    {
        sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());
    }

    if (busClock == SYSCLOCK_CLOCK_SYSCLK || busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        return sysclock_sysfreq;
    }

    if (busClock == SYSCLOCK_CLOCK_REFCLK)
    {
        return 1;  // TODO implement me (refclock computation)
    }
    return 1;
}

/**
 * @brief Change the divisor of the busClock given as argument. This can take up to 60
 * CPU cycles.
 * @param busClock id of the bus clock (SYSCLOCK_CLOCK_REFCLK)
 * @param div divisor to set
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t div)
{
    if (busClock != SYSCLOCK_CLOCK_REFCLK)  // bad index
    {
        return -1;
    }

    // TODO implement me

    return 0;
}

/**
 * @brief Return the actual frequency of the clock source
 * @param source clock id to request
 * @return frequency of 'source' clock, 0 in case of disabled clock, -1 in case of error
 */
int32_t sysclock_sourceFreq(SYSCLOCK_SOURCE source)
{
    int32_t freq = -1;
    uint16_t div;
    int32_t osctune;
    switch (source)
    {
        case SYSCLOCK_SRC_LPRC:
            freq = 32000;  // 32kHz LPRC
            break;

        case SYSCLOCK_SRC_SOSC:
            freq = sysclock_sosc;  // external secondary oscillator
            break;

        case SYSCLOCK_SRC_POSC:
            freq = sysclock_posc;  // external primary oscillator
            break;

        case SYSCLOCK_SRC_SPLL:
            freq = sysclock_pll;  // PLL out freq
            break;

        case SYSCLOCK_SRC_FRC:
            div = OSCCONbits.FRCDIV;
            if (div != 0b111)
            {
                div = 1 << div;
            }
            else
            {
                div = 256;
            }

            osctune = OSCTUN;
            if (osctune >= 32)
            {
                osctune = (osctune | 0xFFFFFFE0);
            }

            freq = (8000000 + osctune * 3750) / div;  // 8MHz typical FRC, tuned by OSCTUN (+/- 1.5%), divided by FRCDIV
            break;
    }
    return freq;
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
        sysclock_sosc = freq;
        return 0;
    }
    if (source == SYSCLOCK_SRC_POSC)
    {
        sysclock_posc = freq;
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
    if (OSCCONbits.CLKLOCK == 1)
    {
        return -1;  // Clocks and PLL are locked, source cannot be changed
    }

    // disable interrupts
    disable_interrupt();

    // unlock clock config (OSCCON is write protected)
    unlockClockConfig();

    // select the new source
    OSCCONbits.NOSC = source;

    // trigger change
    OSCCONSET = _OSCCON_OSWEN_MASK;
    nop();
    nop();

    // relock clock config
    lockClockConfig();

    while (OSCCONbits.OSWEN == 1)
    {
        nop();
    }

    // enable interrupts
    enable_interrupt();

    if (sysclock_source() != source)
    {
        return -3;  // Error when switch clock source
    }

    return 0;
}

/**
 * @brief Sets the system clock of the CPU, the system clock may be different of CPU
 * clock and peripheral clock
 * @param fosc desirate system frequency in Hz
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClock(uint32_t fosc)
{
    // return sysclock_setClockWPLL(fosc);
    sysclock_sysfreq = fosc;
    return 0;
}

/**
 * @brief Internal function to set clock with PLL from XTAL or FRC
 * @param fosc desirate system frequency in Hz
 * @param src input source clock of PLL (SYSCLOCK_SRC_FRC or SYSCLOCK_SRC_POSC)
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setPLLClock(uint32_t fosc, uint8_t src)
{
    // TODO implement me
    return 0;
}
