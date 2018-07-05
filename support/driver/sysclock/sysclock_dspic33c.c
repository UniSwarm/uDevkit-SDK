/**
 * @file sysclock_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2018
 *
 * @date May 28, 2018, 02:28 PM
 *
 * @brief System clock support for udevkit for dsPIC33CH, dsPIC33CK
 *
 * Implementation based on Microchip documents DS70005255B and DS2070005319B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Oscillator-Module-with-High-Speed-PLL-70005255b.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33CH128MP5%20Datasheet%2070005319b.pdf
 */

#include "sysclock.h"

#include <archi.h>

#include <stdio.h>

uint32_t sysclock_sysfreq = 0;
uint32_t sysclock_posc = 0;
uint32_t sysclock_pll = 0;

/**
 * @brief Gets the actual frequency on a particular peripheral bus clock
 * @param busClock id of the bus clock (1 periph bus clock), 0 for sysclock
 * @return bus frequency in Hz, 1 in case of error to not cause divide by 0
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    if (sysclock_sysfreq == 0)
        sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());

    if (busClock == SYSCLOCK_CLOCK_SYSCLK)
        return sysclock_sysfreq >> 1;

    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        uint16_t div = 1;
        if (CLKDIVbits.DOZEN == 1)
            div = 1 << (CLKDIVbits.DOZE);
        return (sysclock_sysfreq >> 1) / div;
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
    uint16_t udiv;
#ifndef SYSCLOCK_HAVENO_FRCDIV
    if (busClock == SYSCLOCK_CLOCK_FRC)
    {
        if (div > 256)
            return -1;
        if (div == 256)
            udiv = 8;
        else
            for (udiv=0; div!=0; udiv++)
                div >>= 1;
        udiv -= 1;
        CLKDIVbits.FRCDIV = udiv;
        return 0;
    }
#endif
#ifdef SYSCLOCK_HAVE_REFCLOCKO
    if (busClock == SYSCLOCK_CLOCK_REFCLK)
    {
        if (div > 32768)
            return -1;
        else
            for (udiv=0; div!=0; udiv++)
                div >>= 1;
        udiv -= 1;
        REFOCONbits.RODIV = udiv;
        return 0;
    }
#endif
    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        if (div == 1)
            CLKDIVbits.DOZEN = 0;
        else
        {
            if (div > 128)
                return -1;
            for (udiv=0; div!=0; udiv++)
                div >>= 1;
            udiv -= 1;
            CLKDIVbits.DOZE = udiv;
            CLKDIVbits.DOZEN = 1;
        }
        return 0;
    }

    return -1;   // bad index
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
        freq = LPRC_BASE_FREQ; // 32kHz LPRC
        break;

    case SYSCLOCK_SRC_POSC:
        freq = sysclock_posc;   // external primary oscillator
        break;

    case SYSCLOCK_SRC_PPLL:
        freq = sysclock_pll;    // primary oscillator with PLL
        break;

    case SYSCLOCK_SRC_BFRC:
        freq = BFRC_BASE_FREQ;  // Backup FRC
        break;

    case SYSCLOCK_SRC_FRC:
    case SYSCLOCK_SRC_FRCDIV:
        osctune = OSCTUN;
        if (osctune >= 32)
            osctune = (osctune | 0xFFFFFFE0);
        freq = FRC_BASE_FREQ + osctune * OSCTUN_D;  // FRC

        if (source == SYSCLOCK_SRC_FRCDIV)
        {
#ifndef SYSCLOCK_HAVENO_FRCDIV
            div = CLKDIVbits.FRCDIV;
#else
            div = 1 << CLKDIVbits.RCDIV;
#endif
            if (div != 0b111)
                div = 1 << div;
            else
                div = 256;

            freq = freq / div; // FRC / div
        }
        break;

    case SYSCLOCK_SRC_FRCPLL:
        freq = sysclock_pll;  // FRC with PLL
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
SYSCLOCK_SOURCE sysclock_source()
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
        return -1; // Clocks and PLL are locked, source cannot be changed

    // disable interrupts
    disable_interrupt();

    // unlock clock config (OSCCON is write protected)
    //unlockClockConfig();

    // select the new source
    __builtin_write_OSCCONH(source); // primariry osc input

    // trigger change
    __builtin_write_OSCCONL(OSCCON | 0x01);
    nop();
    nop();

    // relock clock config
    //lockClockConfig();

    while (OSCCONbits.OSWEN == 1)
        nop();

    // enable interrupts
    enable_interrupt();

    if (sysclock_source() != source)
        return -3; // Error when switch clock source

    sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());

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
    if (sysclock_posc == 0)
    {
        OSCTUN = 0; // ==> Fin = 8 MHz Internal clock
        return sysclock_setPLLClock(fosc, SYSCLOCK_SRC_FRC);
    }
    else
    {
        return sysclock_setPLLClock(fosc, SYSCLOCK_SRC_POSC);
    }
}

/**
 * @brief Internal function to set clock with PLL from XTAL or FRC
 * @param fosc desirate system frequency in Hz
 * @param src input source clock of PLL (SYSCLOCK_SRC_FRC or SYSCLOCK_SRC_POSC)
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setPLLClock(uint32_t fosc, uint8_t src)
{
    return 0;
}
