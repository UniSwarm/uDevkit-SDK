
#include "driver/uart.h"

#include <ctype.h>
#include <stdio.h>

#define puts(str) cmd_puts((str))
#define printf(format, ...) cmd_printf((format), ##__VA_ARGS__)
#include "cmd.h"

int cmd_uart(int argc, char **argv)
{
    uint8_t uart = 255;
    rt_dev_t uart_dev;
    char c;

#if !defined (UART_COUNT) || UART_COUNT==0
    puts("No UART module");
    return 1;
#else
    // no args -> print number of uarts
    if(argc == 1)
    {
        printf("count: %d\r\n", (int)UART_COUNT);
        return 0;
    }

    // first arg numeric : convert to uart id
    c = argv[1][0];
    if(isdigit(c))
    {
        uart = c - '0';
        c = argv[1][1];
        if(isdigit(c))
            uart = uart * 10 + (c - '0');
    }
    if (uart >= UART_COUNT)
    {
        printf("Invalid uart id %d\r\n", uart);
        return 0;
    }
    uart_dev = MKDEV(DEV_CLASS_UART, uart);

    // if no more arg, print property of uart
    if(argc == 2)
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
        printf("Config: %lubds %d%c%d (%lubds)\r\n",
            uart_effectiveBaudSpeed(uart_dev),
            (int)uart_bitLenght(uart_dev),
            parity,
            (int)uart_bitStop(uart_dev),
            uart_baudSpeed(uart_dev));

        return 0;
    }

    return 0;
#endif
}
