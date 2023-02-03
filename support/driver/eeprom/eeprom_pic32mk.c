/**
 * @file eeprom_pic32mk.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 18, 2023, 01:45 PM
 *
 * @brief EEPROM memory support drivers for PIC32MK
 */

#include "eeprom.h"

#include <archi.h>
#include <driver/sysclock.h>

#include <string.h>

#if EEPROM_COUNT > 0
static void _eeprom_processOperation(void);

typedef enum
{
    EEPROM_OP_CMDCFG = 0b100,
    EEPROM_OP_BULKERASE = 0b011,
    EEPROM_OP_PAGEERASE = 0b010,
    EEPROM_OP_WORDPGM = 0b001,
    EEPROM_OP_WORDREAD = 0b000,
} EEPROM_OPERATION;

static void _eeprom_processOperation(void)
{
    // disable interrupts
    uint32_t int_flag = disable_interrupt();

#    ifdef DMACON
    // disable DMA
    uint32_t dma_flag = DMACONbits.SUSPEND;
    if (dma_flag == 0)
    {
        DMACONbits.SUSPEND = 1;
        while ((DMACONbits.DMABUSY))
        {
            ;
        }
    }
#    endif  // DMACON

    // <ATOMIC BLOCK
    EEKEY = 0xEDB7;
    EEKEY = 0x1248;
    EECONSET = _EECON_RW_MASK;
    // >ATOMIC BLOCK

#    ifdef DMACON
    // restore DMA
    if (dma_flag == 0)
    {
        DMACONbits.SUSPEND = 0;
    }
#    endif  // DMACON

    // restore interrupts
    if ((int_flag & 0x00000001) != 0)
    {
        enable_interrupt();
    }
}
#endif

int eeprom_init(void)
{
#if EEPROM_COUNT > 0
    eeprom_reconfig();

    EECONbits.ON = 1;
    while (EECONbits.RDY == 0)
    {
        ;
    }

    EECONbits.WREN = 1;
    EECONbits.CMD = EEPROM_OP_CMDCFG;

    EEADDR = 0x00;
    EEDATA = DEVEE0;
    _eeprom_processOperation();
    eeprom_waitForReady();

    EEADDR = 0x04;
    EEDATA = DEVEE1;
    _eeprom_processOperation();
    eeprom_waitForReady();

    EEADDR = 0x08;
    EEDATA = DEVEE2;
    _eeprom_processOperation();
    eeprom_waitForReady();

    EEADDR = 0x0C;
    EEDATA = DEVEE3;
    _eeprom_processOperation();
    eeprom_waitForReady();

    return 0;
#else
    return -1;
#endif
}

int eeprom_readWord(uint32_t addr, uint32_t *data)
{
#if EEPROM_COUNT > 0
    if ((EECONbits.RW != 0))
    {
        return -1;
    }

    EECONbits.WREN = 0;
    EECONbits.CMD = EEPROM_OP_WORDREAD;
    EEADDR = addr & 0x00000FFC;
    EECONSET = _EECON_RW_MASK;
    eeprom_waitForReady();

    if (EECONbits.ERR != 0)
    {
        return -1;
    }

    *data = EEDATA;
    return 1;
#else
    return -1;
#endif
}

int eeprom_writeWord(uint32_t addr, uint32_t *data)
{
#if EEPROM_COUNT > 0
    if ((EECONbits.RW != 0))
    {
        return -1;
    }

    EEADDR = addr & 0x00000FFC;
    EECONbits.CMD = EEPROM_OP_WORDPGM;
    EECONbits.WREN = 1;
    EEDATA = *data;
    _eeprom_processOperation();
    eeprom_waitForReady();

    if (EECONbits.ERR != 0)
    {
        return -1;
    }

    return EEPROM_WORDS_WRITE_SIZE;
#else
    return -1;
#endif
}

bool eeprom_ready(void)
{
#if EEPROM_COUNT > 0
    return (EECONbits.RW != 0);
#else
    return false;
#endif
}

void eeprom_waitForReady(void)
{
#if EEPROM_COUNT > 0
    while (EECONbits.RW != 0)
    {
        ;
    }
#endif
}

void eeprom_reconfig(void)
{
#if EEPROM_COUNT > 0
    uint32_t pb2freq = sysclock_periphFreq(SYSCLOCK_CLOCK_PBCLK2);
    if (pb2freq < 40000000)
    {
        CFGCON2bits.EEWS = 0;
    }
    else if (pb2freq < 60000000)
    {
        CFGCON2bits.EEWS = 1;
    }
    else if (pb2freq < 80000000)
    {
        CFGCON2bits.EEWS = 2;
    }
    else if (pb2freq < 98000000)
    {
        CFGCON2bits.EEWS = 3;
    }
    else if (pb2freq < 118000000)
    {
        CFGCON2bits.EEWS = 4;
    }
    else
    {
        CFGCON2bits.EEWS = 5;
    }
#endif
}
