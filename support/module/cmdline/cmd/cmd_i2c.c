/**
 * @file cmd_i2c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief I2C commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <driver/i2c.h>

int cmd_i2c(int argc, char **argv)
{
    uint8_t i2c_id = 255;
    rt_dev_t i2c_dev;
    char c;
    uint16_t addr, regaddr, value;

#if !defined(I2C_COUNT) || I2C_COUNT == 0
    puts("No i2c module");
    return 1;
#else
    // no args -> print number of i2cs buses
    if (argc == 1)
    {
        printf("count: %d\r\n", (int)I2C_COUNT);
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        puts("i2c <bus-id>");
        puts("i2c <bus-id> scan");
        puts("i2c <bus-id> setspeed <speed>");
        puts("i2c <bus-id> readreg <addr> <regaddr>");
        puts("i2c <bus-id> writereg <addr> <regaddr> <value>");
        return 0;
    }

    // first arg numeric : convert to i2c_id
    c = argv[1][0];
    if (isdigit(c))
    {
        i2c_id = c - '0';
        c = argv[1][1];
        if (isdigit(c))
        {
            i2c_id = i2c_id * 10 + (c - '0');
        }
    }
    if (i2c_id <= 0 || i2c_id > I2C_COUNT)
    {
        printf("Invalid i2c id %d\r\n", i2c_id);
        return 0;
    }
    i2c_dev = i2c(i2c_id);

    // if no more arg, print properties of i2c
    // > i2c <bus-id>
    if (argc == 2)
    {
        printf("Config: %d bits address %luHz (%luHz)\r\n", (int)i2c_addressWidth(i2c_dev), i2c_effectiveBaudSpeed(i2c_dev), i2c_baudSpeed(i2c_dev));

        return 0;
    }

    // parse argv 2
    // == scan > i2c <bus-id> scan
    if (strcmp(argv[2], "scan") == 0)
    {
        for (uint16_t i2c_addr = 0; i2c_addr <= 255; i2c_addr += 2)
        {
            i2c_start(i2c_dev);
            int ack = i2c_putc(i2c_dev, i2c_addr);
            i2c_stop(i2c_dev);

            if (ack == 0)
            {
                printf("0x%02X\r\n", i2c_addr);
            }
        }
        return 0;
    }

    // == setspeed > i2c <bus-id> setspeed <speed>
    if (strcmp(argv[2], "setspeed") == 0)
    {
        if (argc < 4)
        {
            return 1;
        }
        uint32_t baudSpeed;
        baudSpeed = atol(argv[3]);
        i2c_setBaudSpeed(i2c_dev, baudSpeed);
        return 0;
    }

    if (argc < 5)
    {
        return 1;
    }
    addr = atoi(argv[3]);
    regaddr = atoi(argv[4]);
    // == readreg > i2c <bus-id> readreg <addr> <regaddr>
    if (strcmp(argv[2], "readreg") == 0)
    {
        value = i2c_readreg(i2c_dev, addr, regaddr, I2C_REG8 | I2C_REGADDR8);
        printf("'%d' 0x%X\r\n", value, value);
        return 0;
    }

    if (argc < 6)
    {
        return 1;
    }
    value = atoi(argv[5]);
    // == writereg > i2c <bus-id> writereg <addr> <regaddr> <value>
    if (strcmp(argv[2], "writereg") == 0)
    {
        i2c_writereg(i2c_dev, addr, regaddr, value, I2C_REG8 | I2C_REGADDR8);
        puts("ok");
        return 0;
    }

    return 1;
#endif
}
