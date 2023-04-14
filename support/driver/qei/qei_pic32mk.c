/**
 * @file qei_pic32mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
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

#if !defined(QEI_COUNT) || QEI_COUNT == 0
#    warning "No qei on the current device or unknow device"
#endif

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
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
 * @brief QEI sdk state
 * @param device qei device number
 * @return true if qei was openned by qei_open function
 */
bool qei_isOpened(rt_dev_t device)
{
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
    {
        return false;
    }

    return (_qeis[qei].flags.used == 1);
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

    _qeis[qei].flags.enabled = 1;

    switch (qei)
    {
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            QEI1CONbits.QEIEN = 1;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2CONbits.QEIEN = 1;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            QEI3CONbits.QEIEN = 1;
            break;
#    endif
#    if (QEI_COUNT >= 4) && !defined(QEI4_DISABLE)
        case QEI4_ID:
            QEI4CONbits.QEIEN = 1;
            break;
#    endif
#    if (QEI_COUNT >= 5) && !defined(QEI5_DISABLE)
        case QEI5_ID:
            QEI5CONbits.QEIEN = 1;
            break;
#    endif
#    if (QEI_COUNT >= 6) && !defined(QEI6_DISABLE)
        case QEI6_ID:
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

    _qeis[qei].flags.enabled = 0;

    switch (qei)
    {
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            QEI1CONbits.QEIEN = 0;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2CONbits.QEIEN = 0;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            QEI3CONbits.QEIEN = 0;
            break;
#    endif
#    if (QEI_COUNT >= 4) && !defined(QEI4_DISABLE)
        case QEI4_ID:
            QEI4CONbits.QEIEN = 0;
            break;
#    endif
#    if (QEI_COUNT >= 5) && !defined(QEI5_DISABLE)
        case QEI5_ID:
            QEI5CONbits.QEIEN = 0;
            break;
#    endif
#    if (QEI_COUNT >= 6) && !defined(QEI6_DISABLE)
        case QEI6_ID:
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
 * @brief QEI sdk enabled state
 * @param device qei device number
 * @return true if qei was enabled by qei_enable function
 */
bool qei_isEnabled(rt_dev_t device)
{
    uint8_t qei = MINOR(device);
    if (qei >= QEI_COUNT)
    {
        return false;
    }

    return (_qeis[qei].flags.enabled == 1);
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
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            // TODO implement me
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            break;
#    endif
#    if (QEI_COUNT >= 4) && !defined(QEI4_DISABLE)
        case QEI4_ID:
            break;
#    endif
#    if (QEI_COUNT >= 5) && !defined(QEI5_DISABLE)
        case QEI5_ID:
            break;
#    endif
#    if (QEI_COUNT >= 6) && !defined(QEI6_DISABLE)
        case QEI6_ID:
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
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            return POS1CNT;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            return POS2CNT;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            return POS3CNT;
#    endif
#    if (QEI_COUNT >= 4) && !defined(QEI4_DISABLE)
        case QEI4_ID:
            return POS4CNT;
#    endif
#    if (QEI_COUNT >= 5) && !defined(QEI5_DISABLE)
        case QEI5_ID:
            return POS5CNT;
#    endif
#    if (QEI_COUNT >= 6) && !defined(QEI6_DISABLE)
        case QEI6_ID:
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
