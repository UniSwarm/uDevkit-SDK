/**
 * @file usb-serial_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date November 28, 2016, 20:35 PM
 *
 * @brief USB serial support
 */

#include "usb_serial_sim.h"
#include "simulator.h"

rt_dev_t usb_serial_getFreeDevice(void)
{
    // TODO SIM

    return MKDEV(DEV_CLASS_USB_SERIAL, 0);
}

void usb_serial_task(void)
{
    // TODO SIM
}

ssize_t usb_serial_write(rt_dev_t device, const char *data, size_t size)
{
    return 0;
}

ssize_t usb_serial_read(rt_dev_t device, char *data, size_t max_size)
{
    return 0;
}
