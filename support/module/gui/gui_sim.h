/**
 * @file gui_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date November 05, 2016, 23:20 AM
 *
 * @brief GUI simulator support driver
 */

#ifndef GUI_SIM_H
#define GUI_SIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GUI_SIM_MODULE 0x0100

#define GUI_SIM_CONFIG 0x0001
typedef struct
{
    uint16_t width;
    uint16_t height;
    GuiColorMode colorMode;
} GuiConfig;

#define GUI_SIM_SETPOS 0x0002
typedef struct
{
    uint16_t x;
    uint16_t y;
} GuiPoint;

#define GUI_SIM_SETRECT 0x0003
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} GuiRect;

#define GUI_SIM_WRITEDATA 0x0004

#ifdef __cplusplus
}
#endif

#endif  // GUI_SIM_H
