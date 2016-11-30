#include "simmodule_gui.h"

#include <QDebug>

SimModuleGui::SimModuleGui(uint16_t idPeriph)
    : SimModule(idPeriph)
{
    _screenWidget = NULL;
}

void SimModuleGui::pushData(uint16_t functionId, const QByteArray &data)
{
    //qDebug()<<"I am Gui sim!"<<functionId<<data.toHex()<<data.size();

    if(functionId == GUI_SIM_CONFIG)
    {
        GuiConfig *config = (GuiConfig *)data.data();
        if(_screenWidget == NULL)
        {
            _screenWidget = new ScreenWidget((int)config->width, (int)config->height);
            _screenWidget->show();
        }
    }
    if(functionId == GUI_SIM_SETPOS)
    {
        GuiPoint *point = (GuiPoint *)data.data();
        _screenWidget->setPos(point->x, point->y);
    }
    if(functionId == GUI_SIM_SETRECT)
    {
        GuiRect *rect = (GuiRect *)data.data();
        _screenWidget->setRect(rect->x, rect->y, rect->width, rect->height);
    }
    if(functionId == GUI_SIM_WRITEDATA)
    {
        _screenWidget->writeData((uint16_t *)data.data(), data.size()/2);
    }
}
