/**
 * @file msi_dspic33ch.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 2, 10:00 AM
 *
 * @brief Master Slave Interface driver for dsPIC33CH
 *
 * Implementation based on Microchip document DS70005278B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Master-Slave-Interface-MSI-Module-70005278b.pdf
 */

#include "msi.h"

#include <archi.h>
#include <libpic30.h>

/**
 * @brief Starts the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_slave_start(const uint8_t slave_id)
{
    if (slave_id != 1)
    {
        return -1;
    }

    _start_slave();
    return 0;
}

/**
 * @brief Stops the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_slave_stop(const uint8_t slave_id)
{
    if (slave_id != 1)
    {
        return -1;
    }

    _stop_slave();
    return 0;
}

/**
 * @brief Resets the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_slave_reset(const uint8_t slave_id)
{
    if (slave_id != 1)
    {
        return -1;
    }

    _stop_slave();
    _start_slave();
    return 0;
}

MSI_CORE_STATUS msi_master_status(void)
{
    // SI1STAT
    // TODO IMPLEMENT ME
    return MSI_CORE_STATUS_STARTED;
}

/**
 * @brief Gives the status of the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return MSI_CORE_STATUS status enum
 */
MSI_CORE_STATUS msi_slave_status(const uint8_t slave_id)
{
    if (slave_id != 1)
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
 * @brief Program the PRAM of slave with the program data
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_slave_program(const uint8_t slave_id, __eds__ unsigned char *program)
{
    if (slave_id != 1)
    {
        return -1;
    }

    return _program_slave(slave_id, 0, program);
}

/**
 * @brief Check the PRAM content of slave with the program data
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_slave_verify_program(const uint8_t slave_id, __eds__ unsigned char *program)
{
    if (slave_id != 1)
    {
        return -1;
    }

    return _program_slave(slave_id, 1, program);
}

int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(size);

    if (_DTRDYA == 1)
    {
        return -1;
    }
    uint16_t *ptr = (uint16_t *)data;
    MSI1MBX0D = *(ptr++);
    MSI1MBX1D = *(ptr++);
    MSI1MBX2D = *(ptr++);
    MSI1MBX3D = *(ptr++);
    MSI1MBX4D = *(ptr++);
    return 0;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is full and can not be written, 1 if OK, -1 if protocol is not valid
 */
int msi_protocol_canWrite(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    if (_DTRDYA == 1)  // MailBox is full
    {
        return 0;
    }
    return 1;
}

int msi_protocol_read(const uint8_t protocol, unsigned char *data, uint8_t max_size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(max_size);

    if (_DTRDYB == 0)
    {
        return -1;
    }
    uint16_t *ptr = (uint16_t *)data;
    *ptr = MSI1MBX5D;
    ptr++;
    *ptr = MSI1MBX6D;
    ptr++;
    *ptr = MSI1MBX7D;
    ptr++;
    *ptr = MSI1MBX8D;
    ptr++;
    *ptr = MSI1MBX9D;
    return 0;
}

/**
 * @brief Gets number of data that could be read (in sw buffer)
 * @param protocol protocol id
 * @return 0 if mail is empty, 1 if OK to be read, -1 if protocol is not valid
 */
int msi_protocol_canRead(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    if (_DTRDYB == 0)  // MailBox is empty
    {
        return 0;
    }
    return 1;
}
