#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include <archi.h>
#include "board.h"

int main(void)
{
	uint16_t i, j;
	uint16_t byte_read;
    rt_dev_t uartDbg, uartCmd;
    rt_dev_t usb_serial;
    uint16_t value, value2, value3;
    char buff[200];

    sysclock_setClock(120000000);
    board_init();

    usb_serial = usb_serial_getFreeDevice();
    board_setLed(0, 1);

    // warning keep this init order before remap support
    network_init();
    uartCmd = uart_getFreeDevice();
    uart_getFreeDevice();

    adc_init();

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    // console init
    cmdline_init();
    cmdline_setDevice(uartCmd, uartCmd);
    puts("ok");

    j=0;
    while(1)
    {
        usb_serial_task();

        #ifdef SIMULATOR
            usleep(1000);
        #endif

        value = adc_getValue(ANS0)/7;
        value2 = adc_getValue(ANS1)/7;
        value3 = adc_getValue(ANS2)/7;

        sprintf(buff, "d1:%d\td2:%d\td3:%d\r\n", value, value2, value3);

        byte_read = uart_read(uartDbg, buff, 256);
		if(byte_read > 0)
        {
			uart_write(uartCmd, buff, byte_read);
        }

        if(j++>500)
        {
            //a6_write(buff, strlen(buff)-1);
            uart_write(uartDbg, buff, strlen(buff));
            puts("ok");
            j=0;
            //usb_serial_write(usb_serial, buff, strlen(buff));
        }

        cmdline_task();
    }

    return 0;
}
