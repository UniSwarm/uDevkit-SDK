/**
 * @file eeprom_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 18, 2023, 01:53 PM
 *
 * @brief EEPROM memory support for uDevKit SDK simulator
 */

#include "eeprom.h"

#include <board.h>
#include <simulator.h>

#include <archi.h>
#include <string.h>

static FILE *_eeprom_file = NULL;

static void _eeprom_init(void);

static void _eeprom_init(void)
{
    char path[50] = "";
    strcat(path, BOARD_NAME);
    strcat(path, ".eeprom.bin");

    _eeprom_file = fopen(path, "rb+");
    if (_eeprom_file == NULL)
    {
        char temp[EEPROM_SIZE];

        _eeprom_file = fopen(path, "wb+");
        if (_eeprom_file == NULL)
        {
            printf("[eeprom] Error open file %s\n", path);
            return;
        }

        memset(temp, 0xFF, EEPROM_SIZE);
        fwrite(temp, sizeof(temp), 1, _eeprom_file);
    }
}

int eeprom_init(void)
{
    _eeprom_init();
    return (_eeprom_file == NULL) ? -1 : 0;
}

ssize_t eeprom_read(uint32_t addr, char *data, size_t size)
{
    if (_eeprom_file == NULL)
    {
        return -1;
    }

    fseek(_eeprom_file, addr, SEEK_SET);
    ssize_t size_read = fread(data, size, 1, _eeprom_file);

    return size_read;
}

ssize_t eeprom_write(uint32_t addr, const char *data, size_t size)
{
    if (_eeprom_file == NULL)
    {
        return -1;
    }

    fseek(_eeprom_file, addr, SEEK_SET);
    fwrite(data, size, 1, _eeprom_file);
    return size;
}

int eeprom_readWord(uint32_t addr, uint32_t *data)
{
    uint32_t addrWord = addr - addr % EEPROM_WORDS_WRITE_SIZE;

    fseek(_eeprom_file, addrWord, SEEK_SET);
    fread(data, EEPROM_WORDS_READ_SIZE, 1, _eeprom_file);
    fflush(_eeprom_file);

    return EEPROM_WORDS_READ_SIZE;
}

int eeprom_writeWord(uint32_t addr, uint32_t *data)
{
    uint32_t addrWord = addr - addr % EEPROM_WORDS_WRITE_SIZE;

    fseek(_eeprom_file, addrWord, SEEK_SET);
    fwrite(data, EEPROM_WORDS_WRITE_SIZE, 1, _eeprom_file);
    fflush(_eeprom_file);

    return EEPROM_WORDS_WRITE_SIZE;
}

bool eeprom_ready(void)
{
    return (_eeprom_file != NULL);
}

void eeprom_waitForReady(void)
{
}

void eeprom_reconfig(void)
{
}
