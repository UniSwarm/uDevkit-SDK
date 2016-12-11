#include "modules.h"
#include "board.h"
#include "archi.h"

#include <stdio.h>
#include <stdint.h>

#include "pictures.h"
#include "console.h"
#include "fonts.h"

// #include <gui/widget.h>

int main(void)
{
    unsigned int i,j;
    char buff[101];
    size_t size;

    sysclock_setClock(120000000);
    board_init();

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

    //WORKING ON GUI_CONSOLE
    Console cmd = Terminal_default;
    cmd.width = 300;
    cmd.height = 100;
    cmd.font = &core12b;
    cmd.font_color = Gui_White;
    cmd.background_color = Gui_Black;
    console_open(&cmd, 100, 50);
    // console_write(&cmd, "line0\nline1");
    // console_write(&cmd, "Terminal successfully opened\nTerminal successfully opened!");
    // console_write(&cmd, "Je suis sur que je vais depasser de la ligne!");
    console_write(&cmd, "Je suis sur que je vais depasser de la ligne mais on s en fou parce qu on va regler cela!");
    // console_write(&cmd, "Je suis sur que je vais depasser de la ligne\nTerminal successfully opened!");

    // console_write(&cmd, "bab");
    // console_write(&cmd, "prout");
    // console_write(&cmd, "caca");





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
    // gui_setFont(&core12b);
    // gui_drawText(100, 100, "It seems to work !!! <3");
    // gui_setFont(&core18b);
    // gui_drawText(100, 150, "It seems to work !!! <3");

    //widget_addButton(50, 200, 150, 50);

    //displaying ar1000 responses
    // gui_drawText(100, 150, "response: ");
    // char to_disp[100];
    // sprintf(to_disp, "%d", response);
    // gui_drawText(200, 150, to_disp);

    char prout[100];
    while(1)
    {
        printf("Type a word to add: ");
        scanf("%s", &prout);
        console_write(&cmd, prout);


        for(j=0;j<10;j++) for(i=0;i<65000;i++);

        size = a6_read(buff, 100);
        if(size>0)
        {
            gui_drawTextRect(188, 273, 282, 30, buff, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        }
    }

    return 0;
}
