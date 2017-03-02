/**
 * @file sysclock_pic32mz.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date March 01, 2016, 22:10 PM
 *
 * @brief System clock support for rtprog for PIC32MZ family (DA, EC and EF)
 */

#include "sysclock.h"


#include <xc.h>

uint32_t sysclock_sysfreq = 200000000;

uint32_t sysclock_getPeriphClock(uint8_t busClock)
{
    volatile uint32_t* divisorAddr;
    uint8_t divisor;
    if(busClock == SYSCLOCK_CLOCK_SYSCLK)
        return sysclock_sysfreq;
    if(busClock > SYSCLOCK_CLOCK_PBCLK8)
        return 1; // error, not return 0 to avoid divide by zero
    divisorAddr = &PB1DIV + ((busClock - 1) << 8);
    divisor = (*divisorAddr) & 0x000000FF;
    return sysclock_sysfreq / divisor;
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
    /*uint32_t fin, fplli, fsys;
    uint16_t multiplier;
    uint16_t prediv, postdiv;

    uint8_t frc_mode;

    if (fosc > SYSCLOCK_FOSC_MAX)
        return -1; // cannot generate fosc > SYSCLOCK_FOSC_MAX

    if (fosc < SYSCLOCK_FSYS_MIN / 8)
        return -1; // cannot generate fosc < SYSCLOCK_FSYS_MIN / 8

#ifndef SYSCLOCK_XTAL
    OSCTUN = 23; // ==> Fin = 8 MHz Internal clock
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

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);

    sysclock_sysfreq = fplli * multiplier / postdiv; // Complete this
*/
    return 0;
}

/**
 * @brief Gets system frequency in Hz
 * @return system frequency in Hz
 */
uint32_t sysclock_getClock()
{
    return sysclock_sysfreq;
}

/**
 * @brief Gets CPU clock frequency in Hz
 * @return system frequency in Hz
 */
uint32_t sysclock_getCPUClock()
{
    return sysclock_sysfreq >> 1;
}

