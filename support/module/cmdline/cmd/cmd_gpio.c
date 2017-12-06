
#include "driver/gpio.h"

#include "cmd_stdio.h"

void cmd_gpio_help()
{
    puts("gpio <gpio-pin>");
    puts("gpio <gpio-pin> set");
    puts("gpio <gpio-pin> clear");
    puts("gpio <gpio-pin> toggle");
    puts("gpio <gpio-port>");
    puts("gpio <gpio-port> set <hex-value>");
}

int cmd_gpio(int argc, char **argv)
{
    uint8_t port = 255;
    uint8_t pin = 255;
    rt_dev_t gpio_dev;
    char c;

    // no args -> print help
    if (argc == 1)
    {
        cmd_gpio_help();
        return 0;
    }

    // help
    if (strcmp(argv[1], "help")==0)
    {
        cmd_gpio_help();
        return 0;
    }

    // first arg numeric : convert to gpio id
    c = argv[1][0];
    if (c < 'A' || c > 'L')
    {
        printf("Invalid gpio id\r\n");
        return 0;
    }
    port = c - 'A';
    c = argv[1][1];
    if (isdigit(c))
    {
        pin = c - '0';
        c = argv[1][2];
        if (isdigit(c))
            pin = pin * 10 + (c - '0');
        gpio_dev = gpio_pin(port, pin);
        if (argc == 3 && strcmp(argv[2], "set") == 0)
        {
            gpio_setBit(gpio_dev);
            printf("written\n");
            return 0;
        }
        if (argc == 3 && strcmp(argv[2], "clear") == 0)
        {
            gpio_clearBit(gpio_dev);
            printf("written\n");
            return 0;
        }
        if (argc == 3 && strcmp(argv[2], "toggle") == 0)
        {
            gpio_toggleBit(gpio_dev);
            printf("written\n");
            return 0;
        }
        printf("value: %d\n", gpio_readBit(gpio_dev));
        return 0;
    }
    else
    {
        gpio_dev = gpio_port(port);
        if (argc == 4 && strcmp(argv[2], "set") == 0)
        {
            gpio_writePort(gpio_dev, strtol(argv[3], NULL, 16));
            printf("written\n");
            return 0;
        }
        else
        {
            printf("0x%.4X\r\n", gpio_readPort(gpio_dev));
            return 0;
        }
    }


    return 1;
}
