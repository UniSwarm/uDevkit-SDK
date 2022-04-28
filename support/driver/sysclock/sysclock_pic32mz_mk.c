/**
 * @file sysclock_pic32mz_mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date March 01, 2016, 22:10 PM
 *
 * @brief System clock support for udevkit for PIC32MZ family (DA, EC and EF)
 * and PIC32MK
 *
 * Implementation based on Microchip document DS60001250B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001250B.pdf
 */

#include "sysclock.h"

#include "board.h"
#include <archi.h>

static uint32_t _sysclock_sysfreq = 0;
static uint32_t _sysclock_sosc = 0;
static uint32_t _sysclock_posc = 0;
static uint32_t _sysclock_pll = 0;
#if defined(ARCHI_pic32mk)
static uint32_t _sysclock_upll = 0;
#endif

/**
 * @brief Gets the actual frequency on a particular peripheral bus clock
 * @param busClock id of the bus clock (1 to 8 for PBCLK1 to PBCLK8), 0 for sysclock
 * @return bus frequency in Hz
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

    if (busClock > SYSCLOCK_CLOCK_REFCLOCK4)
    {
        return 1;  // error, not return 0 to avoid divide by zero
    }

    if (busClock <= SYSCLOCK_CLOCK_PBCLK8)
    {
        // Peripheral bus divider
        volatile uint32_t *divisorAddr = &PB1DIV + (((uint8_t)busClock - SYSCLOCK_CLOCK_PBCLK1) << 2);
        uint8_t divisor = ((*divisorAddr) & 0x0000007F) + 1;
        return _sysclock_sysfreq / divisor;
    }
    else
    {
        // Ref clock divider
        volatile uint32_t *refClockConAddr = &REFO1CON + (((uint8_t)busClock - SYSCLOCK_CLOCK_REFCLOCK1) << 3);
        volatile uint32_t *refClockTrimAddr = &REFO1TRIM + (((uint8_t)busClock - SYSCLOCK_CLOCK_REFCLOCK1) << 3);
        uint32_t divisorInt = *refClockConAddr >> 16;
        uint32_t divisorTrim = *refClockTrimAddr >> 23;
        float divisor = divisorInt * 2 + ((float)divisorTrim * 2) / 512.0;
        if (divisorInt == 0)
        {
            divisor = 1;
        }
        uint32_t sourceFreq;
        switch (*refClockConAddr & 0x0000000F)
        {
            case SYSCLOCK_REFCLK_SRC_REFCLKI:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_SPLL:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_UPLL:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_SOSC:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_LPRC:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_FRC:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_POSC:
                sourceFreq = 0;
                break;

            case SYSCLOCK_REFCLK_SRC_PBCLK1:
                sourceFreq = sysclock_periphFreq(SYSCLOCK_CLOCK_PBCLK1);
                break;

            case SYSCLOCK_REFCLK_SRC_SYSCLOCK:
                sourceFreq = _sysclock_sysfreq;
                break;
        }
        return (uint32_t)((float)sourceFreq / divisor);
    }
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
    volatile uint32_t *divisorAddr;

    if (OSCCONbits.CLKLOCK == 1)
    {
        return -1;  // Clocks and PLL are locked, source cannot be changed
    }
    if (busClock == SYSCLOCK_CLOCK_SYSCLK)  // cannot change sysclock
    {
        return -1;
    }
    if (busClock > SYSCLOCK_CLOCK_PBCLK8)  // bad index
    {
        return -1;
    }
    if (div == 0 || div > 128)
    {
        return -1;  // bad divisor value
    }

    // get divisor bus value
    divisorAddr = &PB1DIV + (((uint8_t)busClock - 1) << 2);

    // wait for divisor can be changed
    while ((*divisorAddr & _PB1DIV_PBDIVRDY_MASK) == 0)
    {
        nop();
    }

    // critical section, protected by lock on clock config
    unlockClockConfig();
    *divisorAddr = (*divisorAddr & 0xFFFFFF80) + (div - 1);
    lockClockConfig();

    // wait for divisor setted
    while ((*divisorAddr & _PB1DIV_PBDIVRDY_MASK) == 0)
    {
        nop();
    }

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
            freq = 8000000;  // 8MHz BFRC hardware automatic selection
            break;

        case SYSCLOCK_SRC_FRC2:
#endif

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

            freq = (8000000 + osctune * 31250) / div;  // 8MHz typ FRC, tuned by OSCTUN (+/- 12.5%), divided by FRCDIV
            break;

        case SYSCLOCK_SRC_LPRC:
            freq = 32000;  // 32kHz LPRC
            break;

        case SYSCLOCK_SRC_SOSC:
            freq = _sysclock_sosc;  // external secondary oscillator
            break;

        case SYSCLOCK_SRC_POSC:
            freq = _sysclock_posc;  // external primary oscillator
            break;

        case SYSCLOCK_SRC_SPLL:
            if (_sysclock_pll == 0)
            {
                _sysclock_pll = sysclock_getPLLClock();
            }
            freq = _sysclock_pll;  // PLL out freq
            break;

#if defined(ARCHI_pic32mk)
        case SYSCLOCK_SRC_UPLL:
            freq = _sysclock_upll;  // USB PLL out freq
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
#ifdef SYSCLOCK_SRC_FRC2
    if (source == SYSCLOCK_SRC_FRC2)
    {
        return SYSCLOCK_SRC_FRC;
    }
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
    {
        return -1;  // Clocks and PLL are locked, source cannot be changed
    }

#ifdef SYSCLOCK_SRC_BFRC
    if (source == SYSCLOCK_SRC_BFRC)
    {
        return -2;  // cannot switch to backup FRC
    }
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
    {
        nop();
    }

    // enable interrupts
    enable_interrupt();

    if (sysclock_source() != source)
    {
        return -3;  // Error when switch clock source
    }

    _sysclock_sysfreq = sysclock_sourceFreq(sysclock_source());

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
    uint16_t prediv = 1, multiplier = 1;
    uint8_t postdiv, postdivBits;
    uint16_t mprediv, mmultiplier;
    int32_t merror, error;
    uint8_t inputBit;

    if (sysclock_source() == SYSCLOCK_SRC_SPLL)
    {
        return -1;  // cannot change PLL when it is used
    }

    if (fosc > SYSCLOCK_FOSC_MAX)
    {
        return -1;  // cannot generate fosc > SYSCLOCK_FOSC_MAX
    }

#ifdef SYSCLOCK_SRC_FRC2
    if (src == SYSCLOCK_SRC_FRC2 || src == SYSCLOCK_SRC_FRC)
#else
    if (src == SYSCLOCK_SRC_FRC)
#endif
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_FRC);
        inputBit = 1;  // FRC as input
    }
    else if (src == SYSCLOCK_SRC_POSC)
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_POSC);
        inputBit = 0;  // POSC as input
    }
    else
    {
        return -1;  // source can be only FRC or POSC
    }

    // post div
    postdiv = 32;
    postdivBits = 0b101;
    while (fosc * postdiv > SYSCLOCK_FVCO_MAX && postdiv >= 2)
    {
        postdiv = postdiv >> 1;
        postdivBits--;
    }
    if (postdiv < 2)
    {
        return -1;
    }
    fpllo = fosc * postdiv;

    // best pre divisor and multiplier computation
    error = 0x7FFFFFFF;
    for (mprediv = 1; mprediv <= 8; mprediv++)
    {
        mmultiplier = fpllo / (fin / mprediv);
        merror = fin / mprediv * mmultiplier / postdiv - fpllo;
        if (merror < 0)
        {
            merror = -merror;
        }
        if (merror < error && mmultiplier <= 128)
        {
            prediv = mprediv;
            multiplier = mmultiplier;
            error = merror;
        }
    }

    // set prediv, post and multiplier in bits
    disable_interrupt();
    unlockClockConfig();  // unlock clock config (OSCCON is write protected)
    SPLLCONbits.PLLICLK = inputBit;
    SPLLCONbits.PLLODIV = postdivBits;
    SPLLCONbits.PLLMULT = multiplier - 1;
    SPLLCONbits.PLLIDIV = prediv - 1;
    lockClockConfig();
    enable_interrupt();

    _sysclock_pll = sysclock_getPLLClock();

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
    return sysclock_setPLLClock(fosc, SYSCLOCK_SRC_POSC);
    /*_sysclock_sysfreq = fosc;
    return 0;*/
}

uint32_t sysclock_getPLLClock(void)
{
    uint32_t fin, fpllo;
    uint16_t prediv, multiplier, postdiv;

    if (SPLLCONbits.PLLICLK == 1)  // FRC as input
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
