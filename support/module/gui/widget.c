/**
 * @file widget.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 06, 2016, 22:16 PM
 *
 * @brief Widget structure for gui module
 */

#include <module/gui.h>
#include <gui/widget.h>

#define WIDGET_COUNT 25
Widget widgets[WIDGET_COUNT];

// internal functions
void widget_draw(Widget *widget);

void widget_init()
{
    int i;
    for(i=0; i<WIDGET_COUNT; i++)
    {
        widgets[i].type = 0;
    }
}

void widget_addButton(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    int i;
    for(i=0; i<WIDGET_COUNT; i++)
    {
        if(widgets[i].type == 0)
            break;
    }
    if(i==WIDGET_COUNT)
        return;

    widgets[i].type = WIDGET_TYPE_BUTTON;
    widgets[i].x = x;
    widgets[i].y = y;
    widgets[i].w = w;
    widgets[i].h = h;

    widget_draw(&widgets[i]);
}

void widget_draw(Widget *widget)
{
    if(widget->type == WIDGET_TYPE_BUTTON)
    {
        gui_setPenColor(Gui_Black);
        gui_setBrushColor(Gui_Gray2);
        gui_drawTextRect(widget->x + 2, widget->y + 2, widget->w - 2, widget->h - 2, "OK", GUI_FONT_ALIGN_VMIDDLE | GUI_FONT_ALIGN_HMIDDLE);

        gui_setPenColor(Gui_Gray3);
        gui_drawLine(widget->x, widget->y, widget->x + widget->w, widget->y);
        gui_drawLine(widget->x, widget->y+1, widget->x + widget->w-1, widget->y+1);
        gui_drawLine(widget->x, widget->y, widget->x, widget->y + widget->h - 1);
        gui_drawLine(widget->x+1, widget->y, widget->x+1, widget->y + widget->h-1);
        gui_drawLine(widget->x+2, widget->y, widget->x+2, widget->y + widget->h-2);

        gui_setPenColor(Gui_Gray1);
        gui_drawLine(widget->x, widget->y + widget->h    , widget->x + widget->w, widget->y + widget->h    );
        gui_drawLine(widget->x, widget->y + widget->h - 1, widget->x + widget->w, widget->y + widget->h - 1);

        gui_drawLine(widget->x + widget->w    , widget->y, widget->x + widget->w    , widget->y + widget->h);
        gui_drawLine(widget->x + widget->w - 1, widget->y, widget->x + widget->w - 1, widget->y + widget->h);
        gui_drawLine(widget->x + widget->w - 2, widget->y, widget->x + widget->w - 2, widget->y + widget->h);

        return;
    }
}
