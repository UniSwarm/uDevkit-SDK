/**
 * @file sysclock_pic24_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip documents DS70186D, DS70580C, DS70005131A,
 * DS70307E and DS70216D :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70216D.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70580C.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005131a.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70307E.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70216D.pdf
 *
 * Simple PLL devices: DS70644A
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/S52.pdf
 */

#include "sysclock.h"

#include <stdint.h>

#include <archi.h>

#include "board.h"

uint32_t sysclock_sysfreq = 80000000;
uint32_t sysclock_sosc = 0;
uint32_t sysclock_posc = 0;
uint32_t sysclock_pllMultiplier = 1; // TODO review this

/**
 * @brief Gets the actual frequency on a particular peripherical bus clock
 * @param busClock id of the bus clock (1 periph bus clock), 0 for sysclock
 * @return bus frequency in Hz, 1 in case of error to not cause divide by 0
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
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
    switch (source)
    {
    case SYSCLOCK_SRC_LPRC:
        return 32000;         // 32kHz LPRC
    case SYSCLOCK_SRC_SOSC:
        return sysclock_sosc; // external secondary oscilator
    case SYSCLOCK_SRC_POSC:
        return sysclock_posc; // external primary oscilator
    case SYSCLOCK_SRC_PPLL:
        return sysclock_posc * sysclock_pllMultiplier;  // primary oscilator with PLL
    case SYSCLOCK_SRC_FRC:
        return 8000000;       // FRC  // TODO integrate OSCTUNE
    case SYSCLOCK_SRC_FRC16:
        return 8000000 / 16;  // FRC /16  // TODO integrate OSCTUNE
    case SYSCLOCK_SRC_FRCDIV:
        {
            uint16_t div = CLKDIVbits.FRCDIV;
            if (div != 0b111)
                div = 1 << div;
            else
                div = 256;

            return 8000000 / div; // 8MHz FRC // TODO integrate OSCTUNE
        }
    case SYSCLOCK_SRC_FRCPLL:
        return 8000000 * sysclock_pllMultiplier;  // FRC with PLL  // TODO integrate OSCTUNE
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
    OSCCONbits.NOSC = source;

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

    return 0;
}

/**
 * @brief Sets the system clock of the CPU, the system clock may be different of CPU
 * clock and peripherical clock
 * @param fosc desirate system frequency in Hz
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClock(uint32_t fosc)
{
    return sysclock_setClockWPLL(fosc);
}

/**
 * @brief Internal function to set clock with PLL from XTAL or FRC
 * @param fosc desirate system frequency in Hz
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClockWPLL(uint32_t fosc)
{
    uint32_t fin, fplli, fsys;
    uint16_t multiplier;
    uint16_t prediv, postdiv;

    uint8_t frc_mode;

    if (fosc > SYSCLOCK_FOSC_MAX)
        return -1; // cannot generate fosc > SYSCLOCK_FOSC_MAX

    if (fosc < SYSCLOCK_FSYS_MIN / 8)
        return -1; // cannot generate fosc < SYSCLOCK_FSYS_MIN / 8

#ifndef SYSCLOCK_XTAL
    OSCTUN = 21; // ==> Fin = 8 MHz Internal clock
    fin = 8000000;
    frc_mode = 1;
#else
    fin = SYSCLOCK_XTAL;
    frc_mode = 0;
#endif

    // calculate post-diviser and fsys
    postdiv = 2;
    fsys = fosc << 1;
    if (fsys < SYSCLOCK_FSYS_MIN)
    {
        postdiv = 4;
        fsys = fosc << 2;
    }
    if (fsys < SYSCLOCK_FSYS_MIN)
    {
        postdiv = 8;
        fsys = fosc << 3;
    }

#ifndef SYSCLOCK_PLL4
    // calculate pre-diviser to ensure Fplli < SYSCLOCK_FPLLI_MAX
    prediv = (fin / (SYSCLOCK_FPLLI_MAX + 1)) + 1;
    if (prediv < SYSCLOCK_N1_MIN)
        prediv = SYSCLOCK_N1_MIN;
    fplli = fin / prediv;

    // calculate multiplier
    multiplier = fsys / fplli;

    // set post-diviser
    if (postdiv == 2)
        CLKDIVbits.PLLPOST = 0b00; // PLL post div = 2
    if (postdiv == 4)
        CLKDIVbits.PLLPOST = 0b01; // PLL post div = 4
    if (postdiv == 8)
        CLKDIVbits.PLLPOST = 0b11; // PLL post div = 8

    // set pre-diviser
    CLKDIVbits.PLLPRE = prediv - 2; // PLL pre div = 1

    //                         (PLLFBD + 2)
    // Fosc = Fin * ----------------------------------
    //              ((PLLPRE + 2) * 2 * (PLLPOST + 1))
    PLLFBD = multiplier - 2;

    if (frc_mode == 1)
    {
        __builtin_write_OSCCONH(0x01); // frc input
        __builtin_write_OSCCONL(OSCCON | 0x01);
    }
    else
    {
        __builtin_write_OSCCONH(0x03); // primariry osc input
        __builtin_write_OSCCONL(OSCCON | 0x01);
        // Wait for Clock switch to occur
        while (OSCCONbits.COSC != 0b011);
    }
#else
    prediv = 1;
    fplli = fin;
    multiplier = 4;
    postdiv = 1;
#endif

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);

    sysclock_sysfreq = fplli * multiplier / postdiv; // Complete this

    return 0;
}