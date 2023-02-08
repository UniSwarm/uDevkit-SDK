/**
 * @file spi_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 10, 2016, 10:31 AM
 *
 * @brief SPI communication support driver for dsPIC33EP, dsPIC33EV and PIC24EP
 *
 * Implementation based on Microchip document DS70005185A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005185a.pdf
 */

#include "spi.h"

#include <archi.h>
#include <driver/sysclock.h>
#include <sys/fifo.h>

#if !defined(SPI_COUNT) || SPI_COUNT == 0
#    warning "No spi bus on the current device or unknow device"
#endif

#define SPI_BUFF_SIZE 32

#define SPI_FLAG_UNUSED 0x00
typedef struct
{
    union
    {
        struct
        {
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
    uint8_t sdivp, sdivs;
    spi_status flags;

    STATIC_FIFO(buff, SPI_BUFF_SIZE);
};

static struct spi_dev _spis[] = {
    {.freq = 0, .flags = {{.val = SPI_FLAG_UNUSED}}},
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
    STATIC_FIFO_INIT(_spis[spi].buff, SPI_BUFF_SIZE);

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
            SPI1STATbits.SPIEN = 1;  // enable spi module
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2STATbits.SPIEN = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3STATbits.SPIEN = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 4
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
    {
        return -1;
    }

    _spis[spi].flags.enabled = 0;

    switch (spi)
    {
        case 0:
            SPI1STATbits.SPIEN = 0;  // disable spi
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2STATbits.SPIEN = 0;  // disable spi
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3STATbits.SPIEN = 0;  // disable spi
            break;
#endif
#if SPI_COUNT >= 4
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
int spi_setFreq(rt_dev_t device, uint32_t freq)
{
    uint8_t enabled;
    uint32_t systemClockPeriph;
    uint16_t sdiv;
    uint16_t sdivp, sdivs;

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

    // primary divisor   : 1 (0x3), 4(0x2), 16(0x1), 64(0x0)
    // secondary divisor : 1 (0x7) to 8(0x0)
    if (sdiv <= 8)
    {
        sdivp = 0x3;  // primary = 1
        sdivs = sdiv;
    }
    else if (sdiv <= 32)
    {
        sdivp = 0x2;  // primary = 4
        sdivs = sdiv >> 2;
    }
    else if (sdiv <= 128)
    {
        sdivp = 0x1;  // primary = 16
        sdivs = sdiv >> 4;
    }
    else
    {
        sdivp = 0x0;  // primary = 64
        sdivs = sdiv >> 6;
        if (sdivs > 8)
        {
            sdivs = 8;
        }
    }

    // Do not set the Primary and Secondary prescalers to the value of 1:1 at the same time.
    if (sdivp == 0x3 && sdivs == 1)
    {
        sdivs = 2;
    }

    sdivs = ~(sdivs - 1);

    _spis[spi].sdivp = sdivp;
    _spis[spi].sdivs = sdivs;

    switch (spi)
    {
        case 0:
            SPI1CON1bits.PPRE = sdivp;
            SPI1CON1bits.SPRE = sdivs;
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2CON1bits.PPRE = sdivp;
            SPI2CON1bits.SPRE = sdivs;
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3CON1bits.PPRE = sdivp;
            SPI3CON1bits.SPRE = sdivs;
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            SPI4CON1bits.PPRE = sdivp;
            SPI4CON1bits.SPRE = sdivs;
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
    uint16_t sdivp, sdivs;

    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return 0;
    }

    // secondary divisor : 1 (0x7) to 8(0x0)
    sdivs = ~(_spis[spi].sdivs) + 1;

    // primary divisor   : 1 (0x3), 4(0x2), 16(0x1), 64(0x0)
    sdivp = _spis[spi].sdivp;
    switch (sdivp)
    {
        case 0x3:
            sdivp = 1;
            break;

        case 0x2:
            sdivp = 4;
            break;

        case 0x1:
            sdivp = 16;
            break;

        case 0x0:
            sdivp = 64;
            break;
    }

    systemClockPeriph = sysclock_periphFreq(SYSCLOCK_CLOCK_SPI);
    freq = systemClockPeriph / (sdivp * sdivs);

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
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    if (bitLength == 16)
    {
        bit16 = 1;
    }
    else if (bitLength == 8)
    {
        bit16 = 0;
    }
    else
    {
        return -1;
    }
    _spis[spi].flags.bit16 = bit16;

    switch (spi)
    {
        case 0:
            SPI1CON1bits.MODE16 = bit16;
            break;
#if SPI_COUNT >= 2
        case 1:
            SPI2CON1bits.MODE16 = bit16;
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            SPI3CON1bits.MODE16 = bit16;
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            SPI4CON1bits.MODE16 = bit16;
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

    if (_spis[spi].flags.bit16 == 1)
    {
        return 16;
    }
    return 8;
}

ssize_t spi_write(rt_dev_t device, const char *data, size_t size)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    switch (spi)
    {
        case 0:
            while (SPI1STATbits.SPITBF)
            {
                ;
            }
            break;
#if SPI_COUNT >= 2
        case 1:
            while (SPI2STATbits.SPITBF)
            {
                ;
            }
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            while (SPI3STATbits.SPITBF)
            {
                ;
            }
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            while (SPI4STATbits.SPITBF)
            {
                ;
            }
            break;
#endif
    }

    return 0;
}

/**
 * @brief Wait until all data in transmit buffer will be sended
 * @param device spi bus device
 * @return -1 in case of error, 0 otherwise
 */
int spi_flush(rt_dev_t device)
{
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    if (_spis[spi].flags.enabled != 1)
    {
        return -1;
    }

    switch (spi)
    {
        case 0:
            while (!SPI1STATbits.SRMPT)
            {
                ;  // buffer not empty
            }
            break;
#if SPI_COUNT >= 2
        case 1:
            while (!SPI2STATbits.SRMPT)
            {
                ;
            }
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            while (!SPI3STATbits.SRMPT)
            {
                ;
            }
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            while (!SPI4STATbits.SRMPT)
            {
                ;
            }
            break;
#endif
    }

    return 0;
}

ssize_t spi_read(rt_dev_t device, char *data, size_t size_max)
{
    size_t size_read;
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    size_read = fifo_pop(&_spis[spi].buff, data, size_max);

    return size_read;
}

#if SPI_COUNT >= 1
void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void)
{
    char uart_tmpchar[1];
    while (!U1STAbits.UTXBF && fifo_pop(&_spis[0].buff, uart_tmpchar, 1) == 1)
    {
        SPI1BUF = uart_tmpchar[0];
    }
    _SPI1IF = 0;

    // rec
    char rec[4];
    rec[0] = SPI1BUF;

    fifo_push(&_spis[0].buff, rec, 1);

    _U1RXIF = 0;
}
#endif
