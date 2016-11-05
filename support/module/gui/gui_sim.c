#include "gui.h"

#include "board.h"
#include "gui_sim.h"
#include "simulator.h"

#define GUI_WIDTH 480
#define GUI_HEIGHT 320

Color _gui_penColor;
Color _gui_brushColor;
uint16_t _gui_x, _gui_y;
const Font *_gui_font;

void gui_init(void)
{
    GuiConfig config =
    {
        .width = GUI_WIDTH,
        .height = GUI_HEIGHT
    };
    printf("mowisjgfoi\n");
    simulator_send(GUI_SIM_MODULE, GUI_SIM_CONFIG, (char*)&config, 4);
}

static void gui_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{

}

static void gui_setPos(uint16_t x, uint16_t y)
{

}

void gui_fillScreen(Color color)
{

}

/**
 * @brief gui_dispImage
 * display an Picture at the (x,y) poisiton on the screen
 */
void gui_dispImage(uint16_t x, uint16_t y, const Picture *pic)
{

}

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

}

void gui_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

}

void gui_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{

}

void gui_drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{

}

void gui_drawText(uint16_t x, uint16_t y, const char *txt)
{

}

void gui_drawTextRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *txt, uint8_t flags)
{

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

uint16_t gui_screenWidth(uint8_t screen)
{
    return GUI_WIDTH;
}

uint16_t gui_screenHeight(uint8_t screen)
{
    return GUI_HEIGHT;
}
