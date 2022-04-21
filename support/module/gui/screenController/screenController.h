/**
 * @file screenController.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date November 06, 2016, 15:20 AM
 *
 * @brief global screen controller support driver
 */

#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <driver/device.h>

#include "gui_driver.h"

#ifdef USE_d51e5ta7601
#    include "d51e5ta7601.h"
#endif
#ifdef USE_ssd1306
#    include "ssd1306.h"
#endif

void gui_ctrl_init(rt_dev_t dev);
void gui_ctrl_write_data(uint16_t data);
// uint16_t gui_ctrl_read_data(void);
void gui_ctrl_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void gui_ctrl_setPos(uint16_t x, uint16_t y);
void gui_ctrl_drawPoint(uint16_t x, uint16_t y, uint16_t color);
void gui_ctrl_update(void);

#endif  // SCREENCONTROLLER_H
