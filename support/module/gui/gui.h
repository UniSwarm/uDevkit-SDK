/**
 * @file gui.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2017-2021
 *
 * @date April 25, 2016, 18:35 AM
 *
 * @brief GUI support driver
 */

#ifndef GUI_H
#define GUI_H

#include <driver/device.h>

#include "gui/font.h"
#include "gui/color.h"
#include "gui/picture.h"

void gui_init(rt_dev_t dev);

void gui_fillScreen(Color bColor);
void gui_dispImage(uint16_t x, uint16_t y, const Picture *pic);

// color
void gui_setPenColor(Color color);
Color gui_penColor(void);
void gui_setBrushColor(Color color);
Color gui_brushColor(void);

typedef enum {
    ColorModeMono,
    ColorMode565,
    ColorMode666
} GuiColorMode;

// geometry paint
void gui_drawPoint(uint16_t x, uint16_t y);
void gui_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gui_drawRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h);
void gui_drawFillRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h);

// font support
#define GUI_FONT_ALIGN_VLEFT     0x01   // |TXT        |
#define GUI_FONT_ALIGN_VRIGHT    0x02   // |        TXT|
#define GUI_FONT_ALIGN_VMIDDLE   0x03   // |    TXT    |
                                        // _____________
#define GUI_FONT_ALIGN_HTOP      0x04   //      TOP
#define GUI_FONT_ALIGN_HMIDDLE   0x0C   //    MIDDLE
#define GUI_FONT_ALIGN_HBOTTOM   0x08   //    BOTTOM

void gui_drawText(uint16_t x1, uint16_t y1, const char *txt);
void gui_drawTextRect(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, const char *txt, uint8_t flags);

void gui_setFont(const Font *font);
const Font *gui_font(void);

uint8_t gui_getFontHeight(void);
uint8_t gui_getFontWidth(const char c);
uint16_t gui_getFontTextWidth(const char *txt);

// screen driver properties
uint16_t gui_screenWidth(void);
uint16_t gui_screenHeight(void);

#endif // GUI_H
