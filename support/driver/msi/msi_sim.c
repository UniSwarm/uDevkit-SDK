/**
 * @file msi_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Uniswarm 2019
 *
 * @date March 20 2019, 19:45 PM
 *
 * @brief MSI udevkit simulator support for simulation purpose
 */

#include "msi.h"

// TODO : dummy implementation, please implement me


#ifdef MSI_HAVE_MASTER_INTERFACE
int msi_slave_start(uint8_t slave_id)
{
	return 0;
}

int msi_slave_stop(uint8_t slave_id)
{
	return 0;
}

int msi_slave_reset(uint8_t slave_id)
{
	return 0;
}

MSI_CORE_STATUS msi_slave_status(uint8_t slave_id)
{
	return 0;
}

int msi_slave_program(uint8_t slave_id, __eds__ unsigned char *program)
{
	return 0;
}

int msi_slave_verify_program(uint8_t slave_id, __eds__ unsigned char *program)
{
	return 0;
}

#endif

#ifndef MSI_HAVE_MASTER_INTERFACE
MSI_CORE_STATUS msi_master_status()
{
	return 0;
}
#endif

#ifdef MSI_HAVE_MASTER_INTERFACE
int msi_protocol_write(uint8_t protocol, const unsigned char *data, uint8_t size)
{
	return 0;
}

int msi_protocol_read(uint8_t protocol, unsigned char *data, uint8_t max_size)
{
	return 0;
}
#endif

#ifndef MSI_HAVE_MASTER_INTERFACE
int msi_protocol_write(uint8_t protocol, const unsigned char *data, uint8_t size)
{
	return 0;
}

int msi_protocol_read(uint8_t protocol, unsigned char *data, uint8_t max_size)
{
	return 0;
}
#endif
