#include "gui.h"

#include "board.h"

#include <xc.h>

Color _gui_penColor;
Color _gui_brushColor;
uint16_t _gui_x, _gui_y;
const Font *_gui_font;

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

void gui_write_command(uint16_t cmd)
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

void gui_write_data(uint16_t data)
{
	SCREEN_PORT_OUTPUT;
	SCREEN_CS = 0;
	SCREEN_PORT_OUT = data;
	SCREEN_RW = 0;
	SCREEN_RW = 1;
	SCREEN_CS = 1;
}

uint16_t gui_read_data()
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

void gui_write_command_data (uint8_t cmd, uint16_t data)
{
	gui_write_command(cmd);
	gui_write_data(data);
}

void gui_init(void)
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
	
	gui_write_command_data(0x0001, 0x003C);
	gui_write_command_data(0x0002, 0x0100);
	gui_write_command_data(0x0003, 0x1030);
	gui_write_command_data(0x0008, 0x0808);
	gui_write_command_data(0x000A, 0x0500);
	gui_write_command_data(0x000B, 0x0000);
	gui_write_command_data(0x000C, 0x0770);
	gui_write_command_data(0x000D, 0x0000);
	gui_write_command_data(0x000E, 0x0001);
	gui_write_command_data(0x0011, 0x0406);
	gui_write_command_data(0x0012, 0x000E);
	gui_write_command_data(0x0013, 0x0222);
	gui_write_command_data(0x0014, 0x0015);
	gui_write_command_data(0x0015, 0x4277);
	gui_write_command_data(0x0016, 0x0000);
	gui_write_command_data(0x0030, 0x6A50);
	gui_write_command_data(0x0031, 0x00C9);
	gui_write_command_data(0x0032, 0xC7BE);
	gui_write_command_data(0x0033, 0x0003);
	gui_write_command_data(0x0036, 0x3443);
	gui_write_command_data(0x003B, 0x0000);
	gui_write_command_data(0x003C, 0x0000);
	gui_write_command_data(0x002C, 0x6A50);
	gui_write_command_data(0x002D, 0x00C9);
	gui_write_command_data(0x002E, 0xC7BE);
	gui_write_command_data(0x002F, 0x0003);
	gui_write_command_data(0x0035, 0x3443);
	gui_write_command_data(0x0039, 0x0000);
	gui_write_command_data(0x003A, 0x0000);
	gui_write_command_data(0x0028, 0x6A50);
	gui_write_command_data(0x0029, 0x00C9);
	gui_write_command_data(0x002A, 0xC7BE);
	gui_write_command_data(0x002B, 0x0003);
	gui_write_command_data(0x0034, 0x3443);
	gui_write_command_data(0x0037, 0x0000);
	gui_write_command_data(0x0038, 0x0000);
	delay_ms(20);  // delay 20 ms
	gui_write_command_data(0x0012, 0x200E);
	delay_ms(160);  // delay 160 ms
	gui_write_command_data(0x0012, 0x2003);
	delay_ms(40);  // delay 40 ms
	
	gui_write_command_data(WINDOW_XADDR_END, 0x013F);
	gui_write_command_data(WINDOW_XADDR_START, 0x0000);
	gui_write_command_data(WINDOW_YADDR_END, 0x01DF);
	gui_write_command_data(WINDOW_YADDR_START, 0x0000);
		
	gui_write_command_data(GRAM_ADR_ROW_S, 0x0000);
	gui_write_command_data(GRAM_ADR_COL_S, 0x013F);
	gui_write_command_data(0x0007, 0x0012);
	delay_ms(40);  // delay 40 ms
	gui_write_command_data(0x0007, 0x0017);
}

static void gui_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	gui_write_command_data(WINDOW_XADDR_START, y);
	gui_write_command_data(WINDOW_XADDR_END, y+h-1);
	gui_write_command_data(WINDOW_YADDR_START, x);
	gui_write_command_data(WINDOW_YADDR_END, x+w-1);
	gui_write_command_data(GRAM_ADR_ROW_S, x);
	gui_write_command_data(GRAM_ADR_COL_S, y);
	
	gui_write_command(0x22);
}

static void gui_setPos(uint16_t x, uint16_t y)
{
	gui_write_command_data(GRAM_ADR_ROW_S, x);
	gui_write_command_data(GRAM_ADR_COL_S, y);
	
	gui_write_command(0x22);
}

void gui_fillScreen(Color color)
{
	uint16_t i,j;
	gui_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
	
	for (i=0; i<GUI_WIDTH; i++)
		for (j=0; j<GUI_HEIGHT; j++)
			gui_write_data(color);
}

void gui_affImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, __prog__ const uint16_t *img)
{
	uint16_t i,j;
	unsigned long addr=0;
	
	// set rect image area space address
	gui_setRectScreen(x, y, w, h);
	
	for (i=0; i<w; i++)
	{
		for (j=0; j<h; j++)
		{
			gui_write_data(img[addr]);
			addr++;
		}
	}
	
	// restore full draw screen
	gui_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
}

// void gui_affImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Picture* pic)
// {
// 	uint16_t i,j;
// 	unsigned long addr=0;
	
// 	// set rect image area space address
// 	gui_setRectScreen(x, y, w, h);
	
// 	for (i=0; i<w; i++)
// 	{
// 		for (j=0; j<h; j++)
// 		{
// 			gui_write_data(pic.data[addr]);
// 			addr++;
// 		}
// 	}
	
// 	// restore full draw screen
// 	gui_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
// }

void gui_setPenColor(uint16_t color)
{
	_gui_penColor = color;
}

uint16_t gui_penColor()
{
	return _gui_penColor;
}

void gui_setBrushColor(uint16_t color)
{
	_gui_brushColor = color;
}

uint16_t gui_brushColor()
{
	return _gui_brushColor;
}

void gui_drawPoint(uint16_t x, uint16_t y)
{
	//uint16_t data;
	gui_setPos(x, y);
	
	gui_write_data(_gui_penColor);
	/*data=gui_read_data();
	data=gui_read_data();*/
	
	// warning fixme double pixel send
	gui_write_data(_gui_penColor);
}

void gui_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
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
		gui_drawPoint(x1, y1);
		dy = (y2 > y1) ? 1 : -1;
        while (y1 != y2)
        {
            y1 = y1 + dy;
			gui_drawPoint(x1, y1);
        }
		return;
    }
	if (dy == 0)
	{
		gui_drawPoint(x1, y1);
		dx = (x2 > x1) ? 1 : -1;
	    while (x1 != x2)
	    {
	        x1 = x1 + dx;
			gui_drawPoint(x1, y1);
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

        gui_drawPoint(x1, y1);
        while (x1 != x2)
        {
            x1 += dx;
            y1 = (int)((m*x1 + b)+0.5);
			gui_drawPoint(x1, y1);
        }
		return;
	}
	if (ratioX < ratioY)
	{
        m = (float)dx / (float)dy;
        b = x1 - m*y1;

        dy = (y2 > y1) ? 1 : -1;

        gui_drawPoint(x1, y1);
        while (y1 != y2)
        {
            y1 += dy;
            x1 = (int)((m*y1 + b)+0.5);
			gui_drawPoint(x1, y1);
        }
		return;
	}
}

void gui_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	gui_drawLine(x,   y,   x+w,  y);
    gui_drawLine(x+w, y,   x+w,  y+h);
    gui_drawLine(x+w, y+h, x,    y+h);
    gui_drawLine(x,   y+h, x,    y);
}

void gui_drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint16_t i,j;
	
	// set rect image area space address
	gui_setRectScreen(x, y, w, h);
	
	// fill this rect with brush color
	for (i=0; i<h; i++)
		for (j=0;j<w;j++)
			gui_write_data(_gui_brushColor);
	
	// restore full draw screen
	gui_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
	
	// draw border with pen color
	//gui_drawRect(x, y, w, h);
}

void gui_drawText(uint16_t x, uint16_t y, const char *txt)
{
    gui_drawTextRect(x, y, gui_getFontTextWidth(txt), gui_getFontHeight(), txt, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
}

void gui_drawTextRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *txt, uint8_t flags)
{
	int16_t octet;
	uint16_t i, j;
	char bit;
	const Letter *letter;
    const char *c;
    uint16_t width, xstartdec, xenddec;
    uint16_t height, ystartdec, yenddec;
    
    if(x>=GUI_WIDTH || y>=GUI_HEIGHT)
        return;
    
    // width calculation
    width = gui_getFontTextWidth(txt);
    if((flags&0x03) == GUI_FONT_ALIGN_VLEFT)
    {
        xstartdec = 0;
        xenddec = w - width;
    }
    else if((flags&0x03) == GUI_FONT_ALIGN_VRIGHT)
    {
        xstartdec = w - width;
        xenddec = 0;
    }
    else
    {
        xstartdec = (w - width)>>1;
        xenddec = w - width - xstartdec;
    }
    
    if(width > GUI_WIDTH - x)
        width = GUI_WIDTH - x;
    
    // height calculation
    height = gui_getFontHeight();
    if((flags&0x0C) == GUI_FONT_ALIGN_HTOP)
    {
        ystartdec = 0;
        yenddec = h - height;
    }
    else if((flags&0x0C) == GUI_FONT_ALIGN_HBOTTOM)
    {
        ystartdec = h - height;
        yenddec = 0;
    }
    else
    {
        ystartdec = (h - height)>>1;
        yenddec = h - height - ystartdec;
    }
    
    // windows text size
	gui_setRectScreen(x, y, w, h);
    
    // xstartdec
    for(j = 0; j < xstartdec; j++)
        for(i = 0; i < h; i++)
            gui_write_data(_gui_brushColor);
    
    // writting pixels chars
    c = txt;
	while (*c != '\0')
	{
		if (*c >= _gui_font->first && *c <= _gui_font->last)
		{
			octet = -1;
			letter = _gui_font->letters[*c - _gui_font->first];
			for(j = 0; j < letter->width; j++)
			{
                for(i = 0; i < ystartdec; i++)
                    gui_write_data(_gui_brushColor);
				for(i = 0; i < _gui_font->height; i++)
				{
					if ((i&0x0007) == 0)
					{
						bit = 1;
                        octet++;
					}
					if ((letter->data[octet]) & bit)
						gui_write_data(_gui_penColor);
                    else
						gui_write_data(_gui_brushColor);
					bit = bit << 1;
				}
                for(i = 0; i < yenddec; i++)
                    gui_write_data(_gui_brushColor);
			}
		}
		c++;
    }
    
    // xenddec
    for(j = 0; j < xenddec; j++)
        for(i = 0; i < h; i++)
            gui_write_data(_gui_brushColor);
	
	// restore full draw screen
	gui_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
}

void gui_setFont(const Font *font)
{
    _gui_font = font;
}

const Font *gui_font()
{
    return _gui_font;
}

uint8_t gui_getFontHeight()
{
    return _gui_font->height;
}

uint8_t gui_getFontWidth(const char c)
{
    if(c < _gui_font->first || c > _gui_font->last)
        return 0;
    return _gui_font->letters[c - _gui_font->first]->width;
}

uint16_t gui_getFontTextWidth(const char *txt)
{
    uint16_t width = 0;
    const char *c = txt;
	while (*c != '\0')
	{
        if (*c >= _gui_font->first && *c <= _gui_font->last)
            width += _gui_font->letters[*c - _gui_font->first]->width;
        c++;
    }
    
    return width;
}
