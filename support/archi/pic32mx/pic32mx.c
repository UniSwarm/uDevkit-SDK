/**
 * @file pic32mx.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date Jully 08, 2017, 09:35 AM
 *
 * @brief Architecture low level definitions for PIC32MX
 */

#include <archi.h>

void archi_init()
{
    // enable multiple vector interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    enable_interrupt();
}
