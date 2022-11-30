/**
 * @file cmd_uart.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 28, 2016, 11:44 PM
 *
 * @brief UART commands
 */

#include "cmds.h"

#include "cmd_stdio.h"

#include <driver/uart.h>

int cmd_uart(int argc, char **argv)
{
    uint8_t uart_id = 255;
    rt_dev_t uart_dev;
    char c;

#if !defined(UART_COUNT) || UART_COUNT == 0
    puts("No UART module");
    return 1;
#else
    // no args -> print number of uarts
    if (argc == 1)
    {
        printf("count: %d\r\n", (int)UART_COUNT);
        return 0;
    }

    // help
    if (strcmp(argv[1], "help") == 0)
    {
        puts("uart");
        puts("uart <uart-id>");
        puts("uart <uart-id> read");
        puts("uart <uart-id> write <data-to-write>");
        puts("uart <uart-id> setbs <baud-speed>");
        return 0;
    }

    // first arg numeric : convert to uart id
    c = argv[1][0];
    if (isdigit(c))
    {
        uart_id = c - '0';
        c = argv[1][1];
        if (isdigit(c))
        {
            uart_id = uart_id * 10 + (c - '0');
        }
    }
    if (uart_id <= 0 || uart_id > UART_COUNT)
    {
        printf("Invalid uart id %d\r\n", uart_id);
        return 0;
    }
    uart_dev = uart(uart_id);

    // if no more arg, print properties of uart
    // > uart <uart-id>
    if (argc == 2)
    {
        char parity;
        switch (uart_bitParity(uart_dev))
        {
            case UART_BIT_PARITY_NONE:
                parity = 'N';
                break;

            case UART_BIT_PARITY_EVEN:
                parity = 'E';
                break;

            case UART_BIT_PARITY_ODD:
                parity = 'O';
                break;

            default:
                parity = 'U';
                break;
        }
        printf("Config: %luBd %d%c%d (%luBd)\r\n",
               uart_effectiveBaudSpeed(uart_dev),
               (int)uart_bitLength(uart_dev),
               parity,
               (int)uart_bitStop(uart_dev),
               uart_baudSpeed(uart_dev));

        return 0;
    }

    // parse argv 2

    if (argc < 3)
    {
        return 1;
    }
    // == read > uart <uart-id> read
    if (strcmp(argv[2], "read") == 0)
    {
        char buff[100];
        size_t data_read;
        data_read = uart_read(uart_dev, buff, 100);
        buff[data_read] = 0;
        puts(buff);
        return 0;
    }
    if (argc < 4)
    {
        return 1;
    }
    // == write > uart <uart-id> write <data-to-write>
    if (strcmp(argv[2], "write") == 0)
    {
        size_t written = uart_write(uart_dev, argv[3], strlen(argv[3]));
        printf("ok %d data written\r\n", written);
        return 0;
    }
    // == setbs > uart <uart-id> setbs <baud-speed>
    if (strcmp(argv[2], "setbs") == 0)
    {
        uint32_t baudSpeed;
        baudSpeed = atol(argv[3]);
        uart_setBaudSpeed(uart_dev, baudSpeed);
        puts("ok");
        return 0;
    }

    return 1;
#endif
}
