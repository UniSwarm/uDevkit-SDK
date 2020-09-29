/**
 * @file nvm_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support for uDevKit SDK simulator
 */

#include "simulator.h"
#include "board.h"

#include <archi.h>
#include <string.h>

static FILE *fileNvm;
#define TAILLE_BUF 0xAF000

void nvm_init()
{
    char temp[TAILLE_BUF];

    char path[100];
    strcat(path, "./");
    strcat(path, BOARD_NAME);
    strcat(path, ".bin");

    fileNvm = fopen(path, "w+b");
    if (fileNvm == NULL)
    {
        printf("Error open file\n");
        return;
    }

    memset(temp, 255, TAILLE_BUF);
    fwrite(temp, sizeof (temp), 1, fileNvm);
}

/**
 * @brief Reads flash memory
 * @param address address of the page to read
 * @param ramBuffer array of read data
 * @param size number of words to read
 */
ssize_t nvm_read(uint32_t addr, char *data, size_t size)
{
    char d[0x800] = {0};
    uint8_t i = 0;
    uint8_t j = 0;

    if (fileNvm == NULL)
    {
        nvm_init();
    }

    fseek(fileNvm, addr, SEEK_SET);


    uint8_t sizeEff = (uint8_t)((double)((double)size / 3) *4);
    fread(d, sizeEff, 1, fileNvm);

    for (i = 0; i < sizeEff; i++)
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
    if (fileNvm == NULL)
    {
        nvm_init();
    }
    fseek(fileNvm, addr, SEEK_SET);

    char tab[8] = {0};
    tab[0] = data[0];
    tab[1] = data[1];
    tab[2] = data[2];
    tab[3] = 0;
    tab[4] = data[3];
    tab[5] = data[4];
    tab[6] = data[5];
    tab[7] = 0;
    fwrite(tab, sizeof(tab), 1, fileNvm);
    return 0;
}
