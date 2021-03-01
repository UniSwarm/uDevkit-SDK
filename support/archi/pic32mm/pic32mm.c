/**
 * @file pic32mm.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 10, 2017, 16:50 PM
 *
 * @brief Architecture low level definitions for PIC32MM
 */

#include <archi.h>

void archi_init(void)
{
    // enable multiple vector interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    PRISS = 0x11110000; // interrupts with priority >= 4 use shadow reg set 1,
                        // other shadows reg set 0
    enable_interrupt();
}
