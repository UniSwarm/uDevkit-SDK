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
#define Gui_Gray1          (Color)(0x4208)
#define Gui_Gray2          (Color)(0x7BEF)
#define Gui_Gray3          (Color)(0xCE59)

#define gui_rgb(r, g, b) ((((Color)(r)&0xF8)<<8) + (((Color)(g)&0xFC)<<3) + (((Color)(b)&0xF8)>>3))
#define gui_red(color) (uint8_t)(((color)&0xF800)>>8)
#define gui_green(color) (uint8_t)(((color)&0x07E0)>>3)
#define gui_blue(color) (uint8_t)(((color)&0x001F)<<3)
// RGB to gray => 0.2989R + 0.5870G + 0.1140B = ~0.25R + 0.5G + 0.125B = 1/4 R + 1/2 G + 1/8 B = 1>>2 * R + 1>>1 * G + 1>>3 B
#define gui_gray(color) (uint8_t)((((color)&0xF800)>>10) + (((color)&0x07E0)>>4) + ((color)&0x001F))

#endif // COLOR_H
