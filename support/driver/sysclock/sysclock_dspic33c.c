/**
 * @file sysclock_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2022
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
#include <board.h>

#include <stdio.h>

static uint32_t _sysclock_sysfreq = 0;
static uint32_t _sysclock_posc = 0;
static uint32_t _sysclock_pllo = 0;
static uint32_t _sysclock_vco = 0;
static uint32_t _sysclock_avco = 0;

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

    switch (busClock)
    {
        case SYSCLOCK_CLOCK_FOSC:
            return _sysclock_sysfreq;

        case SYSCLOCK_CLOCK_PBCLK:
            return _sysclock_sysfreq >> 1;

        case SYSCLOCK_CLOCK_REFCLK:
        {
            uint16_t divisor = REFOCONHbits.RODIV << 1;
            return (_sysclock_sysfreq >> 1) / divisor;
        }

        case SYSCLOCK_CLOCK_SYSCLK:
        {
            uint16_t divisor = 1;
            if (CLKDIVbits.DOZEN == 1)
            {
                divisor = 1 << (CLKDIVbits.DOZE);
            }
            return (_sysclock_sysfreq >> 1) / divisor;
        }

        case SYSCLOCK_CLOCK_FRC:
            return sysclock_sourceFreq(SYSCLOCK_SRC_FRC);

        case SYSCLOCK_CLOCK_FPLLO:
            return _sysclock_pllo;

        case SYSCLOCK_CLOCK_VCO:
            return _sysclock_vco;

        case SYSCLOCK_CLOCK_VCO2:
            return _sysclock_vco >> 1;

        case SYSCLOCK_CLOCK_VCO3:
            return _sysclock_vco / 3;

        case SYSCLOCK_CLOCK_VCO4:
            return _sysclock_vco >> 2;

        case SYSCLOCK_CLOCK_AVCO:
            return _sysclock_avco;

        case SYSCLOCK_CLOCK_AVCO2:
            return _sysclock_avco >> 1;

        case SYSCLOCK_CLOCK_AVCO3:
            return _sysclock_avco / 3;

        case SYSCLOCK_CLOCK_AVCO4:
            return _sysclock_avco >> 2;
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
int sysclock_setClockDiv(SYSCLOCK_CLOCK busClock, uint16_t divisor)
{
    uint16_t udivisor = 0;
    if (busClock == SYSCLOCK_CLOCK_FRC)
    {
        if (divisor > 256)
        {
            return -1;
        }
        if (divisor == 256)
        {
            udivisor = 8;
        }
        else
        {
            for (udivisor = 0; divisor != 0; udivisor++)
            {
                divisor >>= 1;
            }
        }
        udivisor -= 1;
        CLKDIVbits.FRCDIV = udivisor;
        return 0;
    }
    if (busClock == SYSCLOCK_CLOCK_REFCLK)
    {
        udivisor >>= 1;
        REFOCONHbits.RODIV = udivisor;
        return 0;
    }
    if (busClock == SYSCLOCK_CLOCK_PBCLK)
    {
        if (divisor == 1)
        {
            CLKDIVbits.DOZEN = 0;
        }
        else
        {
            if (divisor > 128)
            {
                return -1;
            }
            for (udivisor = 0; divisor != 0; udivisor++)
            {
                divisor >>= 1;
            }
            udivisor -= 1;
            CLKDIVbits.DOZE = udivisor;
            CLKDIVbits.DOZEN = 1;
        }
        return 0;
    }

    return -1;  // bad index
}

/**
 * @brief Return the actual frequency of the clock source
 * @param source clock id to request
 * @return frequency of 'source' clock, 0 in case of disabled clock, -1 in case of error
 */
int32_t sysclock_sourceFreq(SYSCLOCK_SOURCE source)
{
    int32_t freq = -1;
    uint16_t divisor;
    switch (source)
    {
        case SYSCLOCK_SRC_LPRC:
            freq = LPRC_BASE_FREQ;  // 32kHz LPRC
            break;

        case SYSCLOCK_SRC_POSC:
            freq = _sysclock_posc;  // external primary oscillator
            break;

        case SYSCLOCK_SRC_PPLL:
        case SYSCLOCK_SRC_FRCPLL:
            freq = _sysclock_pllo >> 1;  // primary oscillator with PLL
            break;

        case SYSCLOCK_SRC_BFRC:
            freq = BFRC_BASE_FREQ;  // Backup FRC
            break;

        case SYSCLOCK_SRC_FRC:
        case SYSCLOCK_SRC_FRCDIV:
#ifdef SYSCLOCK_NO_OSCTUNE
            freq = FRC_BASE_FREQ;
#else
        {
            int32_t osctune = OSCTUN;
            if (osctune >= 32)
            {
                osctune = (osctune | 0xFFFFFFE0);
            }
            freq = FRC_BASE_FREQ + osctune * OSCTUN_D;  // FRC
        }
#endif

            if (source == SYSCLOCK_SRC_FRCDIV)
            {
                divisor = CLKDIVbits.FRCDIV;
                if (divisor != 0b111)
                {
                    divisor = 1 << divisor;
                }
                else
                {
                    divisor = 256;
                }

                freq = freq / divisor;  // FRC / divisor
            }
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
    if (OSCCONbits.CLKLOCK == 1)
    {
        return -1;  // Clocks and PLL are locked, source cannot be changed
    }

    // disable interrupts
    disable_interrupt();

    // unlock clock config (OSCCON is write protected)
    // unlockClockConfig();

    // select the new source
    __builtin_write_OSCCONH(source);  // primariry osc input

    // trigger change
    __builtin_write_OSCCONL(OSCCON | 0x01);
    nop();
    nop();

    // relock clock config
    // lockClockConfig();

    while (OSCCONbits.OSWEN == 1)
    {
        nop();
    }

    if (sysclock_source() != source)
    {
        return -3;  // Error when switch clock source
    }
    if (source == SYSCLOCK_SRC_FRCPLL || source == SYSCLOCK_SRC_PPLL)
    {
        // Wait for PLL to lock
        while (OSCCONbits.LOCK != 1)
        {
            ;
        }
        _sysclock_pllo = sysclock_getPLLClock();
    }

    _sysclock_sysfreq = sysclock_sourceFreq(source);

    // enable interrupts
    enable_interrupt();

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
    if (_sysclock_posc == 0)
    {
#ifndef SYSCLOCK_NO_OSCTUNE
        OSCTUN = 0;  // ==> Fin = 8 MHz Internal clock
#endif
        return sysclock_setPLLClock(fosc, SYSCLOCK_SRC_FRC);
    }
    else
    {
        return sysclock_setPLLClock(fosc, SYSCLOCK_SRC_POSC);
    }
}

/**
 * @brief Internal function to set clock with PLL from Primary oscilator (POSC) or FRC
 * @param fosc desirate system frequency in Hz
 * @param src input source clock of PLL (SYSCLOCK_SRC_FRC or SYSCLOCK_SRC_POSC)
 * @return 0 if ok, -1 in case of error
 */
int sysclock_setPLLClock(uint32_t fosc, uint8_t src)
{
    if (src != SYSCLOCK_SRC_FRC && src != SYSCLOCK_SRC_POSC)
    {
        return -4;
    }

    if (fosc > SYSCLOCK_FOSC_MAX)
    {
        return -1;  // cannot generate fosc > SYSCLOCK_FOSC_MAX
    }
    if (fosc < SYSCLOCK_FSYS_MIN / 8)
    {
        return -1;  // cannot generate fosc < SYSCLOCK_FSYS_MIN / 8
    }

    uint32_t fin = sysclock_sourceFreq(src);
    if (fin == 0)
    {
        return -1;
    }
    if (fin < SYSCLOCK_FPLLI_MIN)
    {
        return -2;
    }

    uint16_t prediv = fin / SYSCLOCK_FPLLI_MIN;
    uint32_t fplli = fin / prediv;
    if (fplli > SYSCLOCK_FPLLI_MAX)
    {
        return -2;
    }

    uint8_t postdiv1 = 0, postdiv2 = 0;
    uint16_t multiplier = 0;
    int32_t error = 0x7FFFFFFF;
    for (uint8_t mpostdiv1 = SYSCLOCK_POSTDIV1_MIN; mpostdiv1 <= SYSCLOCK_POSTDIV1_MAX; mpostdiv1++)
    {
        for (uint16_t mpostdiv2 = SYSCLOCK_POSTDIV2_MIN; mpostdiv2 <= mpostdiv1; mpostdiv2++)
        {
            uint16_t mmultiplier = (fosc * mpostdiv1 * mpostdiv2) / fplli;
            if (mmultiplier < SYSCLOCK_PLLM_MIN || mmultiplier > SYSCLOCK_PLLM_MAX)
            {
                continue;
            }
            uint32_t fvco = fplli * mmultiplier;
            if (fvco < SYSCLOCK_FVCO_MIN || fvco > SYSCLOCK_FVCO_MAX)
            {
                continue;
            }

            int32_t merror = fvco / (mpostdiv1 * mpostdiv2) - fosc;
            if (merror < 0)
            {
                merror = -merror;
            }
            if (merror < error && mmultiplier <= SYSCLOCK_PLLM_MAX && mmultiplier >= SYSCLOCK_PLLM_MIN)
            {
                multiplier = mmultiplier;
                error = merror;
                postdiv1 = mpostdiv1;
                postdiv2 = mpostdiv2;
                if (merror == 0)
                {
                    mpostdiv1 = SYSCLOCK_POSTDIV1_MAX + 1;
                    break;
                }
            }
        }
    }
    if (multiplier == 0)
    {
        return -5;
    }

    CLKDIVbits.PLLPRE = prediv;
    PLLFBDbits.PLLFBDIV = multiplier;
    PLLDIVbits.POST1DIV = postdiv1;
    PLLDIVbits.POST2DIV = postdiv2;

    if (src == SYSCLOCK_SRC_FRC)
    {
        __builtin_write_OSCCONH(SYSCLOCK_SRC_FRCPLL);  // frc input
    }
    else
    {
        __builtin_write_OSCCONH(SYSCLOCK_SRC_PPLL);  // primary osc input
    }
    __builtin_write_OSCCONL(OSCCON | 0x01);

    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0)
    {
        ;
    }
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1)
    {
        ;
    }

    _sysclock_pllo = sysclock_getPLLClock();
    _sysclock_sysfreq = _sysclock_pllo >> 1;

    return 0;
}

uint32_t sysclock_getPLLClock(void)
{
    uint32_t fin;
    if (OSCCONbits.COSC == SYSCLOCK_SRC_FRCPLL)  // FRC as input
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_FRC);
    }
    else if (OSCCONbits.COSC == SYSCLOCK_SRC_PPLL)  // POSC as input
    {
        fin = sysclock_sourceFreq(SYSCLOCK_SRC_POSC);
    }
    else
    {
        return 0;
    }

    uint16_t prediv = CLKDIVbits.PLLPRE;
    uint16_t multiplier = PLLFBDbits.PLLFBDIV;
    uint16_t postdiv = (PLLDIVbits.POST1DIV) * (PLLDIVbits.POST2DIV);

    _sysclock_vco = fin / prediv * multiplier;
    uint32_t fpllo = _sysclock_vco / postdiv;
    return fpllo;
}
