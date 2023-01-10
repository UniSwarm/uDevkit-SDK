/**
 * @file qei_pic32mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date June 19, 2017, 21:40 PM
 *
 * @brief Quadrature Encoder Interface support driver for PIC32MK
 *
 * Implementation based on Microchip document DS60001346A :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/60001346A.pdf
 */

#include "qei.h"

#include <archi.h>

#if defined(QEI_COUNT) && QEI_COUNT > 0
static uint8_t _qeis[QEI_COUNT] = {0};
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
        if (_qeis[i] == 0)
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
    if (_qeis[qei] == 1)
    {
        return -1;
    }

    _qeis[qei] = 1;

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

    _qeis[qei] = 0;
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

    switch (qei)
    {
        case 0:
            QEI1CONbits.QEIEN = 1;
            break;
#    if QEI_COUNT >= 2
        case 1:
            QEI2CONbits.QEIEN = 1;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            QEI3CONbits.QEIEN = 1;
            break;
#    endif
#    if QEI_COUNT >= 4
        case 3:
            QEI4CONbits.QEIEN = 1;
            break;
#    endif
#    if QEI_COUNT >= 5
        case 4:
            QEI5CONbits.QEIEN = 1;
            break;
#    endif
#    if QEI_COUNT >= 6
        case 5:
            QEI6CONbits.QEIEN = 1;
            break;
#    endif
    }
    return 0;
#else
    return -1;
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

    switch (qei)
    {
        case 0:
            QEI1CONbits.QEIEN = 0;
            break;
#    if QEI_COUNT >= 2
        case 1:
            QEI2CONbits.QEIEN = 0;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            QEI3CONbits.QEIEN = 0;
            break;
#    endif
#    if QEI_COUNT >= 4
        case 3:
            QEI4CONbits.QEIEN = 0;
            break;
#    endif
#    if QEI_COUNT >= 5
        case 4:
            QEI5CONbits.QEIEN = 0;
            break;
#    endif
#    if QEI_COUNT >= 6
        case 5:
            QEI6CONbits.QEIEN = 0;
            break;
#    endif
    }
    return 0;
#else
    return -1;
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
    if (qei > QEI_COUNT)
    {
        return -1;
    }

    switch (qei)
    {
        case 0:
            // TODO implement me
            break;
#    if QEI_COUNT >= 2
        case 1:
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            break;
#    endif
#    if QEI_COUNT >= 4
        case 3:
            break;
#    endif
#    if QEI_COUNT >= 5
        case 4:
            break;
#    endif
#    if QEI_COUNT >= 6
        case 5:
            break;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * Configure the hardware input filter on QEIx A, B and I
 * @param device QEI device number
 * @param divider Clock divider
 * @return 0 if ok, -1 in case of error
 */
int qei_setInputFilterConfig(rt_dev_t device, uint16_t divider)
{
    // TODO implement me
    return 0;
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
    // TODO implement me
    return 0;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_value(rt_dev_t device)
{
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return -1;
    }

    switch (qei)
    {
        case 0:
            return POS1CNT;
#    if QEI_COUNT >= 2
        case 1:
            return POS2CNT;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            return POS3CNT;
#    endif
#    if QEI_COUNT >= 4
        case 3:
            return POS4CNT;
#    endif
#    if QEI_COUNT >= 5
        case 4:
            return POS5CNT;
#    endif
#    if QEI_COUNT >= 6
        case 5:
            return POS6CNT;
#    endif
    }
    return 0;
#else
    return -1;
#endif
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    // TODO implement me
    return 0;
}
