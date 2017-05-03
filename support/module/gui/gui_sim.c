#include "gui.h"

#include "board.h"
#include "gui_sim.h"
#include "simulator.h"
#include <math.h>

#include "screenController/screenController.h"

#define GUI_WIDTH 480
#define GUI_HEIGHT 320

Color _gui_penColor;
Color _gui_brushColor;
uint16_t _gui_x, _gui_y;
const Font *_gui_font;

#define BUFFPIXSIZE 200
uint16_t buffPix[BUFFPIXSIZE];
int idPix = 0;

void gui_ctrl_init(rt_dev_t dev)
{
    GuiConfig config =
    {
        .width = GUI_WIDTH,
        .height = GUI_HEIGHT
    };
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_CONFIG, (char*)&config, sizeof(GuiConfig));
}

void gui_ctrl_flush_data()
{
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_WRITEDATA, (char*)buffPix, (idPix)*sizeof(uint16_t));
    idPix = 0;
}

void gui_ctrl_setRectScreen(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    gui_ctrl_flush_data();
    GuiRect rect =
    {
        .x = x,
        .y = y,
        .width = w,
        .height = h
    };
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_SETRECT, (char*)&rect, sizeof(GuiRect));
}

void gui_ctrl_setPos(uint16_t x, uint16_t y)
{
    gui_ctrl_flush_data();
    GuiPoint point =
    {
        .x = x,
        .y = y
    };
    simulator_send(GUI_SIM_MODULE, 0, GUI_SIM_SETPOS, (char*)&point, sizeof(GuiPoint));
}

void gui_ctrl_write_data(uint16_t data)
{
    buffPix[idPix] = data;
    idPix++;

    if(idPix == BUFFPIXSIZE)
		gui_ctrl_flush_data();
}
