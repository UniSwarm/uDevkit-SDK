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
#include <driver/int.h>

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
    void (*txHandler)(void);
    void (*rxHandler)(void);
    void (*errorHandler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#ifndef INT_MODE
#    define INT_MODE INT_DEFAULT_MODE
#endif
#ifndef SPI_INTERRUPT_PRIORITY
#    define SPI_INTERRUPT_PRIORITY 4
#endif
#ifndef SPI1_INT_TX_PRIORITY
#    define SPI1_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI1_INT_RX_PRIORITY
#    define SPI1_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI1_INT_FAULT_PRIORITY
#    define SPI1_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI2_INT_TX_PRIORITY
#    define SPI2_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI2_INT_RX_PRIORITY
#    define SPI2_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI2_INT_FAULT_PRIORITY
#    define SPI2_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI3_INT_TX_PRIORITY
#    define SPI3_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI3_INT_RX_PRIORITY
#    define SPI3_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI3_INT_FAULT_PRIORITY
#    define SPI3_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI4_INT_TX_PRIORITY
#    define SPI4_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI4_INT_RX_PRIORITY
#    define SPI4_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI4_INT_FAULT_PRIORITY
#    define SPI4_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI5_INT_TX_PRIORITY
#    define SPI5_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI5_INT_RX_PRIORITY
#    define SPI5_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI5_INT_FAULT_PRIORITY
#    define SPI5_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI6_INT_TX_PRIORITY
#    define SPI6_INT_TX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI6_INT_RX_PRIORITY
#    define SPI6_INT_RX_PRIORITY SPI_INTERRUPT_PRIORITY
#endif
#ifndef SPI6_INT_FAULT_PRIORITY
#    define SPI6_INT_FAULT_PRIORITY SPI_INTERRUPT_PRIORITY
#endif

static struct spi_dev _spis[] = {
#if SPI_COUNT >= 1
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
#if SPI_COUNT >= 2
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
#if SPI_COUNT >= 3
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
#if SPI_COUNT >= 4
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
#if SPI_COUNT >= 5
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
#if SPI_COUNT >= 6
    {.flags = {{.val = SPI_FLAG_UNUSED}}, .bitLength = 8, .txHandler = NULL, .rxHandler = NULL, .errorHandler = NULL},
#endif
};

#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
void SPI1TxInterrupt(void);
void SPI1RxInterrupt(void);
void SPI1FaultInterrupt(void);
#endif
#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
void SPI2TxInterrupt(void);
void SPI2RxInterrupt(void);
void SPI2FaultInterrupt(void);
#endif
#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
void SPI3TxInterrupt(void);
void SPI3RxInterrupt(void);
void SPI3FaultInterrupt(void);
#endif
#if (SPI_COUNT >= 4) && !defined(SPI4_DISABLE)
void SPI4TxInterrupt(void);
void SPI4RxInterrupt(void);
void SPI4FaultInterrupt(void);
#endif
#if (SPI_COUNT >= 5) && !defined(SPI5_DISABLE)
void SPI5TxInterrupt(void);
void SPI5RxInterrupt(void);
void SPI5FaultInterrupt(void);
#endif
#if (SPI_COUNT >= 6) && !defined(SPI6_DISABLE)
void SPI6TxInterrupt(void);
void SPI6RxInterrupt(void);
void SPI6FaultInterrupt(void);
#endif

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
            _SPI1TXIF = 0;
            _SPI1TXIP = SPI1_INT_TX_PRIORITY;
            _SPI1TXIE = 0;

            _SPI1RXIF = 0;
            _SPI1RXIP = SPI1_INT_RX_PRIORITY;
            _SPI1RXIE = 0;

            _SPI1EIF = 0;
            _SPI1EIP = SPI1_INT_FAULT_PRIORITY;
            _SPI1EIE = 0;

            SPI1CONbits.ON = 1;  // enable spi module
            break;
#if SPI_COUNT >= 2
        case 1:
            _SPI2TXIF = 0;
            _SPI2TXIP = SPI2_INT_TX_PRIORITY;
            _SPI2TXIE = 0;

            _SPI2RXIF = 0;
            _SPI2RXIP = SPI2_INT_RX_PRIORITY;
            _SPI2RXIE = 0;

            _SPI2EIF = 0;
            _SPI2EIP = SPI2_INT_FAULT_PRIORITY;
            _SPI2EIE = 0;

            SPI2CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            _SPI3TXIF = 0;
            _SPI3TXIP = SPI3_INT_TX_PRIORITY;
            _SPI3TXIE = 0;

            _SPI3RXIF = 0;
            _SPI3RXIP = SPI3_INT_RX_PRIORITY;
            _SPI3RXIE = 0;

            _SPI3EIF = 0;
            _SPI3EIP = SPI3_INT_FAULT_PRIORITY;
            _SPI3EIE = 0;

            SPI3CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            _SPI4TXIF = 0;
            _SPI4TXIP = SPI4_INT_TX_PRIORITY;
            _SPI4TXIE = 0;

            _SPI4RXIF = 0;
            _SPI4RXIP = SPI4_INT_RX_PRIORITY;
            _SPI4RXIE = 0;

            _SPI4EIF = 0;
            _SPI4EIP = SPI4_INT_FAULT_PRIORITY;
            _SPI4EIE = 0;

            SPI4CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 5
        case 4:
            _SPI5TXIF = 0;
            _SPI5TXIP = SPI5_INT_TX_PRIORITY;
            _SPI5TXIE = 0;

            _SPI5RXIF = 0;
            _SPI5RXIP = SPI5_INT_RX_PRIORITY;
            _SPI5RXIE = 0;

            _SPI5EIF = 0;
            _SPI5EIP = SPI5_INT_FAULT_PRIORITY;
            _SPI5EIE = 0;

            SPI5CONbits.ON = 1;  // enable spi module
            break;
#endif
#if SPI_COUNT >= 6
        case 5:
            _SPI6TXIF = 0;
            _SPI6TXIP = SPI6_INT_TX_PRIORITY;
            _SPI6TXIE = 0;

            _SPI6RXIF = 0;
            _SPI6RXIP = SPI6_INT_RX_PRIORITY;
            _SPI6RXIE = 0;

            _SPI6EIF = 0;
            _SPI6EIP = SPI6_INT_FAULT_PRIORITY;
            _SPI6EIE = 0;

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
            _SPI1TXIE = 0;
            _SPI1RXIE = 0;
            _SPI1EIE = 0;

            SPI1CONbits.ON = 0;  // disable spi module
            break;
#if SPI_COUNT >= 2
        case 1:
            _SPI2TXIE = 0;
            _SPI2RXIE = 0;
            _SPI2EIE = 0;

            SPI2CONbits.ON = 0;  // disable spi module
            break;
#endif
#if SPI_COUNT >= 3
        case 2:
            _SPI3TXIE = 0;
            _SPI3RXIE = 0;
            _SPI3EIE = 0;

            SPI3CONbits.ON = 0;  // disable spi module
            break;
#endif
#if SPI_COUNT >= 4
        case 3:
            _SPI4TXIE = 0;
            _SPI4RXIE = 0;
            _SPI4EIE = 0;

            SPI4CONbits.ON = 0;  // disable spi module
            break;
#endif
#if SPI_COUNT >= 5
        case 4:
            _SPI5TXIE = 0;
            _SPI5RXIE = 0;
            _SPI5EIE = 0;

            SPI5CONbits.ON = 0;  // disable spi module
            break;
#endif
#if SPI_COUNT >= 6
        case 5:
            _SPI6TXIE = 0;
            _SPI6RXIE = 0;
            _SPI6EIE = 0;

            SPI6CONbits.ON = 0;  // disable spi module
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

int spi_setTxHandler(rt_dev_t device, void (*handler)(void))
{
#if SPI_COUNT >= 1
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].txHandler = handler;
    if (_spis[spi].flags.enabled == 1)
    {
        spi_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

int spi_setRxHandler(rt_dev_t device, void (*handler)(void))
{
#if SPI_COUNT >= 1
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].rxHandler = handler;
    if (_spis[spi].flags.enabled == 1)
    {
        spi_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

int spi_setErrorHandler(rt_dev_t device, void (*handler)(void))
{
#if SPI_COUNT >= 1
    uint8_t spi = MINOR(device);
    if (spi >= SPI_COUNT)
    {
        return -1;
    }

    _spis[spi].errorHandler = handler;
    if (_spis[spi].flags.enabled == 1)
    {
        spi_enable(device);
    }

    return 0;
#else
    return -1;
#endif
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

// Ints
#if (SPI_COUNT >= 1) && !defined(SPI1_DISABLE)
void INT_ISR(_SPI1_TX_VECTOR, SPI1_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI1TxInterrupt(void)
{
    if (_spis[0].txHandler != NULL)
    {
        (*_spis[0].txHandler)();
    }

    _SPI1TXIF = 0;
}

void INT_ISR(_SPI1_RX_VECTOR, SPI1_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI1RxInterrupt(void)
{
    if (_spis[0].rxHandler != NULL)
    {
        (*_spis[0].rxHandler)();
    }

    _SPI1RXIF = 0;
}

void INT_ISR(_SPI1_FAULT_VECTOR, SPI1_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI1FaultInterrupt(void)
{
    if (_spis[0].errorHandler != NULL)
    {
        (*_spis[0].errorHandler)();
    }

    _SPI1EIF = 0;
}
#endif

#if (SPI_COUNT >= 2) && !defined(SPI2_DISABLE)
void INT_ISR(_SPI2_TX_VECTOR, SPI2_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI2TxInterrupt(void)
{
    if (_spis[1].txHandler != NULL)
    {
        (*_spis[1].txHandler)();
    }

    _SPI2TXIF = 0;
}

void INT_ISR(_SPI2_RX_VECTOR, SPI2_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI2RxInterrupt(void)
{
    if (_spis[1].rxHandler != NULL)
    {
        (*_spis[1].rxHandler)();
    }

    _SPI2RXIF = 0;
}

void INT_ISR(_SPI2_FAULT_VECTOR, SPI2_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI2FaultInterrupt(void)
{
    if (_spis[1].errorHandler != NULL)
    {
        (*_spis[1].errorHandler)();
    }

    _SPI2EIF = 0;
}
#endif

#if (SPI_COUNT >= 3) && !defined(SPI3_DISABLE)
void INT_ISR(_SPI3_TX_VECTOR, SPI3_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI3TxInterrupt(void)
{
    if (_spis[2].txHandler != NULL)
    {
        (*_spis[2].txHandler)();
    }

    _SPI3TXIF = 0;
}

void INT_ISR(_SPI3_RX_VECTOR, SPI3_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI3RxInterrupt(void)
{
    if (_spis[2].rxHandler != NULL)
    {
        (*_spis[2].rxHandler)();
    }

    _SPI3RXIF = 0;
}

void INT_ISR(_SPI3_FAULT_VECTOR, SPI3_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI3FaultInterrupt(void)
{
    if (_spis[2].errorHandler != NULL)
    {
        (*_spis[2].errorHandler)();
    }

    _SPI3EIF = 0;
}
#endif

#if (SPI_COUNT >= 4) && !defined(SPI4_DISABLE)
void INT_ISR(_SPI4_TX_VECTOR, SPI4_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI4TxInterrupt(void)
{
    if (_spis[3].txHandler != NULL)
    {
        (*_spis[3].txHandler)();
    }

    _SPI4TXIF = 0;
}

void INT_ISR(_SPI4_RX_VECTOR, SPI4_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI4RxInterrupt(void)
{
    if (_spis[3].rxHandler != NULL)
    {
        (*_spis[3].rxHandler)();
    }

    _SPI4RXIF = 0;
}

void INT_ISR(_SPI4_FAULT_VECTOR, SPI4_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI4FaultInterrupt(void)
{
    if (_spis[3].errorHandler != NULL)
    {
        (*_spis[3].errorHandler)();
    }

    _SPI4EIF = 0;
}
#endif

#if (SPI_COUNT >= 5) && !defined(SPI5_DISABLE)
void INT_ISR(_SPI5_TX_VECTOR, SPI5_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI5TxInterrupt(void)
{
    if (_spis[4].txHandler != NULL)
    {
        (*_spis[4].txHandler)();
    }

    _SPI5TXIF = 0;
}

void INT_ISR(_SPI5_RX_VECTOR, SPI5_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI5RxInterrupt(void)
{
    if (_spis[4].rxHandler != NULL)
    {
        (*_spis[4].rxHandler)();
    }

    _SPI5RXIF = 0;
}

void INT_ISR(_SPI5_FAULT_VECTOR, SPI5_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI5FaultInterrupt(void)
{
    if (_spis[4].errorHandler != NULL)
    {
        (*_spis[4].errorHandler)();
    }

    _SPI5EIF = 0;
}
#endif

#if (SPI_COUNT >= 6) && !defined(SPI6_DISABLE)
void INT_ISR(_SPI6_TX_VECTOR, SPI6_INT_TX_PRIORITY, INT_MODE) __attribute__((weak)) SPI6TxInterrupt(void)
{
    if (_spis[5].txHandler != NULL)
    {
        (*_spis[5].txHandler)();
    }

    _SPI6TXIF = 0;
}

void INT_ISR(_SPI6_RX_VECTOR, SPI6_INT_RX_PRIORITY, INT_MODE) __attribute__((weak)) SPI6RxInterrupt(void)
{
    if (_spis[5].rxHandler != NULL)
    {
        (*_spis[5].rxHandler)();
    }

    _SPI6RXIF = 0;
}

void INT_ISR(_SPI6_FAULT_VECTOR, SPI6_INT_FAULT_PRIORITY, INT_MODE) __attribute__((weak)) SPI6FaultInterrupt(void)
{
    if (_spis[5].errorHandler != NULL)
    {
        (*_spis[5].errorHandler)();
    }

    _SPI6EIF = 0;
}
#endif
