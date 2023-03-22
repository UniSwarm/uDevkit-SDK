/**
 * @file spi_pic32.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2023
 *
 * @date March 22, 2023, 10:32 PM
 *
 * @brief SPI support for udevkit for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61106G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61106G.pdf
 */

#include "spi.h"

#include <archi.h>

enum
{
    SPI_FLAG_UNUSED = 0x00
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
} spi_status;

struct spi_dev
{
    spi_status flags;
    uint8_t bitLength;
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct spi_dev _spis[] = {
#if SPI_COUNT >= 1
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
#if SPI_COUNT >= 2
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
#if SPI_COUNT >= 3
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
#if SPI_COUNT >= 4
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
#if SPI_COUNT >= 5
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
#if SPI_COUNT >= 6
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8},
#endif
};

/**
 * @brief Gives a free spi bus device number and open it
 * @return spi bus device number
 */
rt_dev_t spi_getFreeDevice(void)
{
    uint8_t i;
    for (i = 0; i < SPI_COUNT; i++)
    {
        if (_spis[i].flags.val == SPI_FLAG_UNUSED)
        {
            break;
        }
    }

    if (i == SPI_COUNT)
    {
        return NULLDEV;
    }
    rt_dev_t device = MKDEV(DEV_CLASS_SPI, i);

    spi_open(device);

    return device;
}

/**
 * @brief Open an spi bus device
 * @param device spi bus device number
 */
int spi_open(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }
    if (_spis[spi].flags.used == 1)
    {
        return -1;
    }

    _spis[spi].flags.used = 1;
    // STATIC_FIFO_INIT(_spis[spi].buff, SPI_BUFF_SIZE);

    return 0;
}

/**
 * @brief Close and release an spi bus device
 * @param device spi bus device number
 */
int spi_close(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].flags.val = SPI_FLAG_UNUSED;

    return spi_disable(device);
}

/**
 * @brief SPI sdk state
 * @param device spi device number
 * @return true if spi was openned by spi_open function
 */
bool spi_isOpened(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    return (_spis[spi].flags.used == 1);
}

/**
 * @brief Enable the specified spi bus device
 * @param device spi bus device number
 * @return 0 if ok, -1 in case of error
 */
int spi_enable(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].flags.enabled = 1;

    switch (spi)
    {
        case 0:
            SPI1CONbits.ON = 1;  // enable spi module
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            SPI4CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 5
        case 4:
            SPI5CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 6
        case 5:
            SPI6CONbits.ON = 1;  // enable spi module
            break;
#endif
    }

    return 0;
}

/**
 * @brief Disable the specified spi bus device
 * @param device spi bus device number
 * @return 0 if ok, -1 in case of error
 */
int spi_disable(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].flags.enabled = 0;

    switch (spi)
    {
        case 0:
            SPI1CONbits.ON = 0;  // enable spi module
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2CONbits.ON = 0;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3CONbits.ON = 0;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            SPI4CONbits.ON = 0;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 5
        case 4:
            SPI5CONbits.ON = 0;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 6
        case 5:
            SPI6CONbits.ON = 0;  // enable spi module
            break;
#endif
    }

    return 0;
}

/**
 * @brief SPI sdk enabled state
 * @param device spi device number
 * @return true if spi was enabled by spi_enable function
 */
bool spi_isEnabled(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return false;
    }

    return (_spis[spi].flags.enabled == 1);
}

/**
 * @brief Sets the bit length of the specified spi bus
 * @param device spi devive bus
 * @param bitLength 8 bits or 16 bits
 * @return 0 if ok, -1 in case of error
 */
int spi_setBitLength(rt_dev_t device, uint8_t bitLength)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    uint8_t modeBits;
    switch (bitLength)
    {
        case 8:
            modeBits = 0b00;
            break;

        case 16:
            modeBits = 0b01;
            break;

        case 32:
            modeBits = 0b10;
            break;

        default:
            return -1;
    }
    _spis[spi].bitLength = bitLength;

    switch (spi)
    {
        case 0:
            SPI1CONbits.MODE16 = modeBits & 0x01;
            SPI1CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2CONbits.MODE16 = modeBits & 0x01;
            SPI2CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3CONbits.MODE16 = modeBits & 0x01;
            SPI3CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            SPI4CONbits.MODE16 = modeBits & 0x01;
            SPI4CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#endif
#if SPI_COUNT >= 5
        case 4:
            SPI5CONbits.MODE16 = modeBits & 0x01;
            SPI5CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#endif
#if SPI_COUNT >= 6
        case 5:
            SPI6CONbits.MODE16 = modeBits & 0x01;
            SPI6CONbits.MODE32 = (modeBits >> 1) & 0x01;
            break;
#endif
    }

    return 0;
}

uint8_t spi_bitLength(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return 0;
    }
    return _spis[spi].bitLength;
}

ssize_t spi_write(rt_dev_t device, const char *data, size_t size)
{
    // TODO IMPLEMENT ME
    UDK_UNUSED(device);
    UDK_UNUSED(data);
    UDK_UNUSED(size);
    return -1;
}

int spi_flush(rt_dev_t device)
{
    // TODO IMPLEMENT ME
    UDK_UNUSED(device);
    return -1;
}

ssize_t spi_read(rt_dev_t device, char *data, size_t size_max)
{
    // TODO IMPLEMENT ME
    UDK_UNUSED(device);
    UDK_UNUSED(data);
    UDK_UNUSED(size_max);
    return -1;
}
