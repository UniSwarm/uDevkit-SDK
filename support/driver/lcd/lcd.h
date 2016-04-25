/**
 * @file lcd.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 25, 2016, 18:35 AM 
 * 
 * @brief LCD support driver
 */

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

/* LCD color 565 format */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define WINDOW_XADDR_START	0x0045 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0044 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0047 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0046 // Vertical End Address Set
/*#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set*/
#define GRAM_ADR_ROW_S 0x0020 /* init to 0 , UPDATE FIRST */
#define GRAM_ADR_COL_S 0x0021 /* init to 319 , UPDATE LAST */
#define GRAMWR 			    0x0022 // memory write

void init_lcd();

void fill_screen(unsigned int bColor);
void affImage(unsigned short x, unsigned short y, unsigned short w, unsigned short h, __prog__ const unsigned short *img);

#endif // LCD_H
