/**
 * @file msi_dspic33ch.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
 *
 * @date March 2, 10:00 AM
 *
 * @brief Primary / secondary cores interface driver for dsPIC33CH
 *
 * Implementation based on Microchip document DS70005278B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Master-Slave-Interface-MSI-Module-70005278b.pdf
 */

#include "msi.h"

#include <archi.h>

#include <libpic30.h>
#include <string.h>

/**
 * @brief Starts the secondary with id `secondary_id`
 * @param secondary_id secondary id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_secondary_start(const uint8_t secondary_id)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    start_secondary();
    return 0;
}

/**
 * @brief Stops the secondary with id `secondary_id`
 * @param secondary_id secondary id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_secondary_stop(const uint8_t secondary_id)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    stop_secondary();
    return 0;
}

/**
 * @brief Resets the secondary with id `secondary_id`
 * @param secondary_id secondary id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_secondary_reset(const uint8_t secondary_id)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    stop_secondary();
    start_secondary();
    return 0;
}

/**
 * @brief Gives the status of the secondary with id `secondary_id`
 * @param secondary_id secondary id, first one is 1
 * @return MSI_CORE_STATUS status enum
 */
MSI_CORE_STATUS msi_secondary_status(const uint8_t secondary_id)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    if (MSI1STATbits.SLVWDRST)
    {
        return MSI_CORE_STATUS_RESETED;
    }

    // TODO FIXME
    switch (MSI1STATbits.SLVPWR)
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

/**
 * @brief Program the PRAM of secondary with the program data
 * @param secondary_id secondary id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_secondary_program(const uint8_t secondary_id, __eds__ unsigned char *program)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    return program_secondary(secondary_id, 0, program);
}

/**
 * @brief Check the PRAM content of secondary with the program data
 * @param secondary_id secondary id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_secondary_verify_program(const uint8_t secondary_id, __eds__ unsigned char *program)
{
    if (secondary_id != 1)
    {
        return -1;
    }

    return program_secondary(secondary_id, 1, program);
}

int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(size);

    if (protocol == MSI_PROTOCOL_M2S)
    {
        if (_DTRDYA == 1)
        {
            return -1;
        }
        memcpy((void *)&MSI1MBX0D, (const void *)data, 10);
        return 0;
    }
    if (protocol == MSI_PROTOCOL_M2S2)
    {
        if (_DTRDYC == 1)
        {
            return -1;
        }
        memcpy((void *)&MSI1MBX10D, (const void *)data, 6);
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
    if (protocol == MSI_PROTOCOL_M2S)
    {
        if (_DTRDYA == 1)  // MailBox is full
        {
            return 0;
        }
        return 1;
    }
    if (protocol == MSI_PROTOCOL_M2S2)
    {
        if (_DTRDYC == 1)  // MailBox is full
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

    if (protocol == MSI_PROTOCOL_S2M)
    {
        if (_DTRDYB == 0)
        {
            return -1;
        }
        memcpy((void *)data, (void *)&MSI1MBX5D, 10);
        return 0;
    }

    if (protocol == MSI_PROTOCOL_S2M2)
    {
        if (_DTRDYD == 0)
        {
            return -1;
        }
        memcpy((void *)data, (void *)&MSI1MBX13D, 6);
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
    if (protocol == MSI_PROTOCOL_S2M)
    {
        if (_DTRDYB == 0)  // MailBox is empty
        {
            return 0;
        }
        return 1;
    }

    if (protocol == MSI_PROTOCOL_S2M2)
    {
        if (_DTRDYD == 0)  // MailBox is empty
        {
            return 0;
        }
        return 1;
    }
    return -1;
}
