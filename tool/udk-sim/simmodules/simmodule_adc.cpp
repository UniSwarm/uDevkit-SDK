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

#include "simmodule_adc.h"

#include <QDebug>

SimModuleAdc::SimModuleAdc(SimClient *client, uint16_t idPeriph)
    : SimModule(client, ADC_SIM_MODULE, idPeriph)
{
    _adcWidget = new AdcWidget(idPeriph);
    connect(_adcWidget, SIGNAL(sendRequest(QByteArray)), (SimModuleAdc *)this, SLOT(sendData(QByteArray)));
    _adcWidget->show();
}

QWidget *SimModuleAdc::widget() const
{
    return _adcWidget;
}

void SimModuleAdc::pushData(uint16_t functionId, const QByteArray &data)
{
    if (functionId == 0)
    {
        _adcWidget->setChannelCount(data[0]);
    }
}

void SimModuleAdc::sendData(const QByteArray &str)
{
    QByteArray data;
    data.append(str);
    writeData(ADC_SIM_READ, data);
}
