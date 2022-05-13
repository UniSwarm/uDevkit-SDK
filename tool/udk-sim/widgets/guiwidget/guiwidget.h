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

#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <QLabel>
#include <QWidget>

class ScreenWidget;

class GuiWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GuiWidget(QWidget *parent = Q_NULLPTR);
    GuiWidget(uint16_t idPeriph, QSize size, int colorMode, QWidget *parent = Q_NULLPTR);

    void setPos(uint16_t x, uint16_t y);
    void setRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    void writeData(uint16_t *pix, size_t size);

signals:

public slots:
protected:
    ScreenWidget *_screenWidget;
    QLabel *_statusEnabled;
    QLabel *_params;
    void createWidget();

    uint16_t _idPeriph;
    QSize _size;
    int _colorMode;
};

#endif  // GUIWIDGET_H
