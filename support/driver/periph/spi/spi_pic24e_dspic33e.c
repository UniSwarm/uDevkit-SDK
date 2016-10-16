/**
 * @file spi_pic24_dspic30_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date October 10, 2016, 10:31 AM
 *
 * @brief SPI communication support driver for dsPIC33EP, dsPIC33EV and PIC24EP
 */

#include "spi.h"

#include "driver/sysclock.h"

#include <xc.h>

#if !defined (SPI_COUNT) || SPI_COUNT==0
  #warning "No spi bus on the current device or unknow device"
#endif

#define SPI_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned bit16 : 1;
            unsigned : 5;
        };
        uint8_t val;
    };
} spi_status;

struct spi_dev
{
    uint32_t freq;
    spi_status flags;
};

struct spi_dev spis[] = {
    {
        .freq = 0,
        .flags = {{.val = SPI_FLAG_UNUSED}}
    },
#if SPI_COUNT>=2
    {
        .freq = 0,
        .flags = {{.val = SPI_FLAG_UNUSED}}
    },
#endif
#if SPI_COUNT>=3
    {
        .freq = 0,
        .flags = {{.val = SPI_FLAG_UNUSED}}
    },
#endif
#if SPI_COUNT>=4
    {
        .freq = 0,
        .flags = {{.val = SPI_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free spi bus device number
 * @return spi bus device number
 */
rt_dev_t spi_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < SPI_COUNT; i++)
        if (spis[i].flags.val == SPI_FLAG_UNUSED)
            break;

    if (i == SPI_COUNT)
        return NULLDEV;

    spis[i].flags.used = 1;

    return MKDEV(DEV_CLASS_SPI, i);
}

/**
 * @brief Release an spi bus device
 * @param device spi bus device number
 */
void spi_releaseDevice(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
        return;

    spis[spi].flags.val = SPI_FLAG_UNUSED;
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
        return -1;

    spis[spi].flags.enabled = 1;

    switch (spi)
    {
    case 0:
        SPI1STATbits.SPIEN = 1;  // enable spi module
        break;
#if SPI_COUNT>=2
    case 1:
        SPI2STATbits.SPIEN = 1;  // enable spi module
        break;
#endif
#if SPI_COUNT>=3
    case 2:
        SPI3STATbits.SPIEN = 1;  // enable spi module
        break;
#endif
#if SPI_COUNT>=4
    case 3:
        SPI4STATbits.SPIEN = 1;  // enable spi module
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
        return -1;

    spis[spi].flags.enabled = 0;

    switch (spi)
    {
    case 0:
        SPI1STATbits.SPIEN = 0;  // disable spi
        break;
#if SPI_COUNT>=2
    case 1:
        SPI2STATbits.SPIEN = 0;  // disable spi
        break;
#endif
#if SPI_COUNT>=3
    case 2:
        SPI3STATbits.SPIEN = 0;  // disable spi
        break;
#endif
#if SPI_COUNT>=4
    case 3:
        SPI4STATbits.SPIEN = 0;  // disable spi
        break;
#endif
    }

    return 0;
}

/**
 * @brief Sets the speed of receive and transmit of the specified spi bus device
 * @param device spi bus device number
 * @param freq of receive and transmit clock in Hz
 * @return 0 if ok, -1 in case of error
 */
int spi_setfreq(rt_dev_t device, uint32_t freq)
{
    uint32_t systemClockPeriph;
    uint16_t sdiv;
    uint8_t sdivp, sdivs;

    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
        return -1;

    if (freq == 0)
        return -1;

    spis[spi].freq = freq;

    systemClockPeriph = sysclock_getPeriphClock();
    sdiv = systemClockPeriph / freq;

    if (sdivp == 1 && sdivs == 1) // Do not set the Primary and Secondary prescalers to the value of 1:1 at the same time.
        sdivs = 2;

    switch (spi)
    {
    case 0:
        SPI1CON1bits.PPRE = sdivp;
        SPI1CON1bits.SPRE = sdivs;
        break;
#if SPI_COUNT>=2
    case 1:
        SPI2CON1bits.PPRE = sdivp;
        SPI2CON1bits.SPRE = sdivs;
        break;
#endif
#if SPI_COUNT>=3
    case 2:
        SPI3CON1bits.PPRE = sdivp;
        SPI3CON1bits.SPRE = sdivs;
        break;
#endif
#if SPI_COUNT>=4
    case 3:
        SPI4CON1bits.PPRE = sdivp;
        SPI4CON1bits.SPRE = sdivs;
        break;
#endif
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
    uint16_t sdiv;

    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
        return 0;

    switch (spi)
    {
    case 0:
        sdiv = SPI1BRG;
        break;
#if SPI_COUNT>=2
    case 1:
        sdiv = SPI2BRG;
        break;
#endif
#if SPI_COUNT>=3
    case 2:
        sdiv = SPI3BRG;
        break;
#endif
    }

    systemClockPeriph = sysclock_getPeriphClock();
    freq = systemClockPeriph / (sdiv + 2); // TODO add PGD period to be exact

    return freq;
}

/**
 * @brief Gets the effective baud speed of the specified spi bus device
 * @param device spi bus device number
 * @return speed of receive and transmit in bauds (bits / s)
 */
uint32_t spi_effectivefreq(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
        return 0;

    return spis[spi].freq;
}
