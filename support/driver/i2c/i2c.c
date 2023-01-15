/**
 * @file i2c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 01, 2016, 19:10 PM
 *
 * @brief I2C communication support driver, global function peripheral
 * independent
 */

#include "i2c.h"

/**
 * @brief Read a register at address 'reg' in i2c chip with address 'address'
 * @param device i2c bus device number
 * @param address i2c chip address
 * @param reg reg address to read
 * @param flags flags to configure the request frame
 * @return data received
 */
uint16_t i2c_readreg(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t flags)
{
    uint16_t value = 0;
    uint16_t byte;
    i2c_start(device);
    if (i2c_putc(device, (uint8_t)(address & 0xFE)) == -1)
    {
        i2c_stop(device);
        return 0;
    }
    if (flags & I2C_REGADDR16)
    {
        if (i2c_putc(device, (uint8_t)(reg >> 8)) == -1)
        {
            i2c_stop(device);
            return 0;
        }
    }
    if (i2c_putc(device, (uint8_t)(reg & 0x00FF)) == -1)
    {
        i2c_stop(device);
        return 0;
    }
    if (flags & I2C_READ_STOPSTART)
    {
        i2c_stop(device);
        i2c_start(device);
    }
    else
    {
        i2c_restart(device);
    }
    if (i2c_putc(device, address | 0x01) == -1)
    {
        i2c_stop(device);
        return 0;
    }
    if (flags & I2C_REG16)
    {
        byte = i2c_getc(device);
        i2c_ack(device);
    }
    value = i2c_getc(device);
    if (flags & I2C_REG16)
    {
        if (flags & I2C_READ_LSBFIRST)
        {
            value = (value << 8) + byte;
        }
        else
        {
            value = value + (byte << 8);
        }
    }
    i2c_nack(device);
    i2c_stop(device);
    return value;
}
/**
 * @brief Read 'size' registers begining at address 'reg' in i2c chip with address 'address'
 * @param device i2c bus device number
 * @param address i2c chip address
 * @param reg reg address to start read
 * @param size number of reg to read
 * @param flags flags to configure the request frame
 * @return 0 if success
 */
ssize_t i2c_readregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags)
{
    size_t id;
    uint8_t *ptrreg;

    i2c_start(device);
    if (i2c_putc(device, (uint8_t)(address & 0xFE)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    if (flags & I2C_REGADDR16)
    {
        if (i2c_putc(device, (uint8_t)(reg >> 8)) != 0)
        {
            i2c_stop(device);
            return -1;
        }
    }
    if (i2c_putc(device, (uint8_t)(reg & 0x00FF)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    if (flags & I2C_READ_STOPSTART)
    {
        i2c_stop(device);
        i2c_start(device);
    }
    else
    {
        i2c_restart(device);
    }

    if (i2c_putc(device, address | 0x01) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    ptrreg = regs;
    for (id = 0; id < size; id++)
    {
        if (flags & I2C_REG16)
        {
            *ptrreg = i2c_getc(device) << 8;
            ptrreg++;
        }
        *ptrreg = i2c_getc(device);
        ptrreg++;
        if (id != size - 1)
        {
            i2c_ack(device);
        }
        else
        {
            i2c_nack(device);
            i2c_stop(device);
        }
    }
    return 0;
}

/**
 * @brief Write 'value' in register at address 'reg' in i2c chip with address 'address'
 * @param device i2c bus device number
 * @param address i2c chip address
 * @param reg reg address to write
 * @param value value to write
 * @param flags flags to configure the request frame
 * @return 0 if success
 */
int i2c_writereg(rt_dev_t device, uint16_t address, uint16_t reg, uint16_t value, uint8_t flags)
{
    i2c_start(device);
    if (i2c_putc(device, (uint8_t)(address & 0xFE)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    if (flags & I2C_REGADDR16)
    {
        if (i2c_putc(device, (uint8_t)(reg >> 8)) != 0)
        {
            i2c_stop(device);
            return -1;
        }
    }
    if (i2c_putc(device, (uint8_t)(reg & 0x00FF)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    if (flags & I2C_REG16)
    {
        if (flags & I2C_READ_LSBFIRST)
        {
            value = (value >> 8) | (value << 8);
        }
        if (i2c_putc(device, (uint8_t)(value >> 8)) != 0)
        {
            i2c_stop(device);
            return -1;
        }
    }
    if (i2c_putc(device, (uint8_t)(value & 0x00FF)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    i2c_stop(device);
    return 0;
}

/**
 * @brief Write 'regs' in registers that start at address 'reg' in i2c chip
 * with address 'address'
 * @param device i2c bus device number
 * @param address i2c chip address
 * @param reg reg address to write
 * @param regs values to write
 * @param size number of reg to write
 * @param flags flags to configure the request frame
 * @return 0 if success
 */
int i2c_writeregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags)
{
    size_t id;
    uint8_t *ptrreg;

    i2c_start(device);
    if (i2c_putc(device, (uint8_t)(address & 0xFE)) != 0)
    {
        i2c_stop(device);
        return -1;
    }
    if (flags & I2C_REGADDR16)
    {
        if (i2c_putc(device, (uint8_t)(reg >> 8)) != 0)
        {
            i2c_stop(device);
            return -1;
        }
    }
    if (i2c_putc(device, (uint8_t)(reg & 0x00FF)) != 0)
    {
        i2c_stop(device);
        return -1;
    }

    ptrreg = regs;
    for (id = 0; id < size; id++)
    {
        if (flags & I2C_REG16)
        {
            if (i2c_putc(device, *(ptrreg++)) != 0)
            {
                i2c_stop(device);
                return -1;
            }
        }
        if (i2c_putc(device, *(ptrreg++)) != 0)
        {
            i2c_stop(device);
            return -1;
        }
    }
    i2c_stop(device);
    return 0;
}
