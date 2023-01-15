/**
 * @file msi_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2023
 *
 * @date March 20 2019, 19:45 PM
 *
 * @brief MSI udevkit simulator support for simulation purpose
 */

#include "msi.h"

// TODO : dummy implementation, please implement me

#ifdef MSI_HAVE_PRIMARY_INTERFACE
int msi_secondary_start(const uint8_t secondary_id)
{
    UDK_UNUSED(secondary_id);
    return 0;
}

int msi_secondary_stop(const uint8_t secondary_id)
{
    UDK_UNUSED(secondary_id);
    return 0;
}

int msi_secondary_reset(const uint8_t secondary_id)
{
    UDK_UNUSED(secondary_id);
    return 0;
}

MSI_CORE_STATUS msi_secondary_status(const uint8_t secondary_id)
{
    UDK_UNUSED(secondary_id);
    return 0;
}

int msi_secondary_program(const uint8_t secondary_id, __eds__ unsigned char *program)
{
    UDK_UNUSED(secondary_id);
    UDK_UNUSED(program);
    return 0;
}

int msi_secondary_verify_program(const uint8_t secondary_id, __eds__ unsigned char *program)
{
    UDK_UNUSED(secondary_id);
    UDK_UNUSED(program);
    return 0;
}

#endif

#ifndef MSI_HAVE_PRIMARY_INTERFACE
MSI_CORE_STATUS msi_master_status(void)
{
    return 0;
}
#endif

#ifdef MSI_HAVE_PRIMARY_INTERFACE
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

#ifndef MSI_HAVE_PRIMARY_INTERFACE
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
