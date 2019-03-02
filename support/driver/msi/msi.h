/**
 * @file msi.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 2, 10:00 AM
 *
 * @brief Master Slave Interface driver
 */

#ifndef MSI_H
#define MSI_H

#include <driver/device.h>

int msi_start_slave(uint8_t slave_id);
int msi_stop_slave(uint8_t slave_id);

int msi_program_slave(uint8_t slave_id, __eds__ unsigned char *program);
int msi_verify_program_slave(uint8_t slave_id, __eds__ unsigned char *program);

#if defined(ARCHI_dspic33ch)
 #include "msi_dspic33ch.h"
#else
 #warning Unsuported ARCHI
#endif

#endif // MSI_H