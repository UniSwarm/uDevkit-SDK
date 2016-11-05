/**
 * @file gui_sim.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date November 05, 2016, 23:20 AM
 *
 * @brief GUI simulator support driver
 */

#ifndef GUI_SIM_H
#define GUI_SIM_H

#include <stdint.h>

#define GUI_SIM_MODULE 0x00FC

#define GUI_SIM_CONFIG 0x0001
typedef struct
{
    uint16_t width;
    uint16_t height;
} GuiConfig;

#endif // GUI_SIM_H
