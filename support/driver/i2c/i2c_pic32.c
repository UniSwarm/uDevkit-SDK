/**
 * @file i2c_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 01, 2016, 19:10 PM
 *
 * @brief I2C communication support driver for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 */

#include "i2c.h"

#include "driver/sysclock.h"

#include <archi.h>

#if !defined(I2C_COUNT) || I2C_COUNT == 0
#    warning "No i2c bus on the current device or unknow device"
#endif

enum
{
    I2C_FLAG_UNUSED = 0x00
};
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
#if I2C_COUNT >= 1
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
#if I2C_COUNT >= 2
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
#if I2C_COUNT >= 3
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
#if I2C_COUNT >= 4
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
#if I2C_COUNT >= 5
    {.baudSpeed = 0, .flags = {{.val = I2C_FLAG_UNUSED}}},
#endif
};

#ifdef I2C_NOI2C2
rt_dev_t i2c(uint8_t d)
{
    if (d > 1)
    {
        return MKDEV(DEV_CLASS_I2C, d - 2);
    }
    else
    {
        return MKDEV(DEV_CLASS_I2C, d - 1);
    }
}
#endif

/**
 * @brief Gives a free i2c bus device number and open it
 * @return i2c bus device number
 */
rt_dev_t i2c_getFreeDevice(void)
{
#if I2C_COUNT >= 1
    rt_dev_t device;
    uint8_t i2c_id;
    for (i2c_id = 0; i2c_id < I2C_COUNT; i2c_id++)
    {
        if (_i2cs[i2c_id].flags.val == I2C_FLAG_UNUSED)
        {
            break;
        }
    }

    if (i2c_id == I2C_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_I2C, i2c_id);

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
 * @brief I2C sdk state
 * @param device i2c device number
 * @return true if i2c was openned by i2c_open function
 */
bool i2c_isOpened(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    return (_i2cs[i2c].flags.used == 1);
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
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.I2CEN = 1;  // enable i2c module
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.I2CEN = 1;  // enable i2c module
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
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.I2CEN = 0;  // disable i2c
            _I2C1MIE = 0;           // disable i2c master interrupt
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.I2CEN = 0;  // disable i2c
            _I2C2MIE = 0;           // disable i2c master interrupt
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.I2CEN = 0;  // disable i2c
            _I2C3MIE = 0;           // disable i2c master interrupt
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.I2CEN = 0;  // disable i2c
            _I2C4MIE = 0;           // disable i2c master interrupt
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.I2CEN = 0;  // disable i2c
            _I2C5MIE = 0;           // disable i2c master interrupt
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief I2C sdk enabled state
 * @param device i2c device number
 * @return true if i2c was enabled by i2c_enable function
 */
bool i2c_isEnabled(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return -1;
    }

    return (_i2cs[i2c].flags.enabled == 1);
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
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1BRG = uBrg;
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2BRG = uBrg;
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3BRG = uBrg;
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4BRG = uBrg;
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5BRG = uBrg;
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

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            uBrg = I2C1BRG;
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            uBrg = I2C2BRG;
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            uBrg = I2C3BRG;
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            uBrg = I2C4BRG;
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            uBrg = I2C5BRG;
            break;
#    endif
        default:
            return 0;
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
#if I2C_COUNT >= 1
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    return _i2cs[i2c].baudSpeed;
#else
    return 0;
#endif
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
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.A10M = addrW10;
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.A10M = addrW10;
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.A10M = addrW10;
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.A10M = addrW10;
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.A10M = addrW10;
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
 * @return speed of receive and transmit in bauds (bits / s)
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

    return 7;

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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.SEN = 1;
            while (I2C1CONbits.SEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.SEN = 1;
            while (I2C2CONbits.SEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.SEN = 1;
            while (I2C3CONbits.SEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.SEN = 1;
            while (I2C4CONbits.SEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.SEN = 1;
            while (I2C5CONbits.SEN)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.RSEN = 1;
            while (I2C1CONbits.RSEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.RSEN = 1;
            while (I2C2CONbits.RSEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.RSEN = 1;
            while (I2C3CONbits.RSEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.RSEN = 1;
            while (I2C4CONbits.RSEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.RSEN = 1;
            while (I2C5CONbits.RSEN)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.PEN = 1;
            while (I2C1CONbits.PEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.PEN = 1;
            while (I2C2CONbits.PEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.PEN = 1;
            while (I2C3CONbits.PEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.PEN = 1;
            while (I2C4CONbits.PEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.PEN = 1;
            while (I2C5CONbits.PEN)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            while (I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RCEN || I2C3CONbits.RSEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            while (I2C4CONbits.SEN || I2C4CONbits.PEN || I2C4CONbits.RCEN || I2C4CONbits.RSEN || I2C4CONbits.ACKEN || I2C4STATbits.TRSTAT)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            while (I2C5CONbits.SEN || I2C5CONbits.PEN || I2C5CONbits.RCEN || I2C5CONbits.RSEN || I2C5CONbits.ACKEN || I2C5STATbits.TRSTAT)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.ACKDT = 0;
            I2C1CONbits.ACKEN = 1;
            while (I2C1CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.ACKDT = 0;
            I2C2CONbits.ACKEN = 1;
            while (I2C2CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.ACKDT = 0;
            I2C3CONbits.ACKEN = 1;
            while (I2C3CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.ACKDT = 0;
            I2C4CONbits.ACKEN = 1;
            while (I2C4CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.ACKDT = 0;
            I2C5CONbits.ACKEN = 1;
            while (I2C5CONbits.ACKEN)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.ACKDT = 1;
            I2C1CONbits.ACKEN = 1;
            while (I2C1CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.ACKDT = 1;
            I2C2CONbits.ACKEN = 1;
            while (I2C2CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.ACKDT = 1;
            I2C3CONbits.ACKEN = 1;
            while (I2C3CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.ACKDT = 1;
            I2C4CONbits.ACKEN = 1;
            while (I2C4CONbits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.ACKDT = 1;
            I2C5CONbits.ACKEN = 1;
            while (I2C5CONbits.ACKEN)
            {
                ;
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
        return 0;
    }

    switch (i2c)
    {
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1TRN = (unsigned char)data;
            if (I2C1STATbits.BCL || I2C1STATbits.IWCOL)  // write collision detection
            {
                I2C1STATbits.BCL = 0;
                I2C1STATbits.IWCOL = 0;
                return -1;
            }

            while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C1STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2TRN = (unsigned char)data;
            if (I2C2STATbits.BCL || I2C2STATbits.IWCOL)  // write collision detection
            {
                I2C2STATbits.BCL = 0;
                I2C2STATbits.IWCOL = 0;
                return -1;
            }

            while (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || I2C2CONbits.RSEN || I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C2STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3TRN = (unsigned char)data;
            if (I2C3STATbits.BCL || I2C3STATbits.IWCOL)  // write collision detection
            {
                I2C3STATbits.BCL = 0;
                I2C3STATbits.IWCOL = 0;
                return -1;
            }

            while (I2C3CONbits.SEN || I2C3CONbits.PEN || I2C3CONbits.RCEN || I2C3CONbits.RSEN || I2C3CONbits.ACKEN || I2C3STATbits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C3STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4TRN = (unsigned char)data;
            if (I2C4STATbits.BCL || I2C4STATbits.IWCOL)  // write collision detection
            {
                I2C4STATbits.BCL = 0;
                I2C4STATbits.IWCOL = 0;
                return -1;
            }

            while (I2C4CONbits.SEN || I2C4CONbits.PEN || I2C4CONbits.RCEN || I2C4CONbits.RSEN || I2C4CONbits.ACKEN || I2C4STATbits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C4STATbits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5TRN = (unsigned char)data;
            if (I2C5STATbits.BCL || I2C5STATbits.IWCOL)  // write collision detection
            {
                I2C5STATbits.BCL = 0;
                I2C5STATbits.IWCOL = 0;
                return -1;
            }

            while (I2C5CONbits.SEN || I2C5CONbits.PEN || I2C5CONbits.RCEN || I2C5CONbits.RSEN || I2C5CONbits.ACKEN || I2C5STATbits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C5STATbits.ACKSTAT)  // test for ACK received
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
#    ifdef I2C_NUM1
        case I2C_NUM1:
            I2C1CONbits.RCEN = 1;
            while (I2C1CONbits.RCEN)
            {
                ;
            }
            I2C1STATbits.I2COV = 0;
            return I2C1RCV;
#    endif
#    ifdef I2C_NUM2
        case I2C_NUM2:
            I2C2CONbits.RCEN = 1;
            while (I2C2CONbits.RCEN)
            {
                ;
            }
            I2C2STATbits.I2COV = 0;
            return I2C2RCV;
#    endif
#    ifdef I2C_NUM3
        case I2C_NUM3:
            I2C3CONbits.RCEN = 1;
            while (I2C3CONbits.RCEN)
            {
                ;
            }
            I2C3STATbits.I2COV = 0;
            return I2C3RCV;
#    endif
#    ifdef I2C_NUM4
        case I2C_NUM4:
            I2C4CONbits.RCEN = 1;
            while (I2C4CONbits.RCEN)
            {
                ;
            }
            I2C4STATbits.I2COV = 0;
            return I2C4RCV;
#    endif
#    ifdef I2C_NUM5
        case I2C_NUM5:
            I2C5CONbits.RCEN = 1;
            while (I2C5CONbits.RCEN)
            {
                ;
            }
            I2C5STATbits.I2COV = 0;
            return I2C5RCV;
#    endif
    }
#endif
    return 0;
}

/**
 * @brief Reconfigure clocks for all activated I2C devices. Call this function on clock change.
 */
void i2c_reconfig(void)
{
    // TODO check the impact of I2C_NOI2C2
    for (uint8_t i2c_id = 0; i2c_id < I2C_COUNT; i2c_id++)
    {
        if (_i2cs[i2c_id].flags.used == 1 && _i2cs[i2c_id].baudSpeed != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_I2C, i2c_id);
            i2c_setBaudSpeed(device, _i2cs[i2c_id].baudSpeed);
        }
    }
}
