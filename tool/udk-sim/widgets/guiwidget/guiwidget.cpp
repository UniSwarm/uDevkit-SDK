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

#include "guiwidget.h"

#include "screenwidget.h"

#include <QLayout>

GuiWidget::GuiWidget(QWidget *parent) : QWidget(parent)
{
    createWidget();
}

GuiWidget::GuiWidget(uint16_t idPeriph, QSize size, int colorMode, QWidget *parent) : QWidget(parent)
{
    _idPeriph = idPeriph;
    _size = size;
    _colorMode = colorMode;
    setWindowTitle(QString("screen %1").arg(idPeriph));
    createWidget();
}

void GuiWidget::setPos(uint16_t x, uint16_t y)
{
    _screenWidget->setPos(x, y);
}

void GuiWidget::setRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    _screenWidget->setRect(x, y, width, height);
}

void GuiWidget::writeData(uint16_t *pix, size_t size)
{
    _screenWidget->writeData(pix, size);
}

void GuiWidget::createWidget()
{
    QLayout *layout = new QVBoxLayout();

    _screenWidget = new ScreenWidget(_size.width(), _size.height(), _colorMode);
    layout->addWidget(_screenWidget);

    QLayout *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel(QString("screen %1").arg(_idPeriph)));
    _statusEnabled = new QLabel(QString("%1*%2pix").arg(_size.width()).arg(_size.height()));
    statusLayout->addWidget(_statusEnabled);
    _params = new QLabel("");
    statusLayout->addWidget(_params);

    layout->addItem(statusLayout);

    setLayout(layout);
}
