/**
 * @file color.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 04, 2016, 20:24 PM
 *
 * @brief Color defines for gui module
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

// color 565 format
typedef uint16_t Color;
#define Gui_White          (Color)(0xFFFF)
#define Gui_Black          (Color)(0x0000)
#define Gui_Blue           (Color)(0x001F)
#define Gui_Blue2          (Color)(0x051F)
#define Gui_Red            (Color)(0xF800)
#define Gui_Magenta        (Color)(0xF81F)
#define Gui_Green          (Color)(0x07E0)
#define Gui_Cyan           (Color)(0x7FFF)
#define Gui_Yellow         (Color)(0xFFE0)

#endif // COLOR_H
