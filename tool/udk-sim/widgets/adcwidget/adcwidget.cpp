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
#include <QDebug>

AdcWidget::AdcWidget(QWidget *parent)
    : QWidget(parent)
{
    _channelCount = 1;
    createWidget();
}

AdcWidget::AdcWidget(uint16_t idPeriph, QWidget *parent)
    : QWidget(parent)
{
    _idPeriph = idPeriph;
    setWindowTitle(QString("ADC"));
    _channelCount = 1;
    createWidget();
}

void AdcWidget::recData(const QString &data)
{
    Q_UNUSED(data)
}

void AdcWidget::setChannelCount(int channelCount)
{
    _channelCount = channelCount;
    createWidget();
}

void AdcWidget::send()
{
    QByteArray dataToSend;
    for (int i=0; i<_channelCount; i++)
    {
        uint16_t data = static_cast<uint16_t>(_slidders[i]->value());
        dataToSend.append(static_cast<char>(data & 0xFF));
        dataToSend.append(static_cast<char>(data >> 8));
    }
    emit sendRequest(dataToSend);
}

void AdcWidget::createWidget()
{
    qDeleteAll(children());
    _slidders.clear();

    QLayout *layout = new QVBoxLayout();

    QGridLayout *sliddersLayout = new QGridLayout();
    for (int i=0; i<_channelCount; i++)
    {
        QLabel *numLabel = new QLabel(QString::number(i));
        numLabel->setAlignment(Qt::AlignCenter);
        sliddersLayout->addWidget(numLabel, 0, i);

        QSlider *slidder = new QSlider();
        slidder->setOrientation(Qt::Vertical);
        slidder->setRange(0, 4095);
        connect(slidder, SIGNAL(valueChanged(int)), this, SLOT(send()));
        sliddersLayout->addWidget(slidder, 1, i);
        sliddersLayout->setAlignment(slidder, Qt::AlignHCenter);
        _slidders.append(slidder);

        QLabel *valueLabel = new QLabel("0");
        valueLabel->setAlignment(Qt::AlignCenter);
        valueLabel->setMinimumWidth(valueLabel->fontMetrics().boundingRect("00000").width());
        sliddersLayout->addWidget(valueLabel, 2, i);
        connect(slidder, SIGNAL(valueChanged(int)), valueLabel, SLOT(setNum(int)));
    }
    layout->addItem(sliddersLayout);

    QLayout *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel(QString("adc")));
    _statusEnabled = new QLabel("disabled");
    statusLayout->addWidget(_statusEnabled);
    _params = new QLabel("");
    statusLayout->addWidget(_params);
    layout->addItem(statusLayout);

    setLayout(layout);
}
