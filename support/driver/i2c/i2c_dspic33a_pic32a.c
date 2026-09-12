/**
 * @file i2c_dspic33a_pic32a.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date September 12, 2026, 09:25 AM
 *
 * @brief I2C support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005539C, DS70005629C, DS70005591D and DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
 */

#include "i2c.h"

#include <driver/sysclock.h>

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
 * @brief I2C sdk state
 * @param device i2c device number
 * @return true if i2c was openned by i2c_open function
 */
bool i2c_isOpened(rt_dev_t device)
{
    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return false;
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
        case 0:
            I2C1CON1bits.ON = 1;  // enable i2c module
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.ON = 1;  // enable i2c module
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.ON = 1;  // enable i2c module
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
            I2C1CON1bits.ON = 0;  // disable i2c
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.ON = 0;  // disable i2c
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.ON = 0;  // disable i2c
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
        return false;
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

    uint32_t systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_I2C);
    float delay = 0.000000180;  // 180 ns
    float uBrg = (((1.0 / (2.0 * baudSpeed)) - delay) * systemClockPeriph) - 3;

    if (uBrg <= 4)
    {
        uBrg = 4;
    }

    switch (i2c)
    {
        case 0:
            I2C1LBRG = uBrg;
            I2C1HBRG = uBrg;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2LBRG = uBrg;
            I2C2HBRG = uBrg;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3LBRG = uBrg;
            I2C3HBRG = uBrg;
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
    uint32_t uBrg;

    uint8_t i2c = MINOR(device);
    if (i2c >= I2C_COUNT)
    {
        return 0;
    }

    switch (i2c)
    {
        case 0:
            uBrg = I2C1LBRG;
            break;
#    if I2C_COUNT >= 2
        case 1:
            uBrg = I2C2LBRG;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            uBrg = I2C3LBRG;
            break;
#    endif
        default:
            return 0;
    }

    uint32_t systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_I2C);
    uint32_t baudSpeed = 2 * systemClockPeriph / (uBrg + 3);  // TODO add PGD period to be exact

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
        return -1;
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
            I2C1CON1bits.A10M = addrW10;
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.A10M = addrW10;
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.A10M = addrW10;
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
            I2C1CON1bits.SEN = 1;
            while (I2C1CON1bits.SEN)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.SEN = 1;
            while (I2C2CON1bits.SEN)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.SEN = 1;
            while (I2C3CON1bits.SEN)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CON1bits.RSEN = 1;
            while (I2C1CON1bits.RSEN)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.RSEN = 1;
            while (I2C2CON1bits.RSEN)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.RSEN = 1;
            while (I2C3CON1bits.RSEN)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CON1bits.PEN = 1;
            while (I2C1CON1bits.PEN)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.PEN = 1;
            while (I2C2CON1bits.PEN)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.PEN = 1;
            while (I2C3CON1bits.PEN)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            while (I2C1CON1bits.SEN || I2C1CON1bits.PEN || I2C1CON1bits.RCEN || I2C1CON1bits.RSEN || I2C1CON1bits.ACKEN || I2C1STAT1bits.TRSTAT)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            while (I2C2CON1bits.SEN || I2C2CON1bits.PEN || I2C2CON1bits.RCEN || I2C2CON1bits.RSEN || I2C2CON1bits.ACKEN || I2C2STAT1bits.TRSTAT)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            while (I2C3CON1bits.SEN || I2C3CON1bits.PEN || I2C3CON1bits.RCEN || I2C3CON1bits.RSEN || I2C3CON1bits.ACKEN || I2C3STAT1bits.TRSTAT)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CON1bits.ACKDT = 0;
            I2C1CON1bits.ACKEN = 1;
            while (I2C1CON1bits.ACKEN)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.ACKDT = 0;
            I2C2CON1bits.ACKEN = 1;
            while (I2C2CON1bits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.ACKDT = 0;
            I2C3CON1bits.ACKEN = 1;
            while (I2C3CON1bits.ACKEN)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1CON1bits.ACKDT = 1;
            I2C1CON1bits.ACKEN = 1;
            while (I2C1CON1bits.ACKEN)
            {
                ;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.ACKDT = 1;
            I2C2CON1bits.ACKEN = 1;
            while (I2C2CON1bits.ACKEN)
            {
                ;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.ACKDT = 1;
            I2C3CON1bits.ACKEN = 1;
            while (I2C3CON1bits.ACKEN)
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
        return -1;
    }

    switch (i2c)
    {
        case 0:
            I2C1TRN = data;
            if (I2C1STAT1bits.IWCOL)  // write collision detection
            {
                I2C1STAT1bits.BCL = 0;
                I2C1STAT1bits.IWCOL = 0;
                return -1;
            }

            while (I2C1STAT1bits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C1STAT1bits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    if I2C_COUNT >= 2
        case 1:
            I2C2TRN = data;
            if (I2C2STAT1bits.IWCOL)  // write collision detection
            {
                I2C2STAT1bits.BCL = 0;
                I2C2STAT1bits.IWCOL = 0;
                return -1;
            }

            while (I2C2STAT1bits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C2STAT1bits.ACKSTAT)  // test for ACK received
            {
                return -1;
            }
            break;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3TRN = data;
            if (I2C3STAT1bits.IWCOL)  // write collision detection
            {
                I2C3STAT1bits.BCL = 0;
                I2C3STAT1bits.IWCOL = 0;
                return -1;
            }

            while (I2C3STAT1bits.TRSTAT)
            {
                ;  // wait iddle
            }

            if (I2C3STAT1bits.ACKSTAT)  // test for ACK received
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
            I2C1CON1bits.RCEN = 1;
            while (I2C1CON1bits.RCEN)
            {
                ;
            }
            I2C1STAT1bits.I2COV = 0;
            return I2C1RCV;
#    if I2C_COUNT >= 2
        case 1:
            I2C2CON1bits.RCEN = 1;
            while (I2C2CON1bits.RCEN)
            {
                ;
            }
            I2C2STAT1bits.I2COV = 0;
            return I2C2RCV;
#    endif
#    if I2C_COUNT >= 3
        case 2:
            I2C3CON1bits.RCEN = 1;
            while (I2C3CON1bits.RCEN)
            {
                ;
            }
            I2C3STAT1bits.I2COV = 0;
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
