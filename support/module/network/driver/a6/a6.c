/**
 * @file a6.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 25, 2016, 15:30 PM
 *
 * @brief A6 communication support
 */

#ifdef XC16
  #include <xc.h>
#endif

#include "a6.h"

#include "driver/uart.h"
#include "board.h"

rt_dev_t a6_uart;

int a6_init()
{
    a6_uart = uart(A6_UART);
    uart_open(a6_uart);
    uart_setBaudSpeed(a6_uart, 937500);
    uart_setBitConfig(a6_uart, 8, UART_BIT_PARITY_NONE, 1);

#ifndef SIMULATOR
    A6_RW = A6_READ;
#endif

    uart_enable(a6_uart);
    return 0;
}

ssize_t a6_write(const char *data, size_t size)
{
    ssize_t byte;
#ifndef SIMULATOR
    A6_RW = A6_WRITE;
#endif
    byte = uart_write(a6_uart, data, size);
    //uart_flush(a6_uart);
    //A6_RW = A6_READ;
    return byte;
}

ssize_t a6_read(char *data, size_t size_max)
{
    return uart_read(a6_uart, data, size_max);
}

void a6_writeShort(uint16_t channel, uint16_t value)
{
    char data[6];
    data[0]=0xA6;
    data[1]=(char)(channel>>8);
    data[2]=(char)(channel&0x00FF);
    data[3]=(char)(value>>8);
    data[4]=(char)(value&0x00FF);
    data[5]=0x6A;
}
