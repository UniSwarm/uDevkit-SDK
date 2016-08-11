/**
 * @file usb-serial.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date May 01, 2016, 08:31 AM 
 * 
 * @brief USB serial support
 */

#ifndef USB_SERIAL_H
#define USB_SERIAL_H

#include "driver/device.h"

// API
void usb_serial_init();
void usb_serial_task();

ssize_t usb_serial_write(const char *data, const size_t size);
ssize_t usb_serial_read(char *data, const size_t max_size);

#endif // USB_SERIAL_H
