#include <stdio.h>
#include <stdint.h>
#include <xc.h>


#include "modules.h"
#include "board.h"
#include "archi.h"

#include "pictures.h"

int main(void)
{
	unsigned int i,j;
	uint8_t uart;
	
	setSystemClock(120000000);
	init_board();
	
	// uart init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	SCREEN_LEDBL = 1;
	
	lcd_init();
	lcd_fillScreen(Blue2);
	
	lcd_setPenColor(Yellow);
	
	lcd_setBrushColor(Red);
	lcd_drawFillRect(50, 50, 50, 50);
	
	for(i=51;i<100;i++)
		lcd_drawPoint(50, i);
	
	lcd_setBrushColor(Yellow);
	lcd_drawFillRect(51, 51, 50, 50);
	
	lcd_setBrushColor(Blue);
	lcd_drawFillRect(52, 52, 50, 50);
	
	lcd_drawLine(50, 50, 420, 270);
	lcd_drawLine(50, 270, 420, 50);
	//lcd_affImage(0, 0, 480, 320, picture);
	
	while(1);
	
	return 0;
}
