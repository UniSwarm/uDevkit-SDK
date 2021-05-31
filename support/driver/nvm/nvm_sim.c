/**
 * @file nvm_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020-2021
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support for uDevKit SDK simulator
 */

#include "board.h"
#include "simulator.h"

#include <archi.h>
#include <string.h>

#define __PROGRAM_LENGTH 512000

static FILE *nvm_file;

void nvm_init(void);

void nvm_init(void)
{
    char path[50] = "";
    strcat(path, BOARD_NAME);
    strcat(path, ".bin");

    nvm_file = fopen(path, "rb+");
    if (nvm_file == NULL)
    {
        char temp[__PROGRAM_LENGTH];

        nvm_file = fopen(path, "wb+");
        if (nvm_file == NULL)
        {
            printf("[nvm] Error open file %s\n", path);
            return;
        }

        memset(temp, 255, __PROGRAM_LENGTH);
        fwrite(temp, sizeof(temp), 1, nvm_file);
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
    char d[0x1000] = {0};
    uint16_t i = 0;
    uint16_t j = 0;

    if (nvm_file == NULL)
    {
        nvm_init();
    }

    fseek(nvm_file, addr, SEEK_SET);

    fread(d, size, 1, nvm_file);
    for (i = 0; i < size; i++)
    {
        if ((i % 4) == 3)
        {
            i++;
        }
        data[j] = d[i];
        j++;
    }
    return 0;
}

/**
 * @brief Erases a page of flash memory
 * @param address address of the page to read
 */
ssize_t nvm_erasePage(uint32_t addr)
{
    UDK_UNUSED(addr);
    return 0;
}

/**
 * @brief Writes two words in flash memory
 * @param address address of the page to read
 * @param data array of the data to write (2 * three 8bits words)
 */
void nvm_writeDoubleWord(uint32_t addrWord, char *data)
{
    UDK_UNUSED(addrWord);
    UDK_UNUSED(data);
}

/**
 * @brief Writes words in flash memory
 * @param address address of the page to write
 * @param data array of the data to write
 * @param size size of the data to write in number of bytes
 */
ssize_t nvm_write(uint32_t addr, char *data, size_t size)
{
    UDK_UNUSED(size);
    if (nvm_file == NULL)
    {
        nvm_init();
    }
    fseek(nvm_file, addr, SEEK_SET);

    char tab[8] = {0};
    tab[0] = data[0];
    tab[1] = data[1];
    tab[2] = data[2];
    tab[3] = 0;
    tab[4] = data[3];
    tab[5] = data[4];
    tab[6] = data[5];
    tab[7] = 0;
    fwrite(tab, sizeof(tab), 1, nvm_file);
    return 0;
}
