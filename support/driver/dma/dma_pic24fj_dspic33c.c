/**
 * @file dma_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2026
 *
 * @date September 16, 2021, 09:55 PM
 *
 * @brief DMA support driver for PIC24FJ and dsPIC33C
 *
 * Implementation based on Microchip document DS30009742C:
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM,-Direct-Memory-Access-Controller-(DMA)-DS30009742C.pdf
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
    DMACONbits.DMAEN = 1;
    DMACONbits.PRSSEL = 1;  // Round-robin scheme
    // DMACONbits.PRSSEL = 0; // Fixed priority scheme
    DMAL = (uint16_t)addrLow;
    DMAH = (uint16_t)addrHigh;
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
            DMACH0bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            _DMA1IF = 0;
            _DMA1IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA1IP = 4;
            DMACH1bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            _DMA2IF = 0;
            _DMA2IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA2IP = 4;
            DMACH2bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            _DMA3IF = 0;
            _DMA3IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA3IP = 4;
            DMACH3bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            _DMA4IF = 0;
            _DMA4IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA4IP = 4;
            DMACH4bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            _DMA5IF = 0;
            _DMA5IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA5IP = 4;
            DMACH5bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            _DMA6IF = 0;
            _DMA6IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA6IP = 4;
            DMACH6bits.CHEN = 1;  // enable dma module
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            _DMA7IF = 0;
            _DMA7IE = (_dmas[dma].handler != NULL) ? 1 : 0;
            _DMA7IP = 4;
            DMACH7bits.CHEN = 1;  // enable dma module
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
            DMACH0bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            _DMA1IE = 0;
            DMACH1bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            _DMA2IE = 0;
            DMACH2bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            _DMA3IE = 0;
            DMACH3bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            _DMA4IE = 0;
            DMACH4bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            _DMA5IE = 0;
            DMACH5bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            _DMA6IE = 0;
            DMACH6bits.CHEN = 0;  // disable dma module
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            _DMA7IE = 0;
            DMACH7bits.CHEN = 0;  // disable dma module
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
            DMACH0bits.SAMODE = addrMode;  // source mode
            DMASRC0 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.SAMODE = addrMode;  // source mode
            DMASRC1 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.SAMODE = addrMode;  // source mode
            DMASRC2 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.SAMODE = addrMode;  // source mode
            DMASRC3 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.SAMODE = addrMode;  // source mode
            DMASRC4 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.SAMODE = addrMode;  // source mode
            DMASRC5 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.SAMODE = addrMode;  // source mode
            DMASRC6 = (uint16_t)srcAddr;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.SAMODE = addrMode;  // source mode
            DMASRC7 = (uint16_t)srcAddr;
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
            DMACH0bits.DAMODE = addrMode;  // destination mode
            DMADST0 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.DAMODE = addrMode;  // destination mode
            DMADST1 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.DAMODE = addrMode;  // destination mode
            DMADST2 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.DAMODE = addrMode;  // destination mode
            DMADST3 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.DAMODE = addrMode;  // destination mode
            DMADST4 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.DAMODE = addrMode;  // destination mode
            DMADST5 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.DAMODE = addrMode;  // destination mode
            DMADST6 = (uint16_t)dstAddr;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.DAMODE = addrMode;  // destination mode
            DMADST7 = (uint16_t)dstAddr;
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
            DMAINT0bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMAINT1bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMAINT2bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMAINT3bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMAINT4bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMAINT5bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMAINT6bits.CHSEL = trigger;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMAINT7bits.CHSEL = trigger;
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
            DMACH0bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.TRMODE = transferMode;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.TRMODE = transferMode;
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
            DMACNT0 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACNT1 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACNT2 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACNT3 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACNT4 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACNT5 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACNT6 = transferCount;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACNT7 = transferCount;
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
            DMACH0bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.SIZE = wordSize;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.SIZE = wordSize;
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

    switch (dma)
    {
#    if (DMA_COUNT >= 1) && !defined(DMA1_DISABLE)
        case DMA1_ID:
            DMACH0bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH0bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH1bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH2bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH3bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH4bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH5bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH6bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.RELOAD = ((options & DMA_OPTION_RELOAD) == DMA_OPTION_RELOAD) ? 1 : 0;  // RELOAD on next operation
            DMACH7bits.NULLW = ((options & DMA_OPTION_NULLW) == DMA_OPTION_NULLW) ? 1 : 0;     // dummy write is initiated
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
            DMACH0bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE)
        case DMA2_ID:
            DMACH1bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE)
        case DMA3_ID:
            DMACH2bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE)
        case DMA4_ID:
            DMACH3bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE)
        case DMA5_ID:
            DMACH4bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE)
        case DMA6_ID:
            DMACH5bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE)
        case DMA7_ID:
            DMACH6bits.CHREQ = 1;
            break;
#    endif
#    if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE)
        case DMA8_ID:
            DMACH7bits.CHREQ = 1;
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
    if (_dmas[DMA1_ID].handler)
    {
        (*_dmas[DMA1_ID].handler)();
    }

    _DMA0IF = 0;
}
#endif

#if (DMA_COUNT >= 2) && !defined(DMA2_DISABLE) && !defined(DMA2_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA1Interrupt(void)
{
    if (_dmas[DMA2_ID].handler)
    {
        (*_dmas[DMA2_ID].handler)();
    }

    _DMA1IF = 0;
}
#endif

#if (DMA_COUNT >= 3) && !defined(DMA3_DISABLE) && !defined(DMA3_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA2Interrupt(void)
{
    if (_dmas[DMA3_ID].handler)
    {
        (*_dmas[DMA3_ID].handler)();
    }

    _DMA2IF = 0;
}
#endif

#if (DMA_COUNT >= 4) && !defined(DMA4_DISABLE) && !defined(DMA4_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA3Interrupt(void)
{
    if (_dmas[DMA4_ID].handler)
    {
        (*_dmas[DMA4_ID].handler)();
    }

    _DMA3IF = 0;
}
#endif

#if (DMA_COUNT >= 5) && !defined(DMA5_DISABLE) && !defined(DMA5_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA4Interrupt(void)
{
    if (_dmas[DMA5_ID].handler)
    {
        (*_dmas[DMA5_ID].handler)();
    }

    _DMA4IF = 0;
}
#endif

#if (DMA_COUNT >= 6) && !defined(DMA6_DISABLE) && !defined(DMA6_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA5Interrupt(void)
{
    if (_dmas[DMA6_ID].handler)
    {
        (*_dmas[DMA6_ID].handler)();
    }

    _DMA5IF = 0;
}
#endif

#if (DMA_COUNT >= 7) && !defined(DMA7_DISABLE) && !defined(DMA7_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA6Interrupt(void)
{
    if (_dmas[DMA7_ID].handler)
    {
        (*_dmas[DMA7_ID].handler)();
    }

    _DMA6IF = 0;
}
#endif

#if (DMA_COUNT >= 8) && !defined(DMA8_DISABLE) && !defined(DMA8_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _DMA7Interrupt(void)
{
    if (_dmas[DMA8_ID].handler)
    {
        (*_dmas[DMA8_ID].handler)();
    }

    _DMA7IF = 0;
}
#endif
