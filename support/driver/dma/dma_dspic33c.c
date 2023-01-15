/**
 * @file dma_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2023
 *
 * @date September 16, 2021, 09:55 PM
 *
 * @brief DMA support driver for PIC24 and dsPIC33C
 */

#include "dma.h"

#include <archi.h>

void dma_init(uint16_t addrLow, uint16_t addrHigh)
{
    DMACONbits.PRSSEL = 1;  // Round-robin scheme
    // DMACONbits.PRSSEL = 0; // Fixed priority scheme
    DMAL = addrLow;
    DMAH = addrHigh;
}
