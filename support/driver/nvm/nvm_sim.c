/**
 * @file nvm_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020-2022
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support for uDevKit SDK simulator
 */

#include "nvm.h"

#include "board.h"
#include "simulator.h"

#include <archi.h>
#include <string.h>

#define __PROGRAM_LENGTH 512000

#define SIZE_WORD        4u  // 3 + phantom
#define SIZE_DOUBLE_WORD 6u  // without phantom bit

static FILE *_nvm_file;

void nvm_init(void);

void nvm_init(void)
{
    char path[50] = "";
    strcat(path, BOARD_NAME);
    strcat(path, ".bin");

    _nvm_file = fopen(path, "rb+");
    if (_nvm_file == NULL)
    {
        char temp[__PROGRAM_LENGTH];

        _nvm_file = fopen(path, "wb+");
        if (_nvm_file == NULL)
        {
            printf("[nvm] Error open file %s\n", path);
            return;
        }

        memset(temp, 0xFF, __PROGRAM_LENGTH);
        fwrite(temp, sizeof(temp), 1, _nvm_file);
    }
}

/**
 * @brief Reads flash memory
 * @param address address of the page to read
 * @param ramBuffer array of read data
 * @param size number of words to read
 */
ssize_t nvm_read(uint32_t addr, char *data, size_t size)
{
    char d[NVM_FLASH_PAGE_BYTE] = {0};
    uint16_t i = 0;
    uint16_t j = 0;

    if (_nvm_file == NULL)
    {
        nvm_init();
    }

    fseek(_nvm_file, addr, SEEK_SET);

    fread(d, size, 1, _nvm_file);
    for (i = 0; i < size; i++)
    {
        if ((i % 4) == 3)
        {
            i++;
        }
        data[j] = d[i];
        j++;
    }
    return size;
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

    if (_nvm_file == NULL)
    {
        nvm_init();
    }

    pageAddr = addr & NVM_FLASH_PAGE_MASK;      // align the address with top of page
    pageSize = (NVM_FLASH_PAGE_BYTE >> 2) * 3;  // calculate the exact number of byte
    /* only 3 out of 4 bytes are useful because of phantom byte */

    size_read = nvm_read(pageAddr, data, pageSize);

    return size_read;
}

/**
 * @brief Erases a page of flash memory
 * @param address address of the page to read
 */
ssize_t nvm_erasePage(uint32_t addr)
{
    if (_nvm_file == NULL)
    {
        nvm_init();
    }

    char temp[NVM_FLASH_PAGE_BYTE];
    memset(temp, 0xFF, NVM_FLASH_PAGE_BYTE);

    fseek(_nvm_file, addr, SEEK_SET);
    fwrite(temp, sizeof(temp), 1, _nvm_file);

    return 0;
}

/**
 * @brief Writes two words in flash memory
 * @param address address of the page to read
 * @param data array of the data to write (2 * three 8bits words)
 */
void nvm_writeDoubleWord(uint32_t addrWord, const char *data)
{
    if (_nvm_file == NULL)
    {
        nvm_init();
    }

    char tab[8];
    tab[0] = data[0];
    tab[1] = data[1];
    tab[2] = data[2];
    tab[3] = 0xFF;
    tab[4] = data[3];
    tab[5] = data[4];
    tab[6] = data[5];
    tab[7] = 0xFF;

    fseek(_nvm_file, addrWord, SEEK_SET);
    fwrite(tab, sizeof(char) * 8, 1, _nvm_file);
}

/**
 * @brief Writes words in flash memory
 * @param address address of the page to write
 * @param data array of the data to write
 * @param size size of the data to write in number of bytes
 */
ssize_t nvm_write(uint32_t addr, const char *data, size_t size)
{
    uint16_t end;
    uint16_t index = 0;

    if (_nvm_file == NULL)
    {
        nvm_init();
    }

    end = (((uint16_t)size) / SIZE_DOUBLE_WORD) * SIZE_DOUBLE_WORD;

    while (index <= end)
    {
        nvm_writeDoubleWord(addr, &data[index]);
        addr += SIZE_WORD * 2;
        index += SIZE_DOUBLE_WORD;
    }
    return index;
}
