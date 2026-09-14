/**
 * @file dma_dspic33a_pic32a.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date September 14, 2026, 09:06 PM
 *
 * @brief DMA support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005539C, DS70005629C, DS70005591D and DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
 */

#include "dma.h"

#include <archi.h>

enum
{
    DMA_FLAG_UNUSED = 0x00
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
} dma_status;

struct dma_dev
{
    dma_status flags;
    void (*handler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA0Interrupt(void);
#endif
#if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA1Interrupt(void);
#endif
#if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA2Interrupt(void);
#endif
#if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA3Interrupt(void);
#endif
#if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA4Interrupt(void);
#endif
#if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA5Interrupt(void);
#endif
#if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA6Interrupt(void);
#endif
#if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA7Interrupt(void);
#endif

static struct dma_dev _dmas[] = {
#if DMA_COUNT >= 1
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 2
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 3
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 4
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 5
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 6
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 7
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
#if DMA_COUNT >= 8
    {.flags = {{.val = DMA_FLAG_UNUSED}}, .handler = NULL},
#endif
};

void dma_init(const void *addrLow, const void *addrHigh)
{
    DMACONbits.ON = 1;
    DMACONbits.PRIORITY = 1;  // Round-robin scheme
    // DMACONbits.PRIORITY = 0; // Fixed priority scheme
    DMALOW = (uint32_t)addrLow;
    DMAHIGH = (uint32_t)addrHigh;
}

/**
 * @brief Gives a free dma device number
 * @return dma device number
 */
rt_dev_t dma_getFreeDevice(void)
{
#if DMA_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < DMA_COUNT; i++)
    {
        if (_dmas[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == DMA_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_DMA, i);

    dma_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open a dma
 * @param device dma device number
 */
int dma_open(rt_dev_t device)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }
    if (_dmas[dma].flags.used == 1)
    {
        return -1;
    }

    _dmas[dma].flags.used = 1;
    _dmas[dma].handler = NULL;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close a dma
 * @param device dma device number
 */
int dma_close(rt_dev_t device)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    dma_disable(device);

    _dmas[dma].flags.val = DMA_FLAG_UNUSED;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief DMA sdk state
 * @param device dma device number
 * @return true if dma was openned by dma_open function
 */
bool dma_isOpened(rt_dev_t device)
{
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    return (_dmas[dma].flags.used == 1);
}

/**
 * @brief Enable the specified dma device
 * @param device dma device number
 * @return 0 if ok, -1 in case of error
 */
int dma_enable(rt_dev_t device)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    _dmas[dma].flags.enabled = 1;

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            _DMA0IF = 0;
            _DMA0IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA0IP = 4;
            DMA0CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            _DMA1IF = 0;
            _DMA1IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA1IP = 4;
            DMA1CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            _DMA2IF = 0;
            _DMA2IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA2IP = 4;
            DMA2CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            _DMA3IF = 0;
            _DMA3IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA3IP = 4;
            DMA3CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            _DMA4IF = 0;
            _DMA4IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA4IP = 4;
            DMA4CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            _DMA5IF = 0;
            _DMA5IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA5IP = 4;
            DMA5CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            _DMA6IF = 0;
            _DMA6IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA6IP = 4;
            DMA6CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            _DMA7IF = 0;
            _DMA7IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA7IP = 4;
            DMA7CHbits.CHEN = 1;  // enable dma module
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified dma device
 * @param device dma device number
 * @return 0 if ok, -1 in case of error
 */
int dma_disable(rt_dev_t device)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    _dmas[dma].flags.enabled = 0;

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            _DMA0IE = 0;
            DMA0CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            _DMA1IE = 0;
            DMA1CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            _DMA2IE = 0;
            DMA2CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            _DMA3IE = 0;
            DMA3CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            _DMA4IE = 0;
            DMA4CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            _DMA5IE = 0;
            DMA5CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            _DMA6IE = 0;
            DMA6CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            _DMA7IE = 0;
            DMA7CHbits.CHEN = 0;  // disable dma module
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief DMA sdk enabled state
 * @param device dma device number
 * @return true if dma was enabled by dma_enable function
 */
bool dma_isEnabled(rt_dev_t device)
{
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    return (_dmas[dma].flags.enabled == 1);
}

/**
 * @brief Sets the handler function that will be called on dma interrupt
 * @param device dma device number
 * @param handler void funtion pointer or null to remove the handler
 * @return 0 if ok, -1 in case of error
 */
int dma_setHandler(rt_dev_t device, void (*handler)(void))
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    _dmas[dma].handler = handler;
    if (_dmas[dma].flags.enabled == 1)
    {
        dma_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setSource(rt_dev_t device, const void *srcAddr, uint8_t addrMode)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.SAMODE = addrMode;  // source mode
            DMA0SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.SAMODE = addrMode;  // source mode
            DMA1SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.SAMODE = addrMode;  // source mode
            DMA2SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.SAMODE = addrMode;  // source mode
            DMA3SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.SAMODE = addrMode;  // source mode
            DMA4SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.SAMODE = addrMode;  // source mode
            DMA5SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.SAMODE = addrMode;  // source mode
            DMA6SRC = (uint32_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.SAMODE = addrMode;  // source mode
            DMA7SRC = (uint32_t)srcAddr;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setDestination(rt_dev_t device, void *dstAddr, uint8_t addrMode)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.DAMODE = addrMode;  // destination mode
            DMA0DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.DAMODE = addrMode;  // destination mode
            DMA1DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.DAMODE = addrMode;  // destination mode
            DMA2DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.DAMODE = addrMode;  // destination mode
            DMA3DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.DAMODE = addrMode;  // destination mode
            DMA4DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.DAMODE = addrMode;  // destination mode
            DMA5DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.DAMODE = addrMode;  // destination mode
            DMA6DST = (uint32_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.DAMODE = addrMode;  // destination mode
            DMA7DST = (uint32_t)dstAddr;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setTrigger(rt_dev_t device, uint8_t trigger)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6SELbits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7SELbits.CHSEL = trigger;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setTransferMode(rt_dev_t device, uint8_t transferMode)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.TRMODE = transferMode;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setTransferCount(rt_dev_t device, uint16_t transferCount)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CNT = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CNT = transferCount;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setWordSize(rt_dev_t device, uint8_t wordSize)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.SIZE = wordSize;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_setOptions(rt_dev_t device, uint8_t options)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }
    uint8_t reload = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;
    uint8_t nullw = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 0b01 : 0b00;
    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA0CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA0CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA0CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA1CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA1CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA1CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA2CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA2CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA2CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA3CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA3CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA3CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA4CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA4CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA4CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA5CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA5CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA5CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA6CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA6CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA6CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.RELOADC = reload;  // RELOAD count on next operation
            DMA7CHbits.RELOADD = reload;  // RELOAD destination on next operation
            DMA7CHbits.RELOADS = reload;  // RELOAD source on next operation
            DMA7CHbits.FLWCON = nullw;     // dummy write is initiated
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

int dma_softTrigger(rt_dev_t device)
{
#if DMA_COUNT >= 1
    uint8_t dma = MINOR(device);
    if (dma >= DMA_COUNT)
    {
        return -1;
    }

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMA0CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMA1CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMA2CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMA3CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMA4CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMA5CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMA6CHbits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMA7CHbits.CHREQ = 1;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

#if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE) && !defined(DMA1_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA0Interrupt(void)
{
    if (_dmas[DMA1_ID].handler != NULL)
    {
        (*_dmas[DMA1_ID].handler)();
    }

    _DMA0IF = 0;
}
#endif

#if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE) && !defined(DMA2_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA1Interrupt(void)
{
    if (_dmas[DMA2_ID].handler != NULL)
    {
        (*_dmas[DMA2_ID].handler)();
    }

    _DMA1IF = 0;
}
#endif

#if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE) && !defined(DMA3_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA2Interrupt(void)
{
    if (_dmas[DMA3_ID].handler != NULL)
    {
        (*_dmas[DMA3_ID].handler)();
    }

    _DMA2IF = 0;
}
#endif

#if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE) && !defined(DMA4_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA3Interrupt(void)
{
    if (_dmas[DMA4_ID].handler != NULL)
    {
        (*_dmas[DMA4_ID].handler)();
    }

    _DMA3IF = 0;
}
#endif

#if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE) && !defined(DMA5_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA4Interrupt(void)
{
    if (_dmas[DMA5_ID].handler != NULL)
    {
        (*_dmas[DMA5_ID].handler)();
    }

    _DMA4IF = 0;
}
#endif

#if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE) && !defined(DMA6_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA5Interrupt(void)
{
    if (_dmas[DMA6_ID].handler != NULL)
    {
        (*_dmas[DMA6_ID].handler)();
    }

    _DMA5IF = 0;
}
#endif

#if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE) && !defined(DMA7_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA6Interrupt(void)
{
    if (_dmas[DMA7_ID].handler != NULL)
    {
        (*_dmas[DMA7_ID].handler)();
    }

    _DMA6IF = 0;
}
#endif

#if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE) && !defined(DMA8_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA7Interrupt(void)
{
    if (_dmas[DMA8_ID].handler != NULL)
    {
        (*_dmas[DMA8_ID].handler)();
    }

    _DMA7IF = 0;
}
#endif
