/**
 * @file msi_dspic33ch.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date March 2, 10:00 AM
 *
 * @brief Master Slave Interface driver for dsPIC33CH, secondary part
 *
 * Implementation based on Microchip document DS70005278B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Master-Slave-Interface-MSI-Module-70005278b.pdf
 */

#include "msi.h"

#include <archi.h>

#include <string.h>

/**
 * @brief Gives the status of the master core
 * @return MSI_CORE_STATUS status enum
 */
MSI_CORE_STATUS msi_primary_status(void)
{
    if (SI1STATbits.MSTRST)
    {
        return MSI_CORE_STATUS_RESETED;
    }

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

int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(size);
    uint16_t writeU16[5];

    if (protocol == MSI_PROTOCOL_S2M)
    {
        if (_DTRDYB == 1)
        {
            return -1;
        }
        memcpy((void *)writeU16, (const void *)data, 10);
        SI1MBX5D = writeU16[0];
        SI1MBX6D = writeU16[1];
        SI1MBX7D = writeU16[2];
        SI1MBX8D = writeU16[3];
        SI1MBX9D = writeU16[4];
        return 0;
    }
    if (protocol == MSI_PROTOCOL_S2M2)
    {
        if (_DTRDYD == 1)
        {
            return -1;
        }
        memcpy((void *)writeU16, (const void *)data, 6);
        SI1MBX13D = writeU16[0];
        SI1MBX14D = writeU16[1];
        SI1MBX15D = writeU16[2];
        return 0;
    }
    return -1;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is full and can not be written, 1 if OK, -1 if protocol is not valid
 */
int msi_protocol_canWrite(const uint8_t protocol)
{
    if (protocol == MSI_PROTOCOL_S2M)
    {
        if (_DTRDYB == 1)  // MailBox is full
        {
            return 0;
        }
        return 1;
    }
    if (protocol == MSI_PROTOCOL_S2M2)
    {
        if (_DTRDYD == 1)  // MailBox is full
        {
            return 0;
        }
        return 1;
    }
    return -1;
}

int msi_protocol_read(const uint8_t protocol, unsigned char *data, uint8_t max_size)
{
    UDK_UNUSED(max_size);
    uint16_t readU16[5];

    if (protocol == MSI_PROTOCOL_M2S)
    {
        if (_DTRDYA == 0)
        {
            return -1;
        }
        uint16_t *ptr = readU16;
        *(ptr++) = SI1MBX0D;
        *(ptr++) = SI1MBX1D;
        *(ptr++) = SI1MBX2D;
        *(ptr++) = SI1MBX3D;
        *(ptr++) = SI1MBX4D;
        memcpy((void *)data, (void *)&readU16, 10);
        return 0;
    }

    if (protocol == MSI_PROTOCOL_M2S2)
    {
        if (_DTRDYC == 0)
        {
            return -1;
        }
        uint16_t *ptr = readU16;
        *(ptr++) = SI1MBX10D;
        *(ptr++) = SI1MBX11D;
        *(ptr++) = SI1MBX12D;
        memcpy((void *)data, (void *)&readU16, 6);
        return 0;
    }
    return -1;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is empty, 1 if OK to be read, -1 if protocol is not valid
 */
int msi_protocol_canRead(const uint8_t protocol)
{
    if (protocol == MSI_PROTOCOL_M2S)
    {
        if (_DTRDYA == 0)  // MailBox is empty
        {
            return 0;
        }
        return 1;
    }

    if (protocol == MSI_PROTOCOL_M2S2)
    {
        if (_DTRDYC == 0)  // MailBox is empty
        {
            return 0;
        }
        return 1;
    }
    return -1;
}
