/**
 * @file pic32mzda.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date July 11, 2017, 19:35 PM
 *
 * @brief Architecture low level definitions for PIC32MZDA
 */

#include <archi.h>

void archi_init(void)
{
    // Prefetch-cache: Enable prefetch for PFM (any PFM instructions or data)
    PRECONbits.PREFEN = 3;
    // Flash PM Wait States: MZ Flash runs at 2 wait states @ 200 MHz
    PRECONbits.PFMWS = 2;

    // enable multiple vector interrupts
    INTCONSET = _INTCON_MVEC_MASK;
    PRISS = 0x76543210;
    enable_interrupt();
}
