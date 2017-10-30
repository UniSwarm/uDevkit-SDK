/**
 * @file sysclock_pic32mz_mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date March 01, 2016, 22:10 PM
 *
 * @brief System clock support for rtprog for PIC32MZ family (DA, EC and EF)
 * and PIC32MK
 *
 * Implementation based on Microchip document DS60001250B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001250B.pdf
 */

#include "sysclock.h"

#include <archi.h>
#include "board.h"

uint32_t sysclock_sysfreq = 0;
uint32_t sysclock_sosc = 0;
uint32_t sysclock_posc = 0;
uint32_t sysclock_pll = 0;
#if defined(ARCHI_pic32mk)
uint32_t sysclock_upll = 0;
#endif

/**
 * @brief Gets the actual frequency on a particular peripherical bus clock
 * @param busClock id of the bus clock (1 to 8 for PBCLK1 to PBCLK8), 0 for sysclock
 * @return bus frequency in Hz
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    volatile uint32_t* divisorAddr;
    uint8_t divisor;
    
    if (sysclock_sysfreq == 0)
        sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());
    
    if (busClock == SYSCLOCK_CLOCK_SYSCLK)
        return sysclock_sysfreq;
    if (busClock > SYSCLOCK_CLOCK_PBCLK8)
        return 1; // error, not return 0 to avoid divide by zero
    divisorAddr = &PB1DIV + (((uint8_t)busClock - 1) << 2);
    divisor = ((*divisorAddr) & 0x0000007F) + 1;
    return sysclock_sysfreq / divisor;
}

/**
 * @brief Change the divisor of the busClock given as argument. This can take up to 60
 * CPU cycles.
 * @param busClock id of the bus clock (1 to 8 for PBCLK1 to PBCLK8)
 * @param div divisor to set
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t div)
{
    volatile uint32_t* divisorAddr;

    if (OSCCONbits.CLKLOCK == 1)
        return -1; // Clocks and PLL are locked, source cannot be changed
    if (busClock == SYSCLOCK_CLOCK_SYSCLK) // cannot change sysclock
        return -1;
    if (busClock > SYSCLOCK_CLOCK_PBCLK8)  // bad index
        return -1;
    if (div == 0 || div > 128)
        return -1; // bad divisor value

    // get divisor bus value
    divisorAddr = &PB1DIV + (((uint8_t)busClock - 1) << 2);

    // wait for divisor can be changed
    while((*divisorAddr & _PB1DIV_PBDIVRDY_MASK) == 0)
        nop();

    // critical section, protected by lock on clock config
    unlockClockConfig();
    *divisorAddr = (*divisorAddr & 0xFFFFFF80) + (div - 1);
    lockClockConfig();

    // wait for divisor setted
    while ((*divisorAddr & _PB1DIV_PBDIVRDY_MASK) == 0)
        nop();

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
#if defined(ARCHI_pic32mzda) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef)
    case SYSCLOCK_SRC_BFRC:
        freq = 8000000;         // 8MHz BFRC hardware automatic selection
        break;
    case SYSCLOCK_SRC_FRC2:
#endif

    case SYSCLOCK_SRC_FRC:
        div = OSCCONbits.FRCDIV;
        if (div != 0b111)
            div = 1 << div;
        else
            div = 256;

        osctune = OSCTUN;
        if (osctune >= 32)
            osctune = (osctune | 0xFFFFFFE0);

        freq = (8000000 + osctune * 31250) / div; // 8MHz typical FRC, tuned by OSCTUN (+/- 12.5%), divided by FRCDIV
        break;

    case SYSCLOCK_SRC_LPRC:
        freq = 32000;         // 32kHz LPRC
        break;

    case SYSCLOCK_SRC_SOSC:
        freq = sysclock_sosc; // external secondary oscillator
        break;

    case SYSCLOCK_SRC_POSC:
        freq = sysclock_posc; // external primary oscillator
        break;

    case SYSCLOCK_SRC_SPLL:
        if (sysclock_pll == 0)
            sysclock_pll = sysclock_getPLLClock();
        freq = sysclock_pll;  // PLL out freq
        break;

#if defined(ARCHI_pic32mk)
    case SYSCLOCK_SRC_UPLL:
        freq = sysclock_upll; // USB PLL out freq
        break;
#endif
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
SYSCLOCK_SOURCE sysclock_source()
{
    SYSCLOCK_SOURCE source = (SYSCLOCK_SOURCE)OSCCONbits.COSC;
#ifdef SYSCLOCK_SRC_FRC2
    if (source == SYSCLOCK_SRC_FRC2)
        return SYSCLOCK_SRC_FRC;
#endif
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

    sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());

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
    uint32_t fin, fpllo;
    uint16_t prediv, multiplier, postdiv;

    if (sysclock_source() == SYSCLOCK_SRC_SPLL)
        return -1; // cannot change PLL when it is used

    if (fosc > SYSCLOCK_FOSC_MAX)
        return -1; // cannot generate fosc > SYSCLOCK_FOSC_MAX

#ifdef SYSCLOCK_SRC_FRC2
    if (src == SYSCLOCK_SRC_FRC2 || src == SYSCLOCK_SRC_FRC)
#else
    if (src == SYSCLOCK_SRC_FRC)
#endif
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_FRC);
        SPLLCONbits.PLLICLK = 1; // FRC as input
    }
    else if (src == SYSCLOCK_SRC_POSC)
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_POSC);
        SPLLCONbits.PLLICLK = 0; // POSC as input
    }
    else
    {
        return -1; // source can be only FRC or POSC
    }

    // post div
    postdiv = 32;
    while (fosc * postdiv > SYSCLOCK_FVCO_MAX && postdiv >= 2)
        postdiv = postdiv >> 1;
    if (postdiv < 2)
        return -1;
    fpllo = fosc * postdiv;

    // multiplier
    multiplier = 1;

    // pre divisor
    for (prediv = 1; prediv <= 8; prediv++)
    {
        multiplier = fpllo / (fin / prediv);
    }

    sysclock_pll = 0;

    return 0;
}

uint32_t sysclock_getPLLClock()
{
    uint32_t fin, fpllo;
    uint16_t prediv, multiplier, postdiv;

    if (SPLLCONbits.PLLICLK == 1) // FRC as input
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_FRC);
    }
    else
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_POSC);
    }
    
    prediv = SPLLCONbits.PLLIDIV + 1;
    multiplier = SPLLCONbits.PLLMULT + 1;
    postdiv = 1 << (SPLLCONbits.PLLODIV);
    
    fpllo = fin / prediv * multiplier / postdiv;
    return fpllo;
}
