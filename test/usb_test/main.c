#include <archi.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "archi.h"
#include "board.h"
#include "modules.h"

extern rt_dev_t esp8266_uart;
rt_dev_t usb_serial;

int main(void)
{
    // unsigned int i,j;
    uint8_t uartDbg;
    uint16_t byte_read;
    char buff[256];

    sysclock_setClock(120000000);
    board_init();

    usb_serial = usb_serial_getFreeDevice();

    // warning keep this init order before remap support
    network_init();
    ax12_init(uart(AX12_UART), gpio_pin(AX12_TXEN_PORT, AX12_TXEN_PIN), 0);

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    board_setLed(0, 1);

    while (1)
    {
        usb_serial_task();

        byte_read = uart_read(esp8266_uart, buff, 256);
        if (byte_read > 0)
        {
            usb_serial_write(usb_serial, buff, byte_read);
        }

        byte_read = usb_serial_read(usb_serial, buff, 256);
        if (byte_read > 0)
        {
            uart_write(esp8266_uart, buff, byte_read);
        }
    }

    return 0;
}
