/**
 * @file qei_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief Quadrature Encoder Interface support simulator driver
 */

#include "qei_sim.h"

static uint8_t qei_state = 0;

/**
 * @brief Gives a free QEI device number and open it
 * @return QEI device number
 */
rt_dev_t qei_getFreeDevice(void)
{
    rt_dev_t device;
#if QEI_COUNT>=1
    if (!(qei_state & 0x01))
    {
        qei_state = qei_state | 0x01;
        device = MKDEV(DEV_CLASS_QEI, 1);
        qei_open(device);
        return device;
    }
#endif
#if QEI_COUNT>=2
    if (!(qei_state & 0x02))
    {
        qei_state = qei_state | 0x02;
        device = MKDEV(DEV_CLASS_QEI, 2);
        qei_open(device);
        return device;
    }
#endif

    return NULLDEV;
}

/**
 * @brief Open a QEI
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_open(rt_dev_t device)
{
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei == 1)
    {
        qei_state = qei_state | 0x01;
    }
#endif
#if QEI_COUNT>=2
    if (qei == 2)
    {
        qei_state = qei_state | 0x02;
    }
#endif
    return 0;
}

/**
 * @brief Close a QEI
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_close(rt_dev_t device)
{
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
    {
        return -1;
    }
    if (qei == 1)
    {
        qei_state = qei_state & 0xFE;
    }
#endif
#if QEI_COUNT>=2
    if (qei == 2)
    {
        qei_state = qei_state & 0xFD;
    }
#endif
    return 0;
}

/**
 * @brief Enable the specified QEI device
 * @param device QEI device number
 * @return 0 if ok, -1 in case of error
 */
int qei_enable(rt_dev_t device)
{
#if QEI_COUNT>=1
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

#if QEI_COUNT>=1
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
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return -1;
    }
#else
    return -1;
#endif

    // TODO SIM

#if QEI_COUNT>=1
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
    UDK_UNUSED(dividerg);
    return 0;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_getValue(rt_dev_t device)
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
