#include <stdio.h>
#include <stdint.h>
#include <xc.h>


#include "modules.h"
#include "board.h"
#include "archi.h"

#include "pictures.h"
extern const Font core12b;

int main(void)
{
	unsigned int i,j;
	char buff[101];
    size_t size;
	
	setSystemClock(120000000);
	init_board();
	
	// a6 init
    a6_init();
	
	SCREEN_LEDBL = 1;
	
	lcd_init();
	lcd_fillScreen(Blue2);
	
	lcd_affImage(0, 0, 480, 320, picture);
	
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
    
    lcd_setFont(&core12b);
    lcd_drawText(100, 100, "It seems to work !!! <3");
	
	while(1)
    {
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        
		size = a6_read(buff, 100);
		if(size>0)
        {
            lcd_drawFillRect(0, 140, 300, 60);
            lcd_drawText(10, 150, buff);
        }
    }
	
	return 0;
}
