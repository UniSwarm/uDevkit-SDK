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
	
	// uart init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	lcd_init();
	lcd_fillScreen(Blue2);
	
	while(1);
	
	return 0;
}
