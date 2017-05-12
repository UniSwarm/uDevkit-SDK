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
