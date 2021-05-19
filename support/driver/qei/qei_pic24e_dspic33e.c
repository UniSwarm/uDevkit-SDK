/**
 * @file qei_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2021
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC33EP,
 * dsPIC33EV, PIC24EP, dsPIC33CH and dsPIC33CK
 *
 * Implementation based on Microchip document DS70601B :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/S15.pdf
 */

#include "qei.h"

#include <archi.h>

#if !defined(QEI_COUNT) || QEI_COUNT == 0
#    warning No device QEI periph on the current device
#else
uint8_t qeis[QEI_COUNT] = {0};
#endif

/**
 * @brief Gives a free QEI device number and open it
 * @return QEI device number
 */
rt_dev_t qei_getFreeDevice(void)
{
#if QEI_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < QEI_COUNT; i++)
    {
        if (qeis[i] == 0)
        {
            break;
        }
    }

    if (i == QEI_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_QEI, i);

    qei_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open a QEI
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_open(rt_dev_t device)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
    {
        return -1;
    }
    if (qeis[qei] == 1)
    {
        return -1;
    }

    qeis[qei] = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close a QEI
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_close(rt_dev_t device)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
    {
        return -1;
    }

    qei_disable(device);

    qeis[qei] = 0;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified QEI device
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_enable(rt_dev_t device)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return -1;
    }
#else
    return -1;
#endif

#if QEI_COUNT >= 1
    if (qei == 0)
    {
        QEI1CONbits.QEIEN = 1;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2CONbits.QEIEN = 1;
    }
#endif

#if QEI_COUNT >= 1
    return 0;
#endif
}

/**
 * @brief Disable the specified QEI device
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_disable(rt_dev_t device)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return -1;
    }
#else
    return -1;
#endif

#if QEI_COUNT >= 1
    if (qei == 0)
    {
        QEI1CONbits.QEIEN = 0;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2CONbits.QEIEN = 0;
    }
#endif

#if QEI_COUNT >= 1
    return 0;
#endif
}

/**
 * Configures the specified QEI device with bits in config
 * @param device QEI device number
 * @param config config bit
 * @return 0 if ok, -1 in case of error
 */
int qei_setConfig(rt_dev_t device, uint16_t config)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei == 0)
    {
        INDX1CNTH = 0xFFFF;
        INDX1CNTL = 0xFFFF;

        QEI1GECH = 0xFFFF;
        QEI1GECL = 0xFFFF;

        POS1CNTL = 0;
        POS1CNTH = 0;

        QEI1IOCbits.QEAPOL = config & QEI_AB_INV;
        QEI1IOCbits.QEBPOL = config & QEI_AB_INV;
        QEI1IOCbits.IDXPOL = config & QEI_I_INV;

        return 0;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        INDX2CNTH = 0xFFFF;
        INDX2CNTL = 0xFFFF;

        QEI2GECH = 0xFFFF;
        QEI2GECL = 0xFFFF;

        POS2CNTL = 0;
        POS2CNTH = 0;

        return 0;
    }
#endif
    return -1;
}

/**
 * Configure the hardware input filter on QEIx A, B and I
 * @param device QEI device number
 * @param divider Clock divider
 * @return 0 if ok, -1 in case of error
 */
int qei_setInputFilterConfig(rt_dev_t device, uint16_t divider)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);

    uint8_t fltren;
    if (divider == 0)
    {
        fltren = 0;
    }
    else
    {
        fltren = 1;

        uint8_t shift = 0;
        // find the position number of the first bit, rounded up
        // ex : input 64 -> output 6
        // ex : input 65 -> output 7
        while ((shift < 16) && !((divider - 1) & 0x8000))
        {
            divider <<= 1;
            shift++;
        }
        divider = 16 - shift;
    }

    if (qei == 0)
    {
        QEI1IOCbits.FLTREN = fltren;
        QEI1IOCbits.QFDIV = divider;

        return 0;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2IOCbits.FLTREN = fltren;
        QEI2IOCbits.QFDIV = divider;

        return 0;
    }
#endif
    return -1;
}

/**
 * Set QEI position counter to work in modulo mode
 * @param device QEI device number
 * @param minimum The position counter minimum value. will loop to the maximum value
 * @param maximum The position counter maximum value. will loop to the minimum value
 * @return 0 if ok, -1 in case of error
 */
int qei_setModuloCountMode(rt_dev_t device, int32_t minimum, int32_t maximum)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);

    if (qei == 0)
    {
        QEI1CONbits.PIMOD = 6;  // modulo count mode for position counter
        QEI1LECL = minimum & 0xFFFF;
        QEI1LECH = (minimum >> 16) & 0xFFFF;
        QEI1GECL = maximum & 0xFFFF;
        QEI1GECH = (maximum >> 16) & 0xFFFF;

        return 0;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2CONbits.PIMOD = 6;  // modulo count mode for position counter
        QEI2LECL = minimum & 0xFFFF;
        QEI2LECH = (minimum >> 16) & 0xFFFF;
        QEI2GECL = maximum & 0xFFFF;
        QEI2GECH = (maximum >> 16) & 0xFFFF;

        return 0;
    }
#endif
    return -1;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_getValue(rt_dev_t device)
{
    qei_type tmp32 = 0;
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei == 0)
    {
        tmp32 = (uint32_t)POS1CNTL;
        tmp32 += (uint32_t)POS1HLD << 16;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        tmp32 = (uint32_t)POS2CNTL;
        tmp32 += (uint32_t)POS2HLD << 16;
    }
#endif
    return tmp32;
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    UDK_UNUSED(device);
    UDK_UNUSED(home);

    // TODO implement me
    return 0;
}
