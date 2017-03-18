/**
 * @file qei_pic24f_dspic33f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC33FJ,
 * PIC24F, PIC24FJ and PIC24HJ
 *
 * Implementation based on Microchip document DS70208C :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/70208C.pdf
 */

#include "qei.h"

#include <archi.h>

#if !defined (QEI_COUNT) || QEI_COUNT==0
  #warning No device QEI periph on the current device
#endif

uint16_t qeis[QEI_COUNT] = {0};

/**
 * @brief Gives a free QEI device number and open it
 * @return QEI device number
 */
rt_dev_t qei_getFreeDevice()
{
#if QEI_COUNT>=1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < QEI_COUNT; i++)
        if (qeis[i] == 0)
            break;

    if (i == QEI_COUNT)
        return NULLDEV;
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
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
        return -1;
    if (qeis[qei] == 1)
        return -1;

    qeis[qei] = 0b0000011100000000;

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
int qei_releaseDevice(rt_dev_t device)
{
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
        return -1;

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
#if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
        return -1;
#else
    return -1;
#endif

#if QEI_COUNT>=1
    if (qei == 0)
        QEI1CON = qeis[1];
#endif
#if QEI_COUNT>=2
    if (qei == 1)
        QEI2CON = qeis[2];
#endif

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

#if QEI_COUNT>=1
    if (qei == 0)
        QEI1CONbits.QEIM = 0b000;
#endif
#if QEI_COUNT>=2
    if (qei == 1)
        QEI2CONbits.QEIM = 0b000;
#endif

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
    // TODO implement me
    return 0;
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_getValue(rt_dev_t device)
{
  #if QEI_COUNT>=1
    uint8_t qei = MINOR(device);
    if (qei == 0)
        return POS1CNT;
  #endif
  #if QEI_COUNT>=2
    if (qei == 1)
        return POS2CNT;
  #endif
    return 0;
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    // TODO implement me
    return 0;
}
