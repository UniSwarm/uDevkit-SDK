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

#include <stdint.h>

#include "usb_device.h"
#include "usb_device_cdc.h"

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size);

#endif // USB_SERIAL_H
