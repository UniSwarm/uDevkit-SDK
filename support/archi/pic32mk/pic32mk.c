/**
 * @file pic32mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 10, 2017, 16:15 PM
 *
 * @brief Architecture low level definitions for PIC32MK
 */

#include <archi.h>

void archi_init()
{
    // enable multiple vector interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    PRISS = 0x11110000; // interrupts with priority >= 4 use shadow reg set 1,
                        // other shadows reg set 0
    enable_interrupt();
}

void archi_prefetch_enable()
{
    _mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, (_mfc0(_CP0_CONFIG, _CP0_CONFIG_SELECT) | 0x3));
}

void archi_prefetch_disable()
{
    _mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, ((_mfc0(_CP0_CONFIG, _CP0_CONFIG_SELECT) & 0xFFFFFFFC) | 0x2));
}
