/**
 * @file i2c_pic24_dspic30_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 28, 2016, 20:35 PM 
 *
 * @brief I2C communication support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#include "i2c_sim.h"

#define I2C_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned addrW10 : 1;
            unsigned : 5;
        };
        uint8_t val;
    };
} i2c_status;

struct i2c_dev
{
    uint32_t baudSpeed;
    i2c_status flags;
};

struct i2c_dev i2cs[] = {
    {
        .baudSpeed = 0,
        .flags = {{.val = I2C_FLAG_UNUSED}}
    },
#if I2C_COUNT>=2
    {
        .baudSpeed = 0,
        .flags = {{.val = I2C_FLAG_UNUSED}}
    },
#endif
#if I2C_COUNT>=3
    {
        .baudSpeed = 0,
        .flags = {{.val = I2C_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free i2c bus device number
 * @return i2c bus device number
 */
rt_dev_t i2c_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < I2C_COUNT; i++)
        if (i2cs[i].flags.val == I2C_FLAG_UNUSED)
            break;

    if (i == I2C_COUNT)
        return NULLDEV;

    i2cs[i].flags.used = 1;

    return MKDEV(DEV_CLASS_I2C, i);
}

/**
 * @brief Release an i2c bus device
 * @param device i2c bus device number
 */
void i2c_releaseDevice(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return;

    i2cs[i2c].flags.val = I2C_FLAG_UNUSED;
}

/**
 * @brief Enable the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_enable(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return -1;

    i2cs[i2c].flags.enabled = 1;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Disable the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_disable(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return -1;

    i2cs[i2c].flags.enabled = 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Sets the speed of receive and transmit of the specified i2c bus device
 * @param device i2c bus device number
 * @param baudSpeed speed of receive and transmit in bauds (bits / s)
 * @return 0 if ok, -1 in case of error
 */
int i2c_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return -1;

    if (baudSpeed == 0)
        return -1;

    i2cs[i2c].baudSpeed = baudSpeed;
    
    // TODO SIM

    return 0;
}


/**
 * @brief Gets the true baud speed of the specified i2c bus device
 * @param device i2c bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t i2c_baudSpeed(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;

    return i2cs[i2c].baudSpeed;
}

/**
 * @brief Gets the effective baud speed of the specified i2c bus device
 * @param device i2c bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t i2c_effectiveBaudSpeed(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;

    return i2cs[i2c].baudSpeed;
}

/**
 * @brief Sets the address width of slaves of the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_setAddressWidth(rt_dev_t device, uint8_t addressWidth)
{
    uint8_t addrW10;
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;

    if (addressWidth == 7)
        addrW10 = 0;
    else if (addressWidth == 10)
        addrW10 = 1;
    else
        return -1;

    i2cs[i2c].flags.addrW10 = addrW10;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Gets the address width of slaves of the specified i2c bus device
 * @param device i2c bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint8_t i2c_addressWidth(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return -1;

    if (i2cs[i2c].flags.addrW10 == 1)
        return 10;
    else
        return 7;
}

/**
 * @brief Sends a start condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_start(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Sends a restart condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_restart(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Sends a stop condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_stop(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Waits until start, restart, stop, receive, transmit or ack condition finish
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_idle(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Generates acknowledge condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_ack(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Generates not acknowledge condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_nack(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Send a 8 data on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_putc(rt_dev_t device, const char data)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM

    return 0;
}

/**
 * @brief Receive a 8 data on the specified i2c bus device
 * @param device i2c bus device number
 * @return data received
 */
uint8_t i2c_getc(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
        return 0;
    
    // TODO SIM
    
    return 0;
}

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
    uint16_t value=0;
    i2c_start(device);
    i2c_putc(device, (uint8_t)(address & 0xF8));
    if (flags & I2C_REGADDR16)
        i2c_putc(device, (uint8_t)(reg>>8));
    i2c_putc(device, (uint8_t)reg);
    if (flags & I2C_READ_STOPSTART)
    {
        i2c_stop(device);
        i2c_start(device);
    }
    else
        i2c_restart(device);
    i2c_putc(device, address | 0x01);
    if (flags & I2C_REG16)
        value = i2c_getc(device)<<8;
    value += i2c_getc(device);
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
    i2c_putc(device, (uint8_t)(address & 0xF8));
    if (flags & I2C_REGADDR16)
        i2c_putc(device, (uint8_t)(reg>>8));
    i2c_putc(device, (uint8_t)reg);
    if (flags & I2C_READ_STOPSTART)
    {
        i2c_stop(device);
        i2c_start(device);
    }
    else
        i2c_restart(device);

    i2c_putc(device, address | 0x01);
    ptrreg = regs;
    for (id=0; id<size; id++)
    {
        if (flags & I2C_REG16)
        {
            *ptrreg = i2c_getc(device)<<8;
            ptrreg++;
        }
        *ptrreg = i2c_getc(device);
        ptrreg++;
        if(id!=size-1)
            i2c_ack(device);
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
    i2c_putc(device, (uint8_t)(address & 0xF8));
    if (flags & I2C_REGADDR16)
        i2c_putc(device, (uint8_t)(reg>>8));
    i2c_putc(device, (uint8_t)reg);
    if (flags & I2C_REG16)
        i2c_putc(device, (uint8_t)(value>>8));
    i2c_putc(device, (uint8_t)value);
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
    i2c_putc(device, (uint8_t)(address & 0xF8));
    if (flags & I2C_REGADDR16)
        i2c_putc(device, (uint8_t)(reg>>8));
    i2c_putc(device, (uint8_t)reg);

    ptrreg = regs;
    for (id=0; id<size; id++)
    {
        if (flags & I2C_REG16)
            i2c_putc(device, *(ptrreg++));
        i2c_putc(device, *(ptrreg++));
    }
    i2c_stop(device);
    return 0;
}
