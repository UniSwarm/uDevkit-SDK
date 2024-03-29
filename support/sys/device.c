/**
 * @file device.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 6, 2016, 18:30 PM
 *
 * @brief Device read write wrapper
 */

#include <driver/device.h>

#include "modules.h"  // keep this include before ifdef USE_*

#ifdef USE_uart
#    include <driver/uart.h>
#endif
#ifdef USE_spi
#    include <driver/spi.h>
#endif
#ifdef USE_usb_serial
#    include <driver/usb_serial.h>
#endif
#ifdef USE_i2c
#    include <driver/i2c.h>
#endif
#ifdef USE_timer
#    include <driver/timer.h>
#endif
#ifdef USE_eeprom
#    include <driver/eeprom.h>
#endif

ssize_t device_write(rt_dev_t device, const char *data, size_t size)
{
#if !defined(USE_uart) && !defined(USE_spi) && !defined(USE_usb_serial)
    UDK_UNUSED(data);
    UDK_UNUSED(size);
#endif

    switch (MAJOR(device))
    {
#ifdef USE_uart
        case DEV_CLASS_UART:
            return uart_write(device, data, size);
#endif
#ifdef USE_spi
        case DEV_CLASS_SPI:
            return spi_write(device, data, size);
#endif
#ifdef USE_usb_serial
        case DEV_CLASS_USB_SERIAL:
            return usb_serial_write(device, data, size);
#endif
        default:
            return -1;
    }
}

ssize_t device_read(rt_dev_t device, char *data, size_t size_max)
{
#if !defined(USE_uart) && !defined(USE_spi) && !defined(USE_usb_serial)
    UDK_UNUSED(data);
    UDK_UNUSED(size_max);
#endif

    switch (MAJOR(device))
    {
#ifdef USE_uart
        case DEV_CLASS_UART:
            return uart_read(device, data, size_max);
#endif
#ifdef USE_spi
        case DEV_CLASS_SPI:
            return spi_read(device, data, size_max);
#endif
#ifdef USE_usb_serial
        case DEV_CLASS_USB_SERIAL:
            return usb_serial_read(device, data, size_max);
#endif
        default:
            return -1;
    }
}

void device_reconfig(void)
{
#if defined(USE_uart) && (UART_COUNT > 0)
    uart_reconfig();
#endif
#if defined(USE_timer) && (TIMER_COUNT > 0)
    timer_reconfig();
#endif
#if defined(USE_i2c) && (I2C_COUNT > 0)
    i2c_reconfig();
#endif
#if defined(USE_eeprom) && (EEPROM_COUNT > 0)
    eeprom_reconfig();
#endif
}
