/**
 * @file qei_dspic33a_pic32a.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date June 8, 2025, 06:44 PM
 *
 * @brief QEI support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip document DS70005539C, DS70005591A, DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
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
#if QEI_COUNT >= 2
    {.flags = {{.val = QEI_FLAG_UNUSED}}},
#endif
#if QEI_COUNT >= 3
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
            QEI1CONbits.ON = 1;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2CONbits.ON = 1;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            QEI3CONbits.ON = 1;
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
            QEI1CONbits.ON = 0;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2CONbits.ON = 0;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            QEI3CONbits.ON = 0;
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
            INDX1CNT = 0xFFFF;

            QEI1GEC = 0xFFFF;

            POS1CNT = 0;

            QEI1IOCbits.QEAPOL = config & QEI_AB_INV;
            QEI1IOCbits.QEBPOL = config & QEI_AB_INV;
            QEI1IOCbits.IDXPOL = config & QEI_I_INV;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            INDX2CNT = 0xFFFF;

            QEI2GEC = 0xFFFF;

            POS2CNT = 0;

            QEI2IOCbits.QEAPOL = config & QEI_AB_INV;
            QEI2IOCbits.QEBPOL = config & QEI_AB_INV;
            QEI2IOCbits.IDXPOL = config & QEI_I_INV;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            INDX3CNT = 0xFFFF;

            QEI3GEC = 0xFFFF;

            POS3CNT = 0;

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
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            QEI1IOCbits.FLTREN = fltren;
            QEI1IOCbits.QFDIV = divider;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2IOCbits.FLTREN = fltren;
            QEI2IOCbits.QFDIV = divider;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
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
int qei_setModuloCountMode(rt_dev_t device, qei_type minimum, qei_type maximum)
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
            QEI1CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI1LEC = minimum;
            QEI1GEC = maximum;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            QEI2CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI2LEC = minimum;
            QEI2GEC = maximum;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            QEI3CONbits.PIMOD = 6;  // modulo count mode for position counter
            QEI3LEC = minimum;
            QEI3GEC = maximum;
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
#    if (QEI_COUNT >= 1) && !defined(QEI1_DISABLE)
        case QEI1_ID:
            POS1CNT = value;
            break;
#    endif
#    if (QEI_COUNT >= 2) && !defined(QEI2_DISABLE)
        case QEI2_ID:
            POS2CNT = value;
            break;
#    endif
#    if (QEI_COUNT >= 3) && !defined(QEI3_DISABLE)
        case QEI3_ID:
            POS3CNT = value;
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
