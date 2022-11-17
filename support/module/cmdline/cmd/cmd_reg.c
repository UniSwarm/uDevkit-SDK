/**
 * @file cmd_reg.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief Register commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <archi.h>

#include <stdint.h>

void cmd_reg_help(void)
{
    puts("reg read <hex-addr>");
    puts("reg write <hex-addr> <hex-value>");
}

// TODO adapt for 16 bit device
int cmd_reg(int argc, char **argv)
{
    if (argc < 2)
    {
        cmd_reg_help();
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        cmd_reg_help();
        return 0;
    }

    if (argc < 3)
    {
        return 1;
    }

    volatile rt_reg_ptr_t *addr = (volatile rt_reg_ptr_t *)strtoul(argv[2], NULL, 16);
    if (addr == 0)
    {
        return 1;
    }

    if (strcmp(argv[1], "read") == 0)
    {
        char res[sizeof(int) * 8 + 4];
        rt_reg_t value = *addr;
        uint8_t id = 0;

        // print in binary format
        rt_reg_t mask;
#if (REGSIZE == 4)
        mask = 0x80000000;
#else
        mask = 0x8000;
#endif
        while (mask != 0)
        {
            res[id++] = ((value & mask) == 0) ? '0' : '1';
            mask >>= 1;
            if ((mask & 0x00808080) != 0)
            {
                res[id++] = ' ';
            }
        }
        res[id] = 0;

#if (REGSIZE == 4)
        printf("dec : %d\n", value);
        printf("hex : 0x%.8X\n", value);
        printf("bin : 0b%s\n", res);
#else
        printf("dec : %d\n", value);
        printf("hex : 0x%.4X\n", value);
        printf("bin : 0b%s\n", res);
#endif
        return 0;
    }

    if (argc < 4)
    {
        return 1;
    }
    volatile unsigned int value = (unsigned int)strtoul(argv[3], NULL, 16);
    if (strcmp(argv[1], "write") == 0)
    {
        *addr = value;
        printf("written\n");
        return 0;
    }

    return 1;
}
