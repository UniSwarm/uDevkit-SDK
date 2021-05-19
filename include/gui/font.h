/**
 * @file font.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 12, 2016, 11:28 PM
 *
 * @brief Font structure for gui module
 */

#ifndef _FONT_
#define _FONT_

#include <stdint.h>

typedef struct
{
    uint8_t width;
    const char *data;
} Letter;

typedef struct
{
    uint8_t height;
    char first;
    char last;
    const Letter **letters;
} Font;

#endif  // _FONT_
