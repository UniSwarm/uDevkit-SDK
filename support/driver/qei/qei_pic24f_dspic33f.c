/**
 * @file qei_pic24f_dspic33f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
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

#if !defined(QEI_COUNT) || QEI_COUNT == 0
#    warning "No qei on the current device or unknow device"
#endif

enum
{
    QEI_FLAG_UNUSED = 0x00
};
typedef struct
{
    union
    {
        struct
        {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned : 6;
        };
        uint8_t val;
    };
} qei_status;

struct qei_dev
{
    qei_status flags;
};

static struct qei_dev _qeis[] = {
#if QEI_COUNT >= 1
    {.flags = {{.val = QEI_FLAG_UNUSED}}},
#endif
};

/**
 * @brief Gives a free QEI device number and open it
 * @return QEI device number
 */
rt_dev_t qei_getFreeDevice(void)
{
#if QEI_COUNT >= 1
    uint8_t qei_id;
    for (qei_id = 0; qei_id < QEI_COUNT; qei_id++)
    {
        if (_qeis[qei_id].flags.used == 0)
        {
            break;
        }
    }
    if (qei_id == QEI_COUNT)
    {
        return NULLDEV;
    }

    rt_dev_t device = MKDEV(DEV_CLASS_QEI, qei_id);
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
    if (_qeis[qei].flags.used == 1)
    {
        return -1;
    }

    _qeis[qei].flags.used = 1;

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

    _qeis[qei].flags.used = 0;
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
        QEI1CON = 0b0000011100000000;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2CON = 0b0000011100000000;
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
        QEI1CONbits.QEIM = 0b000;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        QEI2CONbits.QEIM = 0b000;
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
    // TODO implement me
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
    if (qei == 0)
    {
        return POS1CNT;
    }
#endif
#if QEI_COUNT >= 2
    if (qei == 1)
    {
        return POS2CNT;
    }
#endif
    return 0;
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    // TODO implement me
    return 0;
}
