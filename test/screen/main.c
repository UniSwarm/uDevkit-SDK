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
    rt_dev_t uartDbg;
    size_t size;

    sysclock_setClock(120000000);
    board_init();

    // a6 init
    a6_init();
    uartDbg = uart_getFreeDevice();

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
    cmd.font = &Lucida_Console10;
    cmd.font_color = Gui_White;
    cmd.background_color = Gui_Black;
    // console_open(&cmd, 100, 50);

    uart_write(uartDbg, "Type a word to add: ", 20);
    while(1)
    {
        size = uart_read(uartDbg, buff, 100);
        if(size > 0)
        {
            buff[size]=0;
            console_write(&cmd, buff);
            uart_write(uartDbg, buff, size);
            uart_write(uartDbg, "Type a word to add: ", 20);
        }

        for(j=0;j<10;j++) for(i=0;i<65000;i++);

        size = a6_read(buff, 100);
        if(size>0)
        {
            gui_drawTextRect(188, 273, 282, 30, buff, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        }
    }

    return 0;
}
