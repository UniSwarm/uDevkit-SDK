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

#include <libpic30.h>

extern int  _program_slave(int slave_number, int verify,__eds__ unsigned char *image);

/**
 * @brief Start the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_start_slave(uint8_t slave_id)
{
    if (slave_id != 1)
        return -1;

    _start_slave();
    return 0;
}

/**
 * @brief Stop the slave with id `slave_id`
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_stop_slave(uint8_t slave_id)
{
    if (slave_id != 1)
        return -1;

    _stop_slave();
    return 0;
}

/**
 * @brief Program the PRAM of slave with the program data
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_program_slave(uint8_t slave_id, __eds__ unsigned char *program)
{
    if (slave_id != 1)
        return -1;

    return _program_slave(slave_id, 0, program);
}

/**
 * @brief Check the PRAM content of slave with the program data
 * @param slave_id slave id, first one is 1
 * @return 0 if ok, -1 in case of error
 */
int msi_verify_program_slave(uint8_t slave_id, __eds__ unsigned char *program)
{
    if (slave_id != 1)
        return -1;

    return _program_slave(slave_id, 1, program);
}
