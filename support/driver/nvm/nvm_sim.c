/**
 * @file nvm_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support for uDevKit SDK simulator
 */

#include "nvm.h"

#include <archi.h>

/**
 * @brief Reads flash memory
 * @param address address of the page to read
 * @param ramBuffer array of read data
 * @param size number of words to read
 */
void nvm_read(uint32_t address, char *data, size_t size)
{
    // TODO implement me
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
void nvm_write_double_word(uint32_t address, char *data)
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
}
