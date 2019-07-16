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

#ifndef ADCWIDGET_H
#define ADCWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>

#include "driver/adc/adc.h"
#include "driver/adc/adc_sim.h"

class AdcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdcWidget(QWidget *parent = Q_NULLPTR);
    AdcWidget(uint16_t idPeriph, QWidget *parent = Q_NULLPTR);

    void recData(const QString &data);

    void setChannelCount(int channelCount);

signals:
    void sendRequest(QByteArray data);

protected slots:
    void send();

protected:
    QVector<QSlider *> _slidders;
    QLabel *_statusEnabled;
    QLabel *_params;
    void createWidget();

    uint16_t _idPeriph;
    int _channelCount;
};

#endif // ADCWIDGET_H
