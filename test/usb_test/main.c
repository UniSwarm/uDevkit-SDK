#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <xc.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
	unsigned int i,j;
	uint8_t uartDbg;
	uint16_t value;
	char buff[100];
	
	setSystemClock(120000000);
	init_board();
	
	usbserial_init();
	
	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);
	
	LED = 1;
	
	while(1)
	{
		usbserial_task();
	}
	
	return 0;
}
