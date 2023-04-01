/**
 * @file qei_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
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
        case 0:
            INDX1CNTH = 0xFFFF;
            INDX1CNTL = 0xFFFF;

            QEI1GECH = 0xFFFF;
            QEI1GECL = 0xFFFF;

            POS1CNTL = 0;
            POS1CNTH = 0;

            QEI1IOCbits.QEAPOL = config & QEI_AB_INV;
            QEI1IOCbits.QEBPOL = config & QEI_AB_INV;
            QEI1IOCbits.IDXPOL = config & QEI_I_INV;
            break;
#    if QEI_COUNT >= 2
        case 1:
            INDX2CNTH = 0xFFFF;
            INDX2CNTL = 0xFFFF;

            QEI2GECH = 0xFFFF;
            QEI2GECL = 0xFFFF;

            POS2CNTL = 0;
            POS2CNTH = 0;

            QEI2IOCbits.QEAPOL = config & QEI_AB_INV;
            QEI2IOCbits.QEBPOL = config & QEI_AB_INV;
            QEI2IOCbits.IDXPOL = config & QEI_I_INV;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            INDX3CNTH = 0xFFFF;
            INDX3CNTL = 0xFFFF;

            QEI3GECH = 0xFFFF;
            QEI3GECL = 0xFFFF;

            POS3CNTL = 0;
            POS3CNTH = 0;

            QEI3IOCbits.QEAPOL = config & QEI_AB_INV;
            QEI3IOCbits.QEBPOL = config & QEI_AB_INV;
            QEI3IOCbits.IDXPOL = config & QEI_I_INV;
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
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return -1;
    }

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

    switch (qei)
    {
        case 0:
            QEI1IOCbits.FLTREN = fltren;
            QEI1IOCbits.QFDIV = divider;
            break;
#    if QEI_COUNT >= 2
        case 1:
            QEI2IOCbits.FLTREN = fltren;
            QEI2IOCbits.QFDIV = divider;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            QEI3IOCbits.FLTREN = fltren;
            QEI3IOCbits.QFDIV = divider;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
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
    if (qei > QEI_COUNT)
    {
        return -1;
    }

    switch (qei)
    {
        case 0:
            QEI1CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI1LECL = minimum & 0xFFFF;
            QEI1LECH = (minimum >> 16) & 0xFFFF;
            QEI1GECL = maximum & 0xFFFF;
            QEI1GECH = (maximum >> 16) & 0xFFFF;
            break;
#    if QEI_COUNT >= 2
        case 1:
            QEI2CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI2LECL = minimum & 0xFFFF;
            QEI2LECH = (minimum >> 16) & 0xFFFF;
            QEI2GECL = maximum & 0xFFFF;
            QEI2GECH = (maximum >> 16) & 0xFFFF;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            QEI3CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI3LECL = minimum & 0xFFFF;
            QEI3LECH = (minimum >> 16) & 0xFFFF;
            QEI3GECL = maximum & 0xFFFF;
            QEI3GECH = (maximum >> 16) & 0xFFFF;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * Returns the actual position of the specified QEI
 * @param device QEI device number
 * @return position
 */
qei_type qei_value(rt_dev_t device)
{
    qei_type tmp32 = 0;
#if QEI_COUNT >= 1
    uint8_t qei = MINOR(device);
    if (qei > QEI_COUNT)
    {
        return 0;
    }

    switch (qei)
    {
        case 0:
            tmp32 = (uint32_t)POS1CNTL;
            tmp32 += (uint32_t)POS1HLD << 16;
            break;
#    if QEI_COUNT >= 2
        case 1:
            tmp32 = (uint32_t)POS2CNTL;
            tmp32 += (uint32_t)POS2HLD << 16;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            tmp32 = (uint32_t)POS3CNTL;
            tmp32 += (uint32_t)POS3HLD << 16;
#    endif
    }
#endif

    return tmp32;
}

int qei_setValue(rt_dev_t device, qei_type value)
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
            POS1CNTL = value & 0x0000FFFF;
            POS1HLD = value >> 16;
            break;
#    if QEI_COUNT >= 2
        case 1:
            POS2CNTL = value & 0x0000FFFF;
            POS2HLD = value >> 16;
            break;
#    endif
#    if QEI_COUNT >= 3
        case 2:
            POS3CNTL = value & 0x0000FFFF;
            POS3HLD = value >> 16;
#    endif
    }
#endif
    return 0;
}

int qei_setHomeValue(rt_dev_t device, qei_type home)
{
    UDK_UNUSED(device);
    UDK_UNUSED(home);

    // TODO implement me
    return 0;
}
