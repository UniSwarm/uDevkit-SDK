/**
 * @file nvm_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 11, 2023, 10:56 AM
 *
 * @brief NVM (Non Volatile Memory) support drivers for PIC32MK,
 * PIC32MX, PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip documents DS60001121G and DS60001193B:
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/60001121g.pdf
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/60001193B.pdf
 */

#include "nvm.h"

#include <archi.h>

#include <string.h>

static void _nvm_processOperation(void);

typedef enum
{
    NVM_OP_NOP = 0x0,
    NVM_OP_SINGLE_DOUBLE_WORD_PROGRAM = 0x1,
    NVM_OP_QUAD_DOUBLE_WORD_PROGRAM = 0x2,
    NVM_OP_ROW_PROGRAM = 0x3,
    NVM_OP_PAGE_ERASE = 0x4,
    NVM_OP_PROGRAM_ERASE = 0x7,
} NVM_OPERATION;

static void _nvm_processOperation(void)
{
    // disable interrupts
    uint32_t int_flag = disable_interrupt();

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

    // <ATOMIC BLOCK
    NVMKEY = 0x0U;
    NVMKEY = 0xAA996655U;
    NVMKEY = 0x556699AAU;
    NVMCONSET = _NVMCON_WR_MASK;
    // >ATOMIC BLOCK

    // restore DMA
    if (dma_flag == 0)
    {
        DMACONbits.SUSPEND = 0;
    }

    // restore interrupts
    if ((int_flag & 0x00000001) != 0)
    {
        enable_interrupt();
    }
}

int nvm_read(uint32_t address, uint32_t *data, uint32_t length)
{
    memcpy(data, KVA0_TO_KVA1(address), length);
    return 0;
}

int nvm_writeWord(uint32_t address, const uint32_t *data)
{
    // Set data, physical address and operation
    NVMDATA0 = *data;
    NVMADDR = KVA_TO_PA(address);
    NVMCONbits.WREN = 0;
    NVMCONbits.NVMOP = NVM_OP_SINGLE_DOUBLE_WORD_PROGRAM;

    // Enable write
    NVMCONbits.WREN = 1;

    // Launch write
    _nvm_processOperation();

    // Wait for finished
    while (NVMCONbits.WR)
    {
        ;
    }

    if ((NVMCON & (_NVMCON_WRERR_MASK | _NVMCON_LVDERR_MASK)) != 0)
    {
        return -1;
    }
    return 0;
}

int nvm_writeQuadWord(uint32_t address, const uint32_t *data)
{
    const uint32_t *ptrData = data;

    // Set data, physical address and operation
    NVMDATA0 = *(ptrData++);
    NVMDATA1 = *(ptrData++);
    NVMDATA2 = *(ptrData++);
    NVMDATA3 = *(ptrData++);
    NVMADDR = KVA_TO_PA(address);
    NVMCONbits.WREN = 0;
    NVMCONbits.NVMOP = NVM_OP_QUAD_DOUBLE_WORD_PROGRAM;

    // Enable write
    NVMCONbits.WREN = 1;

    // Launch write
    _nvm_processOperation();

    // Wait for finished
    while (NVMCONbits.WR != 0)
    {
        ;
    }

    if ((NVMCON & (_NVMCON_WRERR_MASK | _NVMCON_LVDERR_MASK)) != 0)
    {
        return -1;
    }
    return 0;
}

int nvm_writeRow(uint32_t address, const uint32_t *data)
{
    // Set data, physical address and operation
    NVMSRCADDR = (uint32_t)KVA_TO_PA(data);
    NVMADDR = KVA_TO_PA(address);
    NVMCONbits.WREN = 0;
    NVMCONbits.NVMOP = NVM_OP_ROW_PROGRAM;

    // Enable write
    NVMCONbits.WREN = 1;

    // Launch write
    _nvm_processOperation();

    // Wait for finished
    while (NVMCONbits.WR != 0)
    {
        ;
    }
    // Do not wait for finished, too long operation
    // pool WR outsite

    return 0;
}

int nvm_erasePage(uint32_t address)
{
    // Set physical address and operation
    NVMADDR = KVA_TO_PA(address);
    NVMCONbits.WREN = 0;
    NVMCONbits.NVMOP = NVM_OP_PAGE_ERASE;

    // Enable write
    NVMCONbits.WREN = 1;

    // Launch write
    _nvm_processOperation();

    // Do not wait for finished, too long operation
    // pool WR outsite

    return 0;
}
