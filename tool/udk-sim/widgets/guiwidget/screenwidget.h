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

#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QLabel>
#include <QPixmap>

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    ScreenWidget(int width, int height, int colorModde);

    void setPos(uint16_t x, uint16_t y);
    void setRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    void writeData(const uint16_t *pix, size_t size);

    QColor fromData(uint16_t pixValue) const;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    QPixmap _pixmap;
    QRect _rect;
    QPoint _pos;
    int _colorModde;
};

#endif  // SCREENWIDGET_H
