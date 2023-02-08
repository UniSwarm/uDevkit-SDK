#include "archi.h"
#include "board.h"
#include "modules.h"

#include <stdint.h>
#include <stdio.h>

#include "console.h"
#include "fonts.h"
#include "pictures.h"

#define BARCOLOR     0x2965
#define BARTEXTCOLOR Gui_White

#ifdef BEAR
#    define BACKGROUND 0x51a4
#    define PICTURE    picture_bear
#endif
#ifdef RABBIT
#    define BACKGROUND 0xe652
#    define PICTURE    picture_rabbit
#endif
#ifdef INSECT
#    define BACKGROUND 0xbea6
#    define PICTURE    picture_insect
#endif
#ifdef SIMPLEPICTURE
#    define BACKGROUND 0x51a4
#    define PICTURE    picture
#endif

void drawBatt(uint16_t x, uint16_t y, uint16_t percent)
{
    int i;
    char text[20];
    if (percent > 100)
    {
        percent = 100;
    }

    gui_setBrushColor(BARCOLOR);
    gui_setPenColor(BARTEXTCOLOR);
    gui_drawRect(x, y, 26, 12);
    for (i = 0; i <= percent / 5; i++)
    {
        gui_drawLine(x + 3 + i, y + 4, x + 3 + i, y + 8);
    }
    gui_setPenColor(BARCOLOR);
    for (; i < 20; i++)
    {
        gui_drawLine(x + 3 + i, y + 4, x + 3 + i, y + 8);
    }

    gui_setPenColor(BARTEXTCOLOR);
    gui_drawLine(x + 27, y + 7, x + 27, y + 3);
    gui_drawLine(x + 28, y + 7, x + 28, y + 3);

    sprintf(text, "%d%%", percent);
    gui_drawTextRect(x + 35, y - 4, 55, 20, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
}

void drawBattValue(uint16_t x, uint16_t y, uint16_t volt)
{
    char text[20];

    sprintf(text, "%.2fv", (float)volt / 1000.0);
    gui_drawTextRect(x, y - 4, 70, 20, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
}

void drawPos(uint16_t x, uint16_t y, uint16_t posx, uint16_t posy, uint16_t post)
{
    char text[60];

    sprintf(text, "x: %dmm", (int)posx);
    gui_drawTextRect(x, y, 130, 25, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);

    sprintf(text, "y: %dmm", (int)posy);
    gui_drawTextRect(x, y + 25, 130, 25, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);

    sprintf(text, "t: %d", (int)post);
    gui_drawTextRect(x, y + 50, 50, 25, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
}

void drawMenuBar()
{
    gui_setBrushColor(BARCOLOR);
    gui_setPenColor(BARTEXTCOLOR);
    gui_drawFillRect(0, 293, 480, 27);
    gui_drawTextRect(100, 295, 280, 20, "deltaTips", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HTOP);
}

void drawBar(uint16_t x, uint16_t y, uint16_t dist)
{
    if (dist > 700)
    {
        dist = 700;
    }

    dist /= 10;

    gui_setPenColor(BARTEXTCOLOR);
    gui_drawRect(x - 2, y - 4, 18, 75);

    gui_setBrushColor(BARTEXTCOLOR);
    gui_drawFillRect(x, y + 70 - dist, 15, dist);

    gui_setBrushColor(BACKGROUND);
    gui_drawFillRect(x, y, 15, 70 - dist);
}

int main(void)
{
    unsigned int i, j;
    char buff[101];
    rt_dev_t uartDbg;
    size_t size;
    int16_t value, value2, value3;

    board_init();
    sysclock_setClock(120000000);

    // a6 init
    network_init();
    a6_init(uart(A6_UART), gpio_pin(A6_RW_PORT, A6_RW_PIN), 0);

    uartDbg = uart_getFreeDevice();

    gui_init(NULLDEV);
    gui_fillScreen(Gui_Blue2);

    // display an image
    gui_dispImage(0, 0, &PICTURE);

    gui_setPenColor(Gui_Yellow);
    gui_setBrushColor(0x2965);

    gui_setFont(&core14b);
    drawMenuBar();
    drawBattValue(20, 300, 4100);
    drawBatt(390, 300, 50);

#ifndef SIMPLEPICTURE
    drawBar(20, 100, 600);
    drawBar(480 - 20 - 20, 100, 100);
    drawPos(10, 10, 600, 500, 0);
#endif

    uart_write(uartDbg, "Type a word to add: ", 20);
    while (1)
    {
        /*size = uart_read(uartDbg, buff, 100);
        if(size > 0)
        {
            buff[size]=0;
            console_write(&cmd, buff);
            uart_write(uartDbg, buff, size);
            uart_write(uartDbg, "Type a word to add: ", 20);
        }*/

        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < 65000; i++)
            {
                ;
            }
        }

        size = a6_read(buff, 100);

        char text[60];
        sprintf(text, "t: %d", (int)size);
        gui_drawTextRect(240, 40, 50, 25, text, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        if (size > 10)
        {
            int16_t *ptr;
            ptr = (int16_t *)buff;

            // if(*ptr==0xA6)
            {
                ptr++;
                value = *ptr;
                drawBatt(390, 300, value);

                ptr++;
                value = *ptr;
                drawBattValue(20, 300, value);

#ifndef SIMPLEPICTURE
                ptr++;
                value = *ptr;
                drawBar(20, 100, value);

                ptr++;
                value = *ptr;
                drawBar(480 - 20 - 20, 100, value);

                ptr++;
                value = *ptr;
                ptr++;
                value2 = *ptr;
                ptr++;
                value3 = *ptr;
                drawPos(10, 10, value, value2, value3);
#endif
            }

            // gui_drawTextRect(188, 273, 282, 30, buff, GUI_FONT_ALIGN_VLEFT | GUI_FONT_ALIGN_HTOP);
        }
    }

    return 0;
}
