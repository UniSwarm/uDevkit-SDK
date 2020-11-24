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
int msi_slave_start(const uint8_t slave_id)
{
    UDK_UNUSED(slave_id);
    return 0;
}

int msi_slave_stop(const uint8_t slave_id)
{
    UDK_UNUSED(slave_id);
    return 0;
}

int msi_slave_reset(const uint8_t slave_id)
{
    UDK_UNUSED(slave_id);
    return 0;
}

MSI_CORE_STATUS msi_slave_status(const uint8_t slave_id)
{
    UDK_UNUSED(slave_id);
    return 0;
}

int msi_slave_program(const uint8_t slave_id, __eds__ unsigned char *program)
{
    UDK_UNUSED(slave_id);
    UDK_UNUSED(program);
    return 0;
}

int msi_slave_verify_program(const uint8_t slave_id, __eds__ unsigned char *program)
{
    UDK_UNUSED(slave_id);
    UDK_UNUSED(program);
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
int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(data);
    UDK_UNUSED(size);
    return 0;
}

int msi_protocol_canWrite(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    return 1;
}

int msi_protocol_read(const uint8_t protocol, unsigned char *data, uint8_t max_size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(data);
    UDK_UNUSED(max_size);
    return 0;
}

int msi_protocol_canRead(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    return 1;
}
#endif

#ifndef MSI_HAVE_MASTER_INTERFACE
int msi_protocol_write(const uint8_t protocol, const unsigned char *data, uint8_t size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(data);
    UDK_UNUSED(size);
    return 0;
}

int msi_protocol_canWrite(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    return 1;
}

int msi_protocol_read(const uint8_t protocol, unsigned char *data, uint8_t max_size)
{
    UDK_UNUSED(protocol);
    UDK_UNUSED(data);
    UDK_UNUSED(max_size);
    return 0;
}

int msi_protocol_canRead(const uint8_t protocol)
{
    UDK_UNUSED(protocol);
    return 1;
}
#endif
