#include "modules.h"
#include "board.h"
#include "archi.h"

#include <stdio.h>
#include <stdint.h>

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

	gui_init();
	gui_fillScreen(Gui_Blue2);

	//display an image
	gui_dispImage(0, 0, &picture);

	gui_setPenColor(Gui_Yellow);
	gui_setBrushColor(0x2965);

	//initialize touch
	// ssize_t response = 42;
	// response = ar1000_init();
	// response = ar1000_enable_touch();






	/*gui_drawFillRect(50, 50, 50, 50);

	for(i=51;i<100;i++)
		gui_drawPoint(50, i);

	gui_setBrushColor(Yellow);
	gui_drawFillRect(51, 51, 50, 50);

	gui_setBrushColor(Blue);
	gui_drawFillRect(52, 52, 50, 50);

	gui_drawLine(50, 50, 420, 270);
	gui_drawLine(50, 270, 420, 50);*/





	//Drawing text
    gui_setFont(&core12b);
    gui_drawText(100, 100, "It seems to work !!! <3");

    //displaying ar1000 responses
    // gui_drawText(100, 150, "response: ");
    // char to_disp[100];
    // sprintf(to_disp, "%d", response);
    // gui_drawText(200, 150, to_disp);

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
