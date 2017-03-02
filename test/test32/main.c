#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
    uint16_t i, j;
	rt_dev_t uartDbg;
	uint16_t value;
	char buff[100];

	//sysclock_setClock(120000000);
	board_init();

    board_setLed(1, 1);

	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);

	while(1)
	{
		value = uart_read(uartDbg, buff, 100);
		if(value>0)
			uart_write(uartDbg, buff, value);

    board_setLed(2, 1);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
    board_setLed(2, 0);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
	}

	return 0;
}
