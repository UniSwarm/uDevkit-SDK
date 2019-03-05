/**
 * @file msi_dspic33ch.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 2, 10:00 AM
 *
 * @brief Master Slave Interface driver for dsPIC33CH, slave part
 *
 * Implementation based on Microchip document DS70005278B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Master-Slave-Interface-MSI-Module-70005278b.pdf
 */

#include "msi.h"

#include <archi.h>

/**
 * @brief Gives the status of the master core
 * @return MSI_CORE_STATUS status enum
 */
 MSI_CORE_STATUS msi_slave_status()
{
    if (SI1STATbits.MSTRST)
        return MSI_CORE_STATUS_RESETED;

    switch (SI1STATbits.MSTPWR)
    {
    case 0b00:
        return MSI_CORE_STATUS_LOWPOWERRUN;
    case 0b01:
        return MSI_CORE_STATUS_STARTED;
    case 0b10:
        return MSI_CORE_STATUS_SLEEPED;
    }

    return MSI_CORE_STATUS_RESETED;
}
