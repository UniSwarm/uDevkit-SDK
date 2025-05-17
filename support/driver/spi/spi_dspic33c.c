/**
 * @file spi_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date April 7, 2025, 10:45 AM
 *
 * @brief SPI communication support driver for dsPIC33CK and dsPIC33CH
 *
 * Implementation based on Microchip document DS70005136B :
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/ReferenceManuals/dsPIC33-PIC24-FRM-Serial-Peripheral-Interface-SPI-with-Audio-Codec-Support-DS70005136.pdf
 */

#include "spi.h"

#include <archi.h>
#include <driver/sysclock.h>
#include <sys/fifo.h>

#if !defined(SPI_COUNT) || SPI_COUNT == 0
#    warning "No spi bus on the current device or unknow device"
#endif

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
    uint32_t freq;
    uint8_t bitLength;
    spi_status flags;
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct spi_dev _spis[] = {
#if SPI_COUNT >= 1
    {.freq = 0, .flags = {{.val = SPI_FLAG_UNUSED}}},
#endif
#if SPI_COUNT >= 2
    {.freq = 0, .flags = {{.val = SPI_FLAG_UNUSED}}},
#endif
#if SPI_COUNT >= 3
    {.freq = 0, .flags = {{.val = SPI_FLAG_UNUSED}}},
#endif
#if SPI_COUNT >= 4
    {.freq = 0, .flags = {{.val = SPI_FLAG_UNUSED}}},
#endif
};

/**
 * @brief Gives a free spi bus device number and open it
 * @return spi bus device number
 */
rt_dev_t spi_getFreeDevice(void)
{
    uint8_t i;
    rt_dev_t device;

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
    device = MKDEV(DEV_CLASS_SPI, i);

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
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            SPI1CON1Lbits.SPIEN = 1;  // enable spi module
            SPI1CON1Lbits.MSTEN = 1;
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            SPI2CON1Lbits.SPIEN = 1;  // enable spi module
            SPI2CON1Lbits.MSTEN = 1;
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            SPI3CON1Lbits.SPIEN = 1;  // enable spi module
            SPI3CON1Lbits.MSTEN = 1;
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
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            SPI1CON1Lbits.SPIEN = 0;  // disable spi
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            SPI2CON1Lbits.SPIEN = 0;  // disable spi
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            SPI3CON1Lbits.SPIEN = 0;  // disable spi
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
        return -1;
    }

    return (_spis[spi].flags.enabled == 1);
}

/**
 * @brief Sets the speed of receive and transmit of the specified spi bus device
 * @param device spi bus device number
 * @param freq of receive and transmit clock in Hz
 * @return 0 if ok, -1 in case of error
 */
int spi_setFreq(rt_dev_t device, uint32_t freq)
{
    uint8_t enabled;
    uint32_t systemClockPeriph;
    uint16_t sdiv;

    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    if (freq == 0)
    {
        return -1;
    }

    _spis[spi].freq = freq;

    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_SPI);
    sdiv = systemClockPeriph / freq;

    // disable device if it is already enabled
    if (_spis[spi].flags.enabled == 1)
    {
        enabled = 1;
        spi_disable(device);
    }

    switch (spi)
    {
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            SPI1BRGH = sdiv;
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            SPI2BRGH = sdiv;
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            SPI3BRGH = sdiv;
            break;
#endif
    }

    // re enable device if it was already enabled
    if (enabled == 1)
    {
        spi_enable(device);
    }

    return 0;
}

/**
 * @brief Gets the true baud speed of the specified spi bus device
 * @param device spi bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t spi_freq(rt_dev_t device)
{
    uint32_t freq, systemClockPeriph;
    uint16_t sdiv = 1;

    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return 0;
    }

    switch (spi)
    {
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            sdiv = SPI1BRGH;
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            sdiv = SPI2BRGH;
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            sdiv = SPI3BRGH;
            break;
#endif
    }
    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_SPI);
    freq = systemClockPeriph / sdiv;

    return freq;
}

/**
 * @brief Gets the effective baud speed of the specified spi bus device
 * @param device spi bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t spi_effectiveFreq(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return 0;
    }

    return _spis[spi].freq;
}

/**
 * @brief Sets the bit length of the specified spi bus
 * @param device spi devive bus
 * @param bitLength 8 bits or 16 bits
 * @return 0 if ok, -1 in case of error
 */
int spi_setBitLength(rt_dev_t device, uint8_t bitLength)
{
    uint8_t bit16;
    uint8_t bit32;
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    if (bitLength == 32)
    {
        bit16 = 0;
        bit32 = 1;
    }
    else if (bitLength == 16)
    {
        bit16 = 1;
        bit32 = 0;
    }
    else if (bitLength == 8)
    {
        bit16 = 0;
        bit32 = 0;
    }
    else
    {
        return -1;
    }
    _spis[spi].bitLength = bitLength;

    switch (spi)
    {
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            SPI1CON1bits.MODE16 = bit16;
            SPI1CON1bits.MODE32 = bit32;
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            SPI2CON1bits.MODE16 = bit16;
            SPI2CON1bits.MODE32 = bit32;
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            SPI3CON1bits.MODE16 = bit16;
            SPI3CON1bits.MODE32 = bit32;
            break;
#endif
    }

    return 0;
}

/**
 * @brief Gets the bit length of the spi bus
 * @param device spi devive bus
 * @return length of word in bits
 */
uint8_t spi_bitLength(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return 0;
    }

    return _spis[spi].bitLength;
}

ssize_t spi_exchange(rt_dev_t device, const char *tx, char *rx, size_t size)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    const char *tx_ptr = tx;
    char *rx_ptr = rx;

    switch (spi)
    {
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
        case SPI1_ID:
            for (size_t i = 0; i < size; i++)
            {
                while (SPI1STATLbits.SRMT == 0)
                    ;
                SPI1BUFL = *tx_ptr;
                tx_ptr++;

                while (SPI1STATLbits.SPIRBE == 1)
                    ;
                *rx_ptr = SPI1BUFL;

                rx_ptr++;
            }
            break;
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
        case SPI2_ID:
            for (size_t i = 0; i < size; i++)
            {
                while (SPI2STATLbits.SRMT == 0)
                    ;
                SPI2BUFL = *tx_ptr;
                tx_ptr++;

                while (SPI2STATLbits.SPIRBE == 1)
                    ;
                *rx_ptr = SPI2BUFL;

                rx_ptr++;
            }
            break;
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
        case SPI3_ID:
            for (size_t i = 0; i < size; i++)
            {
                while (SPI3STATLbits.SRMT == 0)
                    ;
                SPI3BUFL = *tx_ptr;
                tx_ptr++;

                while (SPI3STATLbits.SPIRBE == 1)
                    ;
                *rx_ptr = SPI3BUFL;

                rx_ptr++;
            }
            break;
#endif
    }

    return size;
}

ssize_t spi_write(rt_dev_t device, const char *data, size_t size)
{
    return -1;
}

int spi_flush(rt_dev_t device)
{
    return -1;
}

ssize_t spi_read(rt_dev_t device, char *data, size_t size_max)
{
    return -1;
}
