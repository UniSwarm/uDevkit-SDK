#include "screenwidget.h"

#include <QPainter>
#include <QDebug>
#include <QPaintEvent>

ScreenWidget::ScreenWidget(int width, int height)
  : _pixmap(QPixmap(width, height))
{
    QPainter painter(&_pixmap);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, width, height);
    _rect = QRect(0, 0, width, height);
    _pos = QPoint(0, 0);
    painter.end();
    setMinimumSize(width, height);
    update();
}

void ScreenWidget::setPos(uint16_t x, uint16_t y)
{
    _pos = QPoint(x, y);
}

void ScreenWidget::setRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    _rect = QRect(x, y, width, height);
    _pos = QPoint(x, y);
}

void ScreenWidget::writeData(uint16_t *pix, size_t size)
{
    QPainter painter(&_pixmap);

    for(uint i=0; i<size; i++)
    {
        uint16_t pixValue = pix[i];
        QColor color = QColor((pixValue&0xF800)>>8,
                              (pixValue&0x07E0)>>3,
                              (pixValue&0x001F)<<3);
        painter.setPen(color);
        painter.drawPoint(_pos);

        if(_pos.y() >= _rect.bottom())
        {
            _pos.setX(_pos.x()+1);
            _pos.setY(_rect.top());
        }
        else
            _pos.setY(_pos.y()+1);
    }

    painter.end();
    update();
}

void ScreenWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap(0,0, _pixmap);
}
