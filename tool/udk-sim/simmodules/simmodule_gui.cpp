/**
 ** This file is part of the UDK-SDK project.
 ** Copyright 2019 UniSwarm sebastien.caux@uniswarm.eu
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/

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
            _guiWidget = new GuiWidget(_idPeriph, size, config->colorMode);
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
