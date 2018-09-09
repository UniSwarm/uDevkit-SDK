/**
 * @file gui.c
 * @author Sebastien CAUX (sebcaux) / Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2017-2018
 *
 * @date April 25, 2016, 18:35 AM
 *
 * @brief GUI support driver
 */

#include "gui.h"
#include "screenController/screenController.h"

Color _gui_penColor = 1;
Color _gui_brushColor = 0;
const Font *_gui_font = NULL;

void gui_init(rt_dev_t dev)
{
    gui_ctrl_init(dev);
}

void gui_fillScreen(Color color)
{
    uint16_t i,j;
    gui_ctrl_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);

    for (i = 0; i<GUI_WIDTH; i++)
        for (j = 0; j<GUI_HEIGHT; j++)
            gui_ctrl_write_data(color);
}

/**
 * @brief gui_dispImage
 * display an Picture at the (x,y) poisiton on the screen
 */
void gui_dispImage(uint16_t x, uint16_t y, const Picture *pic)
{
    uint16_t i,j;
    unsigned long addr = 0;

    //TODO: create warning if the image is too big

    // set rect image area space address
    gui_ctrl_setRectScreen(x, y, pic->width, pic->height);

    for (i = 0; i<pic->width; i++)
    {
        for (j = 0; j<pic->height; j++)
        {
            gui_ctrl_write_data(pic->data[addr]);
            ++addr;
        }
    }

    // restore full draw screen
    gui_ctrl_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
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
    gui_ctrl_drawPoint(x, y, _gui_penColor);
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
    gui_ctrl_setRectScreen(x, y, w, h);

    // fill this rect with brush color
    for (i = 0; i<h; i++)
        for (j = 0;j<w;j++)
            gui_ctrl_write_data(_gui_brushColor);

    // restore full draw screen
    gui_ctrl_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);

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
    uint16_t text_width, xstartmargin, xendmargin;
    uint16_t text_height, ystartmargin, yendmargin;
    uint16_t wcurrent;
    uint8_t out_of_rect = 0;

    if (_gui_font == NULL)
        return;

    if (x >= GUI_WIDTH || y >= GUI_HEIGHT)
        return;

    // width calculation
    text_width = gui_getFontTextWidth(txt);

    //testing if text is out box
    if (text_width > w)
        text_width = w;

    //testing if text is out screen
    if (text_width > GUI_WIDTH - x)
        text_width = GUI_WIDTH - x;

    //computing margin parameters
    if ((flags&0x03) == GUI_FONT_ALIGN_VLEFT)
    {
        xstartmargin = 0;
        xendmargin = w - text_width;
    }
    else if ((flags&0x03) == GUI_FONT_ALIGN_VRIGHT)
    {
        xstartmargin = w - text_width;
        xendmargin = 0;
    }
    else
    {
        xstartmargin = (w - text_width)>>1;
        xendmargin = w - text_width - xstartmargin;
    }

    // height calculation
    text_height = gui_getFontHeight();
    if ((flags&0x0C) == GUI_FONT_ALIGN_HTOP)
    {
        ystartmargin = 0;
        yendmargin = h - text_height;
    }
    else if ((flags&0x0C) == GUI_FONT_ALIGN_HBOTTOM)
    {
        ystartmargin = h - text_height;
        yendmargin = 0;
    }
    else
    {
        ystartmargin = (h - text_height)>>1;
        yendmargin = h - text_height - ystartmargin;
    }

    // windows text size
    gui_ctrl_setRectScreen(x, y, w, h);

    // xstartmargin
    for (j = 0; j < xstartmargin; j++)
        for (i = 0; i < h; i++)
            gui_ctrl_write_data(_gui_brushColor);

    // writting pixels chars
    c = txt;
    wcurrent = 0;
    while ((*c != '\0') && (out_of_rect != 1) )
    {
        if (*c >= _gui_font->first && *c <= _gui_font->last)
        {
            octet = -1;
            letter = _gui_font->letters[*c - _gui_font->first];
            for (j = 0; j < letter->width; j++)
            {
                //verifying if wcurrent is out of rect
                if ( wcurrent >= text_width )
                {
                    out_of_rect = 1;
                    break;
                }

                for (i = 0; i < ystartmargin; i++)
                    gui_ctrl_write_data(_gui_brushColor);
                for (i = 0; i < _gui_font->height; i++)
                {
                    if ((i&0x0007) == 0)
                    {
                        bit = 1;
                        octet++;
                    }
                    if ((letter->data[octet]) & bit)
                        gui_ctrl_write_data(_gui_penColor);
                    else
                        gui_ctrl_write_data(_gui_brushColor);
                    bit = bit << 1;
                }
                for (i = 0; i < yendmargin; i++)
                    gui_ctrl_write_data(_gui_brushColor);

                wcurrent++;
            }
        }
        c++;
    }

    // xendmargin
    for (j = 0; j < xendmargin; j++)
        for (i = 0; i < h; i++)
            gui_ctrl_write_data(_gui_brushColor);

    // restore full draw screen
    gui_ctrl_setRectScreen(0, 0, GUI_WIDTH, GUI_HEIGHT);
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
    if (_gui_font == NULL)
        return 0;
    return _gui_font->height;
}

uint8_t gui_getFontWidth(const char c)
{
    if (_gui_font == NULL)
        return 0;
    if (c < _gui_font->first || c > _gui_font->last)
        return 0;
    return _gui_font->letters[c - _gui_font->first]->width;
}

uint16_t gui_getFontTextWidth(const char *txt)
{
    uint16_t width = 0;
    const char *c = txt;
    if (_gui_font == NULL)
        return 0;
    while (*c != '\0')
    {
        if (*c >= _gui_font->first && *c <= _gui_font->last)
            width += _gui_font->letters[*c - _gui_font->first]->width;
        c++;
    }

    return width;
}

uint16_t gui_screenWidth()
{
    return GUI_WIDTH;
}

uint16_t gui_screenHeight()
{
    return GUI_HEIGHT;
}
