#include "gui.h"

#include "board.h"
#include "gui_sim.h"
#include "simulator.h"
#include <math.h>

#include "screenController/screenController.h"

#define BUFFPIXSIZE 200
uint16_t buffPix[BUFFPIXSIZE];
int idPix = 0;

void gui_ctrl_init(rt_dev_t dev)
{
    GuiConfig config = {.width = GUI_WIDTH, .height = GUI_HEIGHT, .colorMode = GUI_COLOR_MODE};
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_CONFIG, (char *)&config, sizeof(GuiConfig));
}

void gui_ctrl_flush_data(void)
{
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_WRITEDATA, (char *)buffPix, (idPix) * sizeof(uint16_t));
    idPix = 0;
}

void gui_ctrl_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    gui_ctrl_flush_data();
    GuiRect rect = {.x = x, .y = y, .width = w, .height = h};
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_SETRECT, (char *)&rect, sizeof(GuiRect));
}

void gui_ctrl_update(void)
{
}

void gui_ctrl_setPos(uint16_t x, uint16_t y)
{
    gui_ctrl_flush_data();
    GuiPoint point = {.x = x, .y = y};
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_SETPOS, (char *)&point, sizeof(GuiPoint));
}

void gui_ctrl_write_data(uint16_t data)
{
    buffPix[idPix] = data;
    idPix++;

    if (idPix == BUFFPIXSIZE)
    {
        gui_ctrl_flush_data();
    }
}

void gui_ctrl_drawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    gui_ctrl_setPos(x, y);
    gui_ctrl_write_data(color);
}
