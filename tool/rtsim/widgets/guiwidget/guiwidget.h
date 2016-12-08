#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <QWidget>
#include <QLabel>

class ScreenWidget;

class GuiWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GuiWidget(QWidget *parent = 0);
    GuiWidget(uint16_t idPeriph, QSize size, QWidget *parent = 0);

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
};

#endif // GUIWIDGET_H
