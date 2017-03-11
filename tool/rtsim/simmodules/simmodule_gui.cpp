#include "simmodule_gui.h"

#include <QDebug>

SimModuleGui::SimModuleGui(SimClient *client, uint16_t idPeriph)
    : SimModule(client, GUI_SIM_MODULE, idPeriph)
{
    _guiWidget = NULL;
}

QWidget *SimModuleGui::widget() const
{
    return _guiWidget;
}

void SimModuleGui::pushData(uint16_t functionId, const QByteArray &data)
{
    //qDebug()<<"I am Gui sim!"<<functionId<<data.toHex()<<data.size();

    if(functionId == GUI_SIM_CONFIG)
    {
        GuiConfig *config = (GuiConfig *)data.data();
        if(_guiWidget == NULL)
        {
            QSize size = QSize((int)config->width, (int)config->height);
            _guiWidget = new GuiWidget(_idPeriph, size);
            _guiWidget->show();
        }
    }
    if(functionId == GUI_SIM_SETPOS)
    {
        GuiPoint *point = (GuiPoint *)data.data();
        _guiWidget->setPos(point->x, point->y);
    }
    if(functionId == GUI_SIM_SETRECT)
    {
        GuiRect *rect = (GuiRect *)data.data();
        _guiWidget->setRect(rect->x, rect->y, rect->width, rect->height);
    }
    if(functionId == GUI_SIM_WRITEDATA)
    {
        _guiWidget->writeData((uint16_t *)data.data(), data.size()/2);
    }
}
