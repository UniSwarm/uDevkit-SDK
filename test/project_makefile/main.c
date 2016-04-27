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
	
	setSystemClock(120000000);
	init_board();
	
	// warning keep this init order before remap support
	esp_init();
	ax12_init();
	
	// uart init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	while(1)
	{
		for(j=0;j<60;j++) for(i=0;i<65000;i++);
		LED = 0;
		uart_putc(uart, 'C');
		ax12_send_3_short(1, P_GOAL_POSITION_L, 256, 512, 512);
		for(j=0;j<60;j++) for(i=0;i<65000;i++);
		LED = 1;
		ax12_send_3_short(1, P_GOAL_POSITION_L, 512, 512, 512);
	}
	
	return 0;
}
