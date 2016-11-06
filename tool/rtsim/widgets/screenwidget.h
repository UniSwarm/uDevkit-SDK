#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QLabel>
#include <QPixmap>

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    ScreenWidget(int width, int height);

    void setPos(uint16_t x, uint16_t y);
    void setRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    void writeData(uint16_t *pix, size_t size);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

protected:
    QPixmap _pixmap;
    QRect _rect;
    QPoint _pos;
};

#endif // SCREENWIDGET_H
