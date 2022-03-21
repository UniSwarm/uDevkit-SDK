/**
 * @file nvm_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020-2021
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support drivers for dsPIC30F, dsPIC33FJ,
 * dsPIC33EP, dsPIC33EV, PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#include "nvm.h"

#include <archi.h>

#if !defined(NVM_FLASH_PAGE_BYTE) || NVM_FLASH_PAGE_BYTE == 0
#    warning "No flash on the current device or unknown device"
#endif

void nvm_writeDoubleWord(uint32_t addrWord, const char *data);

/**
 * @brief Reads a defined number of bytes flash memory
 * @param addrs address in bytes of the page to read
 * @param ramBuffer array of read data
 * @param size number of words to read
 */
ssize_t nvm_read(uint32_t addr, char *data, size_t size)
{
    uint16_t offset, i = 0;
    size_t sizeRemaining;
    ssize_t size_read;

    addr >>= 1;
    TBLPAG = addr >> 16;
    offset = addr;
    sizeRemaining = size;  // set the number of value to read

    while (sizeRemaining >= 3)  // read if there is more than 3 bytes to read
    {
        uint16_t data16h, data16l;
        data16h = __builtin_tblrdh(offset);  // read of high word
        data16l = __builtin_tblrdl(offset);  // read of low word

        data[i++] = (char)data16l;
        data[i++] = (char)(data16l >> 8);
        data[i++] = (char)data16h;

        offset += 2;
        sizeRemaining -= 3;

        if (offset == 0x0000)
        {
            TBLPAG++;  // TBLPAG value switch
        }
    }

    if ((sizeRemaining < 3) && (sizeRemaining > 0))  // read if there is less than 3 bytes to read
    {
        uint16_t data16l;
        data16l = __builtin_tblrdl(offset);
        data[i++] = (char)data16l;
        if (sizeRemaining == 2)
        {
            data[i++] = (char)(data16l >> 8);
        }
    }
    size_read = i;
    return size_read;
}

/**
 * @brief Writes 2 instrusction words in flash memory
 * @param addraddr of the page to write
 * @param data array of the data to write (2 * three bytes)
 */
void nvm_writeDoubleWord(uint32_t addrWord, const char *data)
{
    unsigned char *udata = (unsigned char *)data;

    NVMCON = 0x4001;  // Memory double-word program operation
    TBLPAG = 0xFA;    // write latch upper addr

    __builtin_tblwtl(0, (((uint16_t)udata[1]) << 8) + udata[0]);
    __builtin_tblwth(0, (uint8_t)udata[2]);  // load write latches

    __builtin_tblwtl(2, (((uint16_t)udata[4]) << 8) + udata[3]);
    __builtin_tblwth(2, (uint8_t)udata[5]);  // load write latches

    NVMADRL = addrWord;
    NVMADRH = addrWord >> 16;  // set target write address

    __builtin_disi(6);      // Disable interrupts for NVM unlock
    __builtin_write_NVM();  // unlock and wait until WR = 0
    while (NVMCONbits.WR == 1)
        ;
}

/**
 * @brief Writes a defined number of bytes in flash memory
 * @param addr address of the page to write
 * @param data array of the data to write
 * @param size size of the data to write in number of bytes
 */
ssize_t nvm_write(uint32_t addr, const char *data, size_t size)
{
    uint32_t currentAddr;
    size_t sizeRemaining, i;
    ssize_t size_write;
    char newData[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    addr >>= 1;
    currentAddr = addr;
    sizeRemaining = size;  // set the number of value to read

    if ((currentAddr & 0x0003) >= 2)  // if the address is not aligned
    {
        if (sizeRemaining < 3)  // if less than 3 bytes to write
        {
            for (i = 0; i < sizeRemaining; i++)
            {
                newData[i + 3] = data[i];
            }
            sizeRemaining = 0;
        }
        else  // if 3 bytes or more to write
        {
            for (i = 0; i < 3; i++)
            {
                newData[i + 3] = data[i];
            }
            sizeRemaining -= 3;
        }

        currentAddr = currentAddr & 0xFFFFFFC;
        nvm_writeDoubleWord(currentAddr, newData);

        currentAddr += 4;
        data += 3;
    }

    while (sizeRemaining > 6)  // if at least 6 bytes to write
    {
        nvm_writeDoubleWord(currentAddr, data);
        currentAddr += 4;
        data += 6;
        sizeRemaining -= 6;
    }

    if (sizeRemaining > 0)  // if less than 6 bytes to write
    {
        newData[3] = 0xFF;
        newData[4] = 0xFF;
        newData[5] = 0xFF;

        for (i = 0; i < sizeRemaining; i++)
        {
            newData[i] = data[i];
        }
        sizeRemaining = 0;
        nvm_writeDoubleWord(currentAddr, newData);
    }
    size_write = (size - sizeRemaining);
    return size_write;
}

/**
 * @brief Read a whole page in flash memory
 * @param addr address of the page to read
 * @param data array of the data to read
 */
ssize_t nvm_readPage(uint32_t addr, char *data)
{
    uint32_t pageAddr;
    size_t pageSize;
    ssize_t size_read;

    pageAddr = addr & NVM_FLASH_PAGE_MASK;      // align the address with top of page
    pageSize = (NVM_FLASH_PAGE_BYTE >> 2) * 3;  // calculate the exact number of byte
    /* only 3 out of 4 bytes are useful because of phantom byte */

    size_read = nvm_read(pageAddr, data, pageSize);

    return size_read;
}

/**
 * @brief Erases a page of flash memory
 * @param addraddr of the page to read
 */
ssize_t nvm_erasePage(uint32_t addr)
{
    ssize_t size_erase;

    addr >>= 1;
    NVMADR = addr & 0xF800;  // filter supposed to be on the other register
    NVMADRU = addr >> 16;    // set target write addrof general segment

    NVMCON = 0x4003;
    size_erase = NVM_FLASH_PAGE_BYTE;

    __builtin_disi(6);      // Disable interrupts for NVM unlock
    __builtin_write_NVM();  // unlock and wait until WR = 0
    while (NVMCONbits.WR == 1)
        ;

    return size_erase;
}

/**
 * @brief Writes a whole page in flash memory
 * @param addr address of the page to write
 * @param data array of the data to write
 */
ssize_t nvm_writePage(uint32_t addr, const char *data)
{
    uint32_t pageAddr;
    size_t pageSize;
    ssize_t size_write;

    addr >>= 1;
    pageAddr = addr & NVM_FLASH_PAGE_MASK;      // align the address with top of page
    pageSize = (NVM_FLASH_PAGE_BYTE >> 2) * 3;  // calculate the exact number of byte
    /* only 3 out of 4 bytes are useful because of phantom byte */

    nvm_erasePage(pageAddr);  // the page needs to be erase before any writing
    size_write = nvm_write(pageAddr, data, pageSize);

    return size_write;
}

/**
 * @brief transform an address to page number
 * @param addr address of the page
 */
uint16_t nvm_pageNumber(uint32_t addr)
{
    uint16_t pageNum = addr >> NVM_FLASH_PAGE_SHIFT;
    return pageNum;
}

/**
 * @brief transform a page number to an address
 * @param pageNum number of the page
 */
uint32_t nvm_pageAddress(uint16_t pageNum)
{
    uint32_t pageAddr = (uint32_t)pageNum << NVM_FLASH_PAGE_SHIFT;
    return pageAddr;
}
