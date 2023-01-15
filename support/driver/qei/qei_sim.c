/**
 * @file qei_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief Quadrature Encoder Interface support simulator driver
 */

#include "qei_sim.h"

static uint8_t _qeis[QEI_COUNT] = {0};

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
    if (qei >= QEI_COUNT)
    {
        return -1;
    }
    if (qei > QEI_COUNT)
    {
        return -1;
    }
#else
    return -1;
#endif

    // TODO SIM

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

    // TODO SIM

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
    // TODO SIM
    UDK_UNUSED(device);
    UDK_UNUSED(config);
    return 0;
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
    UDK_UNUSED(device);
    UDK_UNUSED(divider);
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
    UDK_UNUSED(device);
    UDK_UNUSED(minimum);
    UDK_UNUSED(maximum);
    return 0;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_value(rt_dev_t device)
{
    UDK_UNUSED(device);

    qei_type tmp32 = 0;

    // TODO SIM

    return tmp32;
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    UDK_UNUSED(device);
    UDK_UNUSED(home);

    // TODO implement me

    return 0;
}
