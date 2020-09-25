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
#include <archi.h>

static FILE *fileNvm;
#define TAILLE_BUF 0x3E800
void nvm_init()
{
    char temp[0x3E800];
    fileNvm = fopen("/home/julien/Seafile/2_FW/uCANOpen/build/_NVM.dat", "r+");
    if (fileNvm == NULL)
    {
        printf("Error open file\n");
        return;
    }
    fwrite(temp, sizeof (temp), 1, fileNvm);
}

/**
 * @brief Reads flash memory
 * @param address address of the page to read
 * @param ramBuffer array of read data
 * @param size number of words to read
 */
void nvm_read(uint32_t address, char *data, size_t size)
{
    size_t count;
    char d[0x800] = {0};

    fileNvm = fopen("/home/julien/Seafile/2_FW/uCANOpen/build/_NVM.dat", "rb");
    if (fileNvm == NULL)
    {
        printf("Error open file\n");
        return;
    }

    fseek(fileNvm, address, SEEK_SET);


//    count = fread(d, 8, 1, fileNvm);
//    if ( count != fread(data, size, 1, fileNvm) )
//    {
//        fprintf( stderr, "Cannot read blocks in file\n" );
//    }

    uint8_t i = 0;
        uint8_t j = 0;
    uint32_t nb_val_lues = 0;

    uint8_t oo = (uint8_t)((double)((double)size / 3) *4);

    nb_val_lues += fread(d, oo, 1, fileNvm);

    for (i = 0; i < oo; i++)
    {
        if ((i % 4) == 3)
        {
            i++;
        }
        data[j] = d[i];
        j++;
    }

    fclose(fileNvm);

}

/**
 * @brief Erases a page of flash memory
 * @param address address of the page to read
 */
void nvm_erase_page(uint32_t address)
{
    // TODO implement me
}

/**
 * @brief Writes two words in flash memory
 * @param address address of the page to read
 * @param data array of the data to write (2 * three 8bits words)
 */
void nvm_writeDoubleWord(uint32_t addrWord, char *data)
{
    // TODO implement me
}

/**
 * @brief Writes words in flash memory
 * @param address address of the page to write
 * @param data array of the data to write
 * @param size size of the data to write in number of bytes
 */
void nvm_write(uint32_t address, char *data, size_t size)
{
    // TODO implement me

    if (fileNvm == NULL)
    {
        nvm_init();
    }
    fseek(fileNvm, address, SEEK_SET);

    char tab[8] = {0};
    tab[0] = data[2];
    tab[1] = data[1];
    tab[2] = data[0];
    tab[3] = 0;
    tab[4] = data[3];
    tab[5] = data[5];
    tab[6] = data[4];
    tab[7] = 0;
    fwrite(tab, sizeof(tab), 1, fileNvm);
    //    fclose(fileNvm);
}
