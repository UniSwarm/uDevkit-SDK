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
rt_dev_t usb_serial_getFreeDevice(void);
void usb_serial_task(void);

ssize_t usb_serial_write(rt_dev_t device, const char *data, size_t size);
ssize_t usb_serial_read(rt_dev_t device, char *data, size_t max_size);

#endif // USB_SERIAL_H
