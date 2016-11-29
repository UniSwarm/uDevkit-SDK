/**
 * @file qei_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief Quadrature Encoder Interface support simulator driver
 */

#include "qei_sim.h"

uint8_t qei_state = 0;

/**
 * @brief Gives a free QEI device number
 * @return QEI device number
 */
rt_dev_t qei_getFreeDevice()
{
#if QEI_COUNT>=1
    if (!(qei_state & 0x01))
    {
        qei_state = qei_state | 0x01;
        return MKDEV(DEV_CLASS_QEI, 1);
    }
#endif
#if QEI_COUNT>=2
    if (!(qei_state & 0x02))
    {
        qei_state = qei_state | 0x02;
        return MKDEV(DEV_CLASS_QEI, 2);
    }
#endif

    return NULLDEV;
}

/**
 * @brief Release a QEI
 * @param device QEI device number
 */
void qei_releaseDevice(rt_dev_t device)
{
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei == 1)
        qei_state = qei_state & 0xFE;
#endif
#if QEI_COUNT>=2
    if (qei == 2)
        qei_state = qei_state & 0xFD;
#endif
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
    if (qei > QEI_COUNT)
        return -1;
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
        return -1;
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
    
    return 0;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
uint32_t qei_getValue(rt_dev_t device)
{
    uint32_t tmp32 = 0;

    // TODO SIM
    
    return tmp32;
}

int qei_setHomeValue(rt_dev_t device, uint32_t home)
{
    // TODO implement me
    
    return 0;
}
