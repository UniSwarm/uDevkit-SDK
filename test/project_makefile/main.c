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
	
	// warning keep this init order before remap support
	esp_init();
	ax12_init();
	adc_init();
	
	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);
	
	while(1)
	{
		for(j=0;j<10;j++) for(i=0;i<65000;i++);
		LED = 0;
		for(j=0;j<10;j++) for(i=0;i<65000;i++);
		LED = 1;
		
		/*value = adc_getValue(24);	// AnS1
		value = adc_getValue(25);	// AnS2*/
		value = adc_getValue(26);	// AnS3
		ax12_moveTo(1, value, 512, 512);
		
		sprintf(buff, "value: %d\n", sharp_convert(value, FarSharp));
		uart_write(uartDbg, buff, strlen(buff));
	}
	
	return 0;
}
