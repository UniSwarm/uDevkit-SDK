
#include "driver/i2c.h"

#include "cmd_stdio.h"

int cmd_i2c(int argc, char **argv)
{
    uint8_t i2c = 255;
    rt_dev_t i2c_dev;
    char c;
    uint16_t addr, regaddr, value;

#if !defined (I2C_COUNT) || I2C_COUNT==0
    puts("No i2c module");
    return 1;
#else
    // no args -> print number of i2cs buses
    if(argc == 1)
    {
        printf("count: %d\r\n", (int)I2C_COUNT);
        return 0;
    }

    // first arg numeric : convert to i2c id
    c = argv[1][0];
    if(isdigit(c))
    {
        i2c = c - '0';
        c = argv[1][1];
        if(isdigit(c))
            i2c = i2c * 10 + (c - '0');
    }
    if (i2c >= I2C_COUNT)
    {
        printf("Invalid i2c id %d\r\n", i2c);
        return 0;
    }
    i2c_dev = MKDEV(DEV_CLASS_I2C, i2c);

    // if no more arg, print properties of i2c
    if(argc == 2)
    {
        printf("Config: %d bits address %luHz (%luHz)\r\n",
            (int)i2c_addressWidth(i2c_dev),
            i2c_effectiveBaudSpeed(i2c_dev),
            i2c_baudSpeed(i2c_dev));

        return 0;
    }

    // parse argv 2
    // == setspeed > i2c <bus-id> setspeed <addr>
    if(strcmp(argv[2], "setspeed")==0)
    {
        if(argc < 4)
            return 1;
        uint32_t baudSpeed;
        baudSpeed = atol(argv[3]);
        i2c_setBaudSpeed(i2c_dev, baudSpeed);
        return 0;
    }

    if(argc < 5)
        return 1;
    addr = atoi(argv[3]);
    regaddr = atoi(argv[4]);
    // == readreg > i2c <bus-id> readreg <addr> <regaddr>
    if(strcmp(argv[2], "readreg")==0)
    {
        value = i2c_readreg(i2c_dev, addr, regaddr, I2C_REG8 | I2C_REGADDR8);
        printf("'%d' 0x%X\r\n", value, value);
        return 0;
    }

    if(argc < 6)
        return 1;
    value = atoi(argv[5]);
    // == writereg > i2c <bus-id> writereg <addr> <regaddr> <value>
    if(strcmp(argv[2], "writereg")==0)
    {
        i2c_writereg(i2c_dev, addr, regaddr, value, I2C_REG8 | I2C_REGADDR8);
        puts("ok");
        return 0;
    }

    return 1;
#endif
}
