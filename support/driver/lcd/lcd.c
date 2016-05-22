#include "lcd.h"

#include "board.h"

#include <xc.h>

Color _lcd_penColor;
Color _lcd_brushColor;
uint16_t _lcd_x, _lcd_y;

// <TODO write this functions correctly
void delay_ms(uint16_t ms)
{
	int i, j;
	for(j=0; j<ms; j++) for(i=0; i<6210; i++) asm("NOP");
}

void delay_us(uint16_t us)
{
	int i, j;
	for(j=0; j<us; j++) for(i=0; i<6; i++) asm("NOP");
}
// TODO/>

void lcd_write_command(uint16_t cmd)
{
	SCREEN_PORT_OUTPUT;
	SCREEN_RS = 0;
	SCREEN_CS = 0;
	SCREEN_PORT_OUT = cmd;
	SCREEN_RW = 0;
	SCREEN_RW = 1;
	SCREEN_CS = 1;
	SCREEN_RS = 1;
}

void lcd_write_data(uint16_t data)
{
	SCREEN_PORT_OUTPUT;
	SCREEN_CS = 0;
	SCREEN_PORT_OUT = data;
	SCREEN_RW = 0;
	SCREEN_RW = 1;
	SCREEN_CS = 1;
}

uint16_t lcd_read_data()
{
	uint16_t data;
	SCREEN_PORT_INPUT;
	SCREEN_CS = 0;
	SCREEN_RD = 0;
	asm("NOP");
	data = SCREEN_PORT_IN;
	SCREEN_RD = 1;
	SCREEN_CS = 1;
	return data;
}

void lcd_write_command_data (uint8_t cmd, uint16_t data)
{
	lcd_write_command(cmd);
	lcd_write_data(data);
}

void lcd_init(void)
{
	SCREEN_CS = 1;
	SCREEN_RS = 1;
	SCREEN_RW = 1;
	SCREEN_RD = 1;
	SCREEN_RST = 1;
	delay_ms(5);
	SCREEN_RST = 0;
	delay_ms(5);
	SCREEN_RST = 1;
	delay_ms(5);
	
	lcd_write_command_data(0x0001, 0x003C);
	lcd_write_command_data(0x0002, 0x0100);
	lcd_write_command_data(0x0003, 0x1030);
	lcd_write_command_data(0x0008, 0x0808);
	lcd_write_command_data(0x000A, 0x0500);
	lcd_write_command_data(0x000B, 0x0000);
	lcd_write_command_data(0x000C, 0x0770);
	lcd_write_command_data(0x000D, 0x0000);
	lcd_write_command_data(0x000E, 0x0001);
	lcd_write_command_data(0x0011, 0x0406);
	lcd_write_command_data(0x0012, 0x000E);
	lcd_write_command_data(0x0013, 0x0222);
	lcd_write_command_data(0x0014, 0x0015);
	lcd_write_command_data(0x0015, 0x4277);
	lcd_write_command_data(0x0016, 0x0000);
	lcd_write_command_data(0x0030, 0x6A50);
	lcd_write_command_data(0x0031, 0x00C9);
	lcd_write_command_data(0x0032, 0xC7BE);
	lcd_write_command_data(0x0033, 0x0003);
	lcd_write_command_data(0x0036, 0x3443);
	lcd_write_command_data(0x003B, 0x0000);
	lcd_write_command_data(0x003C, 0x0000);
	lcd_write_command_data(0x002C, 0x6A50);
	lcd_write_command_data(0x002D, 0x00C9);
	lcd_write_command_data(0x002E, 0xC7BE);
	lcd_write_command_data(0x002F, 0x0003);
	lcd_write_command_data(0x0035, 0x3443);
	lcd_write_command_data(0x0039, 0x0000);
	lcd_write_command_data(0x003A, 0x0000);
	lcd_write_command_data(0x0028, 0x6A50);
	lcd_write_command_data(0x0029, 0x00C9);
	lcd_write_command_data(0x002A, 0xC7BE);
	lcd_write_command_data(0x002B, 0x0003);
	lcd_write_command_data(0x0034, 0x3443);
	lcd_write_command_data(0x0037, 0x0000);
	lcd_write_command_data(0x0038, 0x0000);
	delay_ms(20);  // delay 20 ms
	lcd_write_command_data(0x0012, 0x200E);
	delay_ms(160);  // delay 160 ms
	lcd_write_command_data(0x0012, 0x2003);
	delay_ms(40);  // delay 40 ms
	
	lcd_write_command_data(WINDOW_XADDR_END, 0x013F);
	lcd_write_command_data(WINDOW_XADDR_START, 0x0000);
	lcd_write_command_data(WINDOW_YADDR_END, 0x01DF);
	lcd_write_command_data(WINDOW_YADDR_START, 0x0000);
		
	lcd_write_command_data(GRAM_ADR_ROW_S, 0x0000);
	lcd_write_command_data(GRAM_ADR_COL_S, 0x013F);
	lcd_write_command_data(0x0007, 0x0012);
	delay_ms(40);  // delay 40 ms
	lcd_write_command_data(0x0007, 0x0017);
}

static void lcd_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	lcd_write_command_data(WINDOW_XADDR_START, y);
	lcd_write_command_data(WINDOW_XADDR_END, y+h-1);
	lcd_write_command_data(WINDOW_YADDR_START, x);
	lcd_write_command_data(WINDOW_YADDR_END, x+w-1);
	lcd_write_command_data(GRAM_ADR_ROW_S, x);
	lcd_write_command_data(GRAM_ADR_COL_S, y);
	
	lcd_write_command(0x22);
}

static void lcd_setPos(uint16_t x, uint16_t y)
{
	lcd_write_command_data(GRAM_ADR_ROW_S, x);
	lcd_write_command_data(GRAM_ADR_COL_S, y);
	
	lcd_write_command(0x22);
}

void lcd_fillScreen(uint16_t color)
{
	uint16_t i,j;
	lcd_setRectScreen(0, 0, LCD_WIDTH, LCD_HEIGHT);
	
	for (i=0; i<LCD_WIDTH; i++)
		for (j=0; j<LCD_HEIGHT; j++)
			lcd_write_data(color);
}

void lcd_affImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, __prog__ const uint16_t *img)
{
	uint16_t i,j;
	unsigned long addr=0;
	
	// set rect image area space address
	lcd_setRectScreen(x, y, w, h);
	
	for (i=0; i<w; i++)
	{
		for (j=0; j<h; j++)
		{
			lcd_write_data(img[addr]);
			addr++;
		}
	}
	
	// restore full draw screen
	lcd_setRectScreen(0, 0, LCD_WIDTH, LCD_HEIGHT);
}

void lcd_setPenColor(uint16_t color)
{
	_lcd_penColor = color;
}

uint16_t lcd_penColor()
{
	return _lcd_penColor;
}

void lcd_setBrushColor(uint16_t color)
{
	_lcd_brushColor = color;
}

uint16_t lcd_brushColor()
{
	return _lcd_brushColor;
}

void lcd_drawPoint(uint16_t x, uint16_t y)
{
	uint16_t data;
	lcd_setPos(x, y);
	
	lcd_write_data(_lcd_penColor);
	/*data=lcd_read_data();
	data=lcd_read_data();*/
	
	// warning fixme double pixel send
	lcd_write_data(_lcd_penColor);
}

void lcd_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ratioX = dx;
	int ratioY = dy;
	float m, b;
	/*void (*pixelPtr)(unsigned short,unsigned short,char);
	
	// Si la ligne ne sort pas de l ecran, on affiche les pixels sans les controler
	pixelPtr = ( (x1 >= 0 && y1 >= 0 && x1 < PIXEL_NUMBER_X && y1 < PIXEL_NUMBER_Y) &&
				 (x2 >= 0 && y2 >= 0 && x2 < PIXEL_NUMBER_X && y2 < PIXEL_NUMBER_Y) )
		? &point : &drawPoint;*/

	if (dx == 0)
    {
		lcd_drawPoint(x1, y1);
		dy = (y2 > y1) ? 1 : -1;
        while (y1 != y2)
        {
            y1 = y1 + dy;
			lcd_drawPoint(x1, y1);
        }
		return;
    }
	if (dy == 0)
	{
		lcd_drawPoint(x1, y1);
		dx = (x2 > x1) ? 1 : -1;
	    while (x1 != x2)
	    {
	        x1 = x1 + dx;
			lcd_drawPoint(x1, y1);
	    }
		return;
	}
	
	if (ratioX < 0) ratioX = -ratioX;
	if (ratioY < 0) ratioY = -ratioY;
	
	if (ratioX >= ratioY)
	{
        m = (float)dy / (float)dx;
        b = y1 - m*x1;

        dx = (x2 > x1) ? 1 : -1;

        lcd_drawPoint(x1, y1);
        while (x1 != x2)
        {
            x1 += dx;
            y1 = (int)((m*x1 + b)+0.5);
			lcd_drawPoint(x1, y1);
        }
		return;
	}
	if (ratioX < ratioY)
	{
        m = (float)dx / (float)dy;
        b = x1 - m*y1;

        dy = (y2 > y1) ? 1 : -1;

        lcd_drawPoint(x1, y1);
        while (y1 != y2)
        {
            y1 += dy;
            x1 = (int)((m*y1 + b)+0.5);
			lcd_drawPoint(x1, y1);
        }
		return;
	}
}

void lcd_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	int i;
	
	lcd_drawLine(x,   y,   x+w,  y);
    lcd_drawLine(x+w, y,   x+w,  y+h);
    lcd_drawLine(x+w, y+h, x,    y+h);
    lcd_drawLine(x,   y+h, x,    y);
}

void lcd_drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint16_t i,j;
	
	// set rect image area space address
	lcd_setRectScreen(x, y, w, h);
	
	// fill this rect with brush color
	for (i=0; i<h; i++)
		for (j=0;j<w;j++)
			lcd_write_data(_lcd_brushColor);
	
	// restore full draw screen
	lcd_setRectScreen(0, 0, LCD_WIDTH, LCD_HEIGHT);
	
	// draw border with pen color
	//lcd_drawRect(x, y, w, h);
}

void lcd_drawText(uint16_t x1, uint16_t y1, const char *txt)
{
	
}
