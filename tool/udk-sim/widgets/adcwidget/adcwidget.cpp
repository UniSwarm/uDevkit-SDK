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
    Q_UNUSED(data)
}

void AdcWidget::send()
{
    QByteArray dataToSend;

    uint16_t data = static_cast<uint16_t>(_dial->value());
    dataToSend.append(static_cast<char>(data & 0xFF));
    dataToSend.append(static_cast<char>(data >> 8));
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
