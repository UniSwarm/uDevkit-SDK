#include "modules.h"
#include "board.h"
#include "archi.h"

#include <stdio.h>
#include <stdint.h>
#include <xc.h>

#include "pictures.h"
extern const Font core12b;

int main(void)
{
	unsigned int i,j;
	char buff[101];
    size_t size;

	sysclock_setClock(120000000);
	init_board();

	// a6 init
    a6_init();
    //ar1000_init();

	SCREEN_LEDBL = 1;

	gui_init();
	gui_fillScreen(Blue2);

	// gui_affImage(0, 0, 480, 320, picture);
	Picture pic;
	pic.data = picture;
	gui_affImage(0, 0, 480, 320, &pic);

	gui_setPenColor(Yellow);
	gui_setBrushColor(0x2965);

	/*gui_drawFillRect(50, 50, 50, 50);

	for(i=51;i<100;i++)
		gui_drawPoint(50, i);

	gui_setBrushColor(Yellow);
	gui_drawFillRect(51, 51, 50, 50);

	gui_setBrushColor(Blue);
	gui_drawFillRect(52, 52, 50, 50);

	gui_drawLine(50, 50, 420, 270);
	gui_drawLine(50, 270, 420, 50);*/

    // gui_setFont(&core12b);
    // gui_drawText(100, 100, "It seems to work !!! <3");

	while(1)
    {
		for(j=0;j<10;j++) for(i=0;i<65000;i++);

		size = a6_read(buff, 100);
		if(size>0)
        {
            gui_drawTextRect(188, 273, 282, 30, buff, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        }
    }

	return 0;
}
