/**
 * @file sysclock_dspic33a_pic32a.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025-2026
 *
 * @date May 31, 2025, 10:15 PM
 *
 * @brief System clock support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005539C, DS70005629C, DS70005591D and DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
 */

#include "sysclock.h"

#include <archi.h>

static uint32_t _sysclock_posc = 0;
static uint32_t _sysclock_pll1 = 0;
static uint32_t _sysclock_vco1 = 0;
static uint32_t _sysclock_pll2 = 0;
static uint32_t _sysclock_vco2 = 0;
static uint32_t _sysclock_refi1 = 0;
static uint32_t _sysclock_refi2 = 0;

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
            return LPRC_BASE_FREQ;

        case SYSCLOCK_SRC_POSC:
            return _sysclock_posc;

        case SYSCLOCK_SRC_PLL1_FOUT:
            if (_sysclock_pll1 == 0)
            {
                _sysclock_pll1 = sysclock_getPLLClock(0);
            }
            return _sysclock_pll1;

        case SYSCLOCK_SRC_PLL2_FOUT:
            if (_sysclock_pll2 == 0)
            {
                _sysclock_pll2 = sysclock_getPLLClock(1);
            }
            return _sysclock_pll2;

        case SYSCLOCK_SRC_PLL1_VCO_DIV:
            if (_sysclock_vco1 == 0)
            {
                sysclock_getPLLClock(0);
            }
            return _sysclock_vco1 / (VCO1DIVbits.INTDIV * 2);

        case SYSCLOCK_SRC_PLL2_VCO_DIV:
            if (_sysclock_vco2 == 0)
            {
                sysclock_getPLLClock(1);
            }
            return _sysclock_vco2 / (VCO2DIVbits.INTDIV * 2);

        case SYSCLOCK_SRC_REFI1:
            return _sysclock_refi1;

        case SYSCLOCK_SRC_REFI2:
            return _sysclock_refi2;

        case SYSCLOCK_SRC_BFRC:
            return BFRC_BASE_FREQ;

        case SYSCLOCK_SRC_FRC:
            return FRC_BASE_FREQ;

        default:
            return -1;
    }
}

int sysclock_setSourceFreq(SYSCLOCK_SOURCE source, uint32_t freq)
{
    switch (source)
    {
        case SYSCLOCK_SRC_POSC:
            _sysclock_posc = freq;
            return 0;

        case SYSCLOCK_SRC_REFI1:
            _sysclock_refi1 = freq;
            return 0;

        case SYSCLOCK_SRC_REFI2:
            _sysclock_refi2 = freq;
            return 0;

        default:
            return -1;
    }
}

uint32_t sysclock_clkgenFreq(uint8_t clkgen)
{
    if (clkgen >= SYSCLOCK_CLKGEN_MAX)
    {
        return 0;
    }

    volatile CLK1CONBITS *clkCon = &CLK1CONbits + clkgen * 2;
    volatile CLK1DIVBITS *clkDiv = &CLK1DIVbits + clkgen * 2;
    int32_t inputFreq = sysclock_sourceFreq(clkCon->COSC);
    int16_t divider = clkDiv->INTDIV * 2;
    int16_t fracDiv = clkDiv->FRACDIV;
    if (divider == 0)
    {
        return inputFreq;
    }
    if (fracDiv == 0)
    {
        return inputFreq / divider;
    }

    return (uint32_t)((float)inputFreq / ((float)divider + (float)fracDiv / 256.0));
}

/**
 * @brief Gets the actual frequency on a particular peripheral bus clock
 * @param busClock id of the bus clock (1 periph bus clock), 0 for sysclock
 * @return bus frequency in Hz, 1 in case of error to not cause divide by 0
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    if (busClock < SYSCLOCK_CLKGEN_MAX)
    {
        return sysclock_clkgenFreq((uint8_t)busClock);
    }
    switch (busClock)
    {
        case SYSCLOCK_CLOCK_FAST_PERIPH:
            return sysclock_clkgenFreq(SYSCLOCK_CLOCK_CLKGEN1);

        case SYSCLOCK_CLOCK_STD_PERIPH:
            return sysclock_clkgenFreq(SYSCLOCK_CLOCK_CLKGEN1) / 2;

        case SYSCLOCK_CLOCK_SLOW_PERIPH:
            return sysclock_clkgenFreq(SYSCLOCK_CLOCK_CLKGEN1) / 4;

        default:
            return 0;
    }
}

uint32_t sysclock_getPLLClock(uint8_t pllId)
{
    volatile PLL1CONBITS *pllCon = &PLL1CONbits;
    volatile PLL1DIVBITS *pllDiv = &PLL1DIVbits;
    if (pllId > 1)
    {
        return 0;
    }
    if (pllId == 1)
    {
        pllCon = (volatile PLL1CONBITS *)&PLL2CONbits;
        pllDiv = (volatile PLL1DIVBITS *)&PLL2DIVbits;
    }

    uint32_t fin = sysclock_sourceFreq(pllCon->COSC);

    uint16_t prediv = pllDiv->PLLPRE;
    uint16_t multiplier = pllDiv->PLLFBDIV;
    uint16_t postdiv = pllDiv->POSTDIV1 * pllDiv->POSTDIV2;

    _sysclock_vco1 = fin / prediv * multiplier;
    uint32_t fpllo = _sysclock_vco1 / postdiv;
    return fpllo;
}
