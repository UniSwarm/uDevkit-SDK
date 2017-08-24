/**
 * @file sysclock_pic32mx.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 12, 2017, 23:30 PM
 *
 * @brief System clock support for rtprog for PIC32MX family
 *
 * Implementation based on Microchip document DS61112H :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61112H.pdf
 */

#include "sysclock.h"

#include <archi.h>
#include "board.h"

uint32_t sysclock_sysfreq = 80000000;
uint32_t sysclock_sosc = 0;
uint32_t sysclock_posc = 0;
uint32_t sysclock_pllMultiplier = 1;

/**
 * @brief Gets the actual frequency on a particular peripherical bus clock
 * @param busClock id of the bus clock
 * @return bus frequency in Hz, 1 in case of error to not cause divide by 0
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    if (busClock == SYSCLOCK_CLOCK_SYSCLK)
        return sysclock_sysfreq;
    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        uint8_t div = OSCCONbits.PBDIV;
        div = 1 << div;
        return sysclock_sysfreq / div; // TODO
    }
    return 1;
}

/**
 * @brief Change the divisor of the busClock given as argument.
 * @param busClock id of the bus clock or ref clock (SYSCLOCK_CLOCK_REFCLK or
 * SYSCLOCK_CLOCK_PBCLK)
 * @param div divisor to set
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t div)
{
    // checks
    // TODO
    if (busClock != SYSCLOCK_CLOCK_REFCLK && busClock != SYSCLOCK_CLOCK_PBCLK)  // bad index
        return -1;

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
            uint16_t div = OSCCONbits.FRCDIV;
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

#ifdef SYSCLOCK_SRC_BFRC
    if (source == SYSCLOCK_SRC_BFRC)
        return -2; // cannot switch to backup FRC
#endif

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
    //return sysclock_setClockWPLL(fosc);
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

    // set sysclock_pllMultiplier

    return 0;
}
