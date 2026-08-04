/**
 * @file dma_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2026
 *
 * @date September 16, 2021, 09:55 PM
 *
 * @brief DMA support driver for PIC24FJ and dsPIC33C
 *
 * Implementation based on Microchip document DS30009742C:
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM,-Direct-Memory-Access-Controller-(DMA)-DS30009742C.pdf
 */

#include "dma.h"

#include <archi.h>

void dma_init(uint16_t addrLow, uint16_t addrHigh)
{
    DMACONbits.DMAEN = 1;
    DMACONbits.PRSSEL = 1;  // Round-robin scheme
    // DMACONbits.PRSSEL = 0; // Fixed priority scheme
    DMAL = addrLow;
    DMAH = addrHigh;
}
