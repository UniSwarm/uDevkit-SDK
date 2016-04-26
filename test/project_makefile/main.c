#include <stdio.h>
#include <stdint.h>
#include <xc.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
	unsigned int i,j;
	uint8_t uart;
	
	setSystemClock(60000000);
	init_board();
	esp_init();
	
	// uart init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	while(1)
	{
		for(j=0;j<50;j++) for(i=0;i<65000;i++);
		LED = 0;
		for(j=0;j<10;j++) for(i=0;i<65000;i++);
		LED = 1;
		printf("test");
	}
	
	return 0;
}
