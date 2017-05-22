#include "adcwidget.h"

#include <QLayout>
#include <QPushButton>

AdcWidget::AdcWidget(QWidget *parent)
    : QWidget(parent)
{
    createWidget();
}

AdcWidget::AdcWidget(uint16_t idPeriph, QWidget *parent)
    : QWidget(parent)
{
    _idPeriph = idPeriph;
    setWindowTitle(QString("ADC"));
    createWidget();
}

void AdcWidget::recData(const QString &data)
{
}

void AdcWidget::send()
{
    QByteArray dataToSend;

    uint16_t data = _dial->value();
    dataToSend.append((char)(data & 0xFF));
    dataToSend.append((char)(data >> 8));
    emit sendRequest(dataToSend);
}

void AdcWidget::createWidget()
{
    QLayout *layout = new QVBoxLayout();

    _dial = new QDial();
    _dial->setRange(0, 4095);
    connect(_dial, SIGNAL(valueChanged(int)), this, SLOT(send()));
    layout->addWidget(_dial);

    QLayout *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel(QString("adc")));
    _statusEnabled = new QLabel("disabled");
    statusLayout->addWidget(_statusEnabled);
    _params = new QLabel("");
    statusLayout->addWidget(_params);
    layout->addItem(statusLayout);

    setLayout(layout);
}
