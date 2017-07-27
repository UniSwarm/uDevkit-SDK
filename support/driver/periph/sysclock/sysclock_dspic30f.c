/**
 * @file sysclock_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 11, 2016, 05:12 PM
 *
 * @brief System clock support for rtprog for dsPIC30F
 *
 * Implementation based on Microchip documents DS70054E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70054e.pdf
 */

#include "sysclock.h"

#include <stdint.h>

#include <archi.h>

#include "board.h"

uint32_t sysfreq;

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
    // TODO implement me
    return 0;
}

/**
 * @brief Gets the actual frequency on a particular peripherical bus clock
 * @param busClock id of the bus clock (1 periph bus clock), 0 for sysclock
 * @return bus frequency in Hz
 */
uint32_t sysclock_periphFreq(SYSCLOCK_CLOCK busClock)
{
    return sysfreq >> 1;
}