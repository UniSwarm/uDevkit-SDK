/**
 * @file gui.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 25, 2016, 18:35 AM 
 * 
 * @brief GUI support driver
 */

#ifndef GUI_H
#define GUI_H

#include <stdint.h>

#include "gui/font.h"

// color 565 format
typedef uint16_t Color;
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define WINDOW_XADDR_START  0x0045 // Horizontal Start Address Set
#define WINDOW_XADDR_END    0x0044 // Horizontal End Address Set
#define WINDOW_YADDR_START  0x0047 // Vertical Start Address Set
#define WINDOW_YADDR_END    0x0046 // Vertical End Address Set
#define GRAM_ADR_ROW_S      0x0020 // init to 0 , UPDATE FIRST
#define GRAM_ADR_COL_S      0x0021 // init to 319 , UPDATE LAST
#define GRAMWR              0x0022 // memory write

#define GUI_WIDTH 480
#define GUI_HEIGHT 320

/**
 * @brief Picture struct
 * contains data and metadata (width, height...)
 */
typedef struct
{
    //metadata
    uint16_t width;
    uint16_t height;

    //data
    __prog__ const uint16_t *data;

} Picture;

void gui_init(void);

void gui_fillScreen(Color bColor);
void gui_dispImage(uint16_t x, uint16_t y, const Picture *pic);

// color
void gui_setPenColor(Color color);
Color gui_penColor(void);
void gui_setBrushColor(Color color);
Color gui_brushColor(void);

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
const Font *gui_font();

uint8_t gui_getFontHeight();
uint8_t gui_getFontWidth(const char c);
uint16_t gui_getFontTextWidth(const char *txt);

#endif // GUI_H
