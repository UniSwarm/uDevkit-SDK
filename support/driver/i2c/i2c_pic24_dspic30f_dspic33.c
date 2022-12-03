/**
 * @file i2c_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date June 09, 2016, 18:47 PM
 *
 * @brief I2C communication support driver for dsPIC30F, dsPIC33FJ, dsPIC33EP,
 * dsPIC33CH, dsPIC33CK, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#include "i2c.h"

#include "driver/sysclock.h"

#include <archi.h>

#if !defined(I2C_COUNT) || I2C_COUNT == 0
#    warning "No i2c bus on the current device or unknow device"
#endif

#define I2C_FLAG_UNUSED 0x00
typedef struct
{
    union
    {
        struct
        {
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

static struct i2c_dev _i2cs[] = {
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#if I2C_COUNT >= 2
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
#if I2C_COUNT >= 3
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
};

/**
 * @brief Gives a free i2c bus device number and open it
 * @return i2c bus device number
 */
rt_dev_t i2c_getFreeDevice(void)
{
#if I2C_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < I2C_COUNT; i++)
    {
        if (_i2cs[i].flags.val == I2C_FLAG_UNUSED)
        {
            break;
        }
    }

    if (i == I2C_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_I2C, i);

    i2c_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open an i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_open(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }
    if (_i2cs[i2c].flags.used == 1)
    {
        return -1;
    }

    _i2cs[i2c].flags.used = 1;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close and release an i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_close(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    i2c_disable(device);

    _i2cs[i2c].flags.val = I2C_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_enable(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    _i2cs[i2c].flags.enabled = 1;

    switch (i2c)
    {
        case 0:
            I2C1CONbits.I2CEN = 1;  // enable i2c module
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_disable(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    _i2cs[i2c].flags.enabled = 0;

    switch (i2c)
    {
        case 0:
            I2C1CONbits.I2CEN = 0;  // disable i2c
#    ifndef ARCHI_dspic30f
            _MI2C1IE = 0;
#    endif
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.I2CEN = 0;  // disable i2c
            _MI2C2IE = 0;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.I2CEN = 0;  // disable i2c
            _MI2C3IE = 0;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the speed of receive and transmit of the specified i2c bus device
 * @param device i2c bus device number
 * @param baudSpeed speed of receive and transmit in bauds (bits / s)
 * @return 0 if ok, -1 in case of error
 */
int i2c_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)
{
#if I2C_COUNT >= 1
    uint32_t systemClockPeriph;
    uint16_t uBrg;

    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    if (baudSpeed == 0)
    {
        return -1;
    }

    _i2cs[i2c].baudSpeed = baudSpeed;

    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_I2C);
    uBrg = (systemClockPeriph / baudSpeed) - (systemClockPeriph / I2C_FPGD) - 2;

    if (uBrg <= 1)
    {
        uBrg = 2;
    }

    switch (i2c)
    {
        case 0:
            I2C1BRG = uBrg;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2BRG = uBrg;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3BRG = uBrg;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gets the true baud speed of the specified i2c bus device
 * @param device i2c bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t i2c_baudSpeed(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint32_t baudSpeed, systemClockPeriph;
    uint16_t uBrg;

    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    switch (i2c)
    {
        case 0:
            uBrg = I2C1BRG;
            break;
#    if I2C_COUNT >= 2
        case 1:
            uBrg = I2C2BRG;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            uBrg = I2C3BRG;
            break;
#    endif
    }

    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_I2C);
    baudSpeed = systemClockPeriph / (uBrg + 2);  // TODO add PGD period to be exact

    return baudSpeed;
#else
    return 0;
#endif
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
    {
        return 0;
    }

    return _i2cs[i2c].baudSpeed;
}

/**
 * @brief Sets the address width of slaves of the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_setAddressWidth(rt_dev_t device, uint8_t addressWidth)
{
#if I2C_COUNT >= 1
    uint8_t addrW10;
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    if (addressWidth == 7)
    {
        addrW10 = 0;
    }
    else if (addressWidth == 10)
    {
        addrW10 = 1;
    }
    else
    {
        return -1;
    }

    _i2cs[i2c].flags.addrW10 = addrW10;

    switch (i2c)
    {
        case 0:
            I2C1CONbits.A10M = addrW10;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.A10M = addrW10;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.A10M = addrW10;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gets the address width of slaves of the specified i2c bus device
 * @param device i2c bus device number
 * @return speed of receive and transmit in bauds (bits / s), 0 in case of error
 */
uint8_t i2c_addressWidth(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    if (_i2cs[i2c].flags.addrW10 == 1)
    {
        return 10;
    }
    else
    {
        return 7;
    }
#else
    return 0;
#endif
}

/**
 * @brief Sends a start condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_start(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.SEN = 1;
            while (I2C1CONbits.SEN)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.SEN = 1;
            while (I2C2CONbits.SEN)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.SEN = 1;
            while (I2C3CONbits.SEN)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sends a restart condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_restart(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.RSEN = 1;
            while (I2C1CONbits.RSEN)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.RSEN = 1;
            while (I2C2CONbits.RSEN)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.RSEN = 1;
            while (I2C3CONbits.RSEN)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sends a stop condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_stop(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.PEN = 1;
            while (I2C1CONbits.PEN)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.PEN = 1;
            while (I2C2CONbits.PEN)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.PEN = 1;
            while (I2C3CONbits.PEN)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Waits until start, restart, stop, receive, transmit or ack condition finish
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_idle(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            while (I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RCEN || I2C3CONbits.RSEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Generates acknowledge condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_ack(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.ACKDT = 0;
            I2C1CONbits.ACKEN = 1;
            while (I2C1CONbits.ACKEN)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.ACKDT = 0;
            I2C2CONbits.ACKEN = 1;
            while (I2C2CONbits.ACKEN)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.ACKDT = 0;
            I2C3CONbits.ACKEN = 1;
            while (I2C3CONbits.ACKEN)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Generates not acknowledge condition on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_nack(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.ACKDT = 1;
            I2C1CONbits.ACKEN = 1;
            while (I2C1CONbits.ACKEN)
                ;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.ACKDT = 1;
            I2C2CONbits.ACKEN = 1;
            while (I2C2CONbits.ACKEN)
                ;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.ACKDT = 1;
            I2C3CONbits.ACKEN = 1;
            while (I2C3CONbits.ACKEN)
                ;
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Send a 8 data on the specified i2c bus device
 * @param device i2c bus device number
 * @return 0 if ok, -1 in case of error
 */
int i2c_putc(rt_dev_t device, const char data)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1TRN = data;
            if (I2C1STATbits.IWCOL)  // write collision detection
            {
                return -1;
            }

            while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT)
                ;  // wait iddle

            if (I2C1STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2TRN = data;
            if (I2C2STATbits.IWCOL)  // write collision detection
            {
                return -1;
            }

            while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT)
                ;  // wait iddle

            if (I2C2STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3TRN = data;
            if (I2C3STATbits.IWCOL)  // write collision detection
            {
                return -1;
            }

            while (I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RCEN || I2C3CONbits.RSEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT)
                ;  // wait iddle

            if (I2C3STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Receive a 8 data on the specified i2c bus device
 * @param device i2c bus device number
 * @return data received
 */
uint8_t i2c_getc(rt_dev_t device)
{
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    switch (i2c)
    {
        case 0:
            I2C1CONbits.RCEN = 1;
            while (I2C1CONbits.RCEN)
                ;
            I2C1STATbits.I2COV = 0;
            return I2C1RCV;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CONbits.RCEN = 1;
            while (I2C2CONbits.RCEN)
                ;
            I2C2STATbits.I2COV = 0;
            return I2C2RCV;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CONbits.RCEN = 1;
            while (I2C3CONbits.RCEN)
                ;
            I2C3STATbits.I2COV = 0;
            return I2C3RCV;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Reconfigure clocks for all activated I2C devices. Call this function on clock change.
 */
void i2c_reconfig(void)
{
    for (uint8_t i = 0; i < I2C_COUNT; i++)
    {
        if (_i2cs[i].flags.used == 1 && _i2cs[i].baudSpeed != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_I2C, i);
            i2c_setBaudSpeed(device, _i2cs[i].baudSpeed);
        }
    }
}
