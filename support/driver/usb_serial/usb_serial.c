/**
 * @file usb-serial_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date May 01, 2016, 08:31 AM
 *
 * @brief USB serial support
 */

#include "usb_serial.h"

#include "usb_device.h"
#include "usb_device_cdc.h"

#include "sys/fifo.h"

#define UARTSERIAL_BUFFRX_SIZE 512
STATIC_FIFO(usb_serial_buffrx, UARTSERIAL_BUFFRX_SIZE);
uint8_t usb_serial_buffer[64];

void usb_serial_init()
{
	SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    STATIC_FIFO_INIT(usb_serial_buffrx, UARTSERIAL_BUFFRX_SIZE);
}

rt_dev_t usb_serial_getFreeDevice()
{
    usb_serial_init();

    return MKDEV(DEV_CLASS_USB_SERIAL, 0);
}

void usb_serial_task()
{
    uint16_t size_rec;

	if( USBGetDeviceState() < CONFIGURED_STATE )
		return;
	if( USBIsDeviceSuspended() == true )
		return;

    // send service
	CDCTxService();

    // receive service
    size_rec = getsUSBUSART(usb_serial_buffer, sizeof(usb_serial_buffer));
    if(size_rec > 0)
    {
        fifo_push(&usb_serial_buffrx, (char*)usb_serial_buffer, size_rec);
    }
}

ssize_t usb_serial_write(rt_dev_t device, const char *data, size_t size)
{
    uint8_t *ptrData;
    size_t sizeToWrite;
    if( USBGetDeviceState() < CONFIGURED_STATE )
		return 0;
	if( USBIsDeviceSuspended() == true )
		return 0;

    sizeToWrite = size;
    ptrData = (uint8_t *)data;
    while(sizeToWrite > 0)
    {
        if( USBUSARTIsTxTrfReady() == true)
        {
            size_t size_packet = sizeToWrite;
            if(size_packet > 255)
                size_packet = 255;
            putUSBUSART(ptrData, size);
            sizeToWrite -= size_packet;
            ptrData += size_packet;
        }
        usb_serial_task();
    }
    return size;
}

ssize_t usb_serial_read(rt_dev_t device, char *data, size_t max_size)
{
    return fifo_pop(&usb_serial_buffrx, data, max_size);
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (int) event )
    {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */

            //Call the hardware platform specific handler for suspend events for
            //possible further action (like optionally going reconfiguring the application
            //for lower power states and going to sleep during the suspend event).  This
            //would normally be done in USB compliant bus powered applications, although
            //no further processing is needed for purely self powered applications that
            //don't consume power from the host.
            SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND);
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */

            //Call the hardware platform specific resume from suspend handler (ex: to
            //restore I/O pins to higher power states if they were changed during the
            //preceding SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND) call at the start
            //of the suspend condition.
            SYSTEM_Initialize(SYSTEM_STATE_USB_RESUME);
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the
             * demo code. */
            CDCInitEP();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}
