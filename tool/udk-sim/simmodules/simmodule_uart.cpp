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

#include "simmodule_uart.h"

#include <QDebug>

SimModuleUart::SimModuleUart(SimClient *client, uint16_t idPeriph)
    : SimModule(client, UART_SIM_MODULE, idPeriph)
{
    _uartWidget = new UartWidget(idPeriph);
    connect(_uartWidget, SIGNAL(sendRequest(QString)), (SimModuleUart*)this, SLOT(sendData(QString)));
    _uartWidget->show();
}

QWidget *SimModuleUart::widget() const
{
    return _uartWidget;
}

void SimModuleUart::pushData(uint16_t functionId, const QByteArray &data)
{
    switch (functionId)
    {
    case UART_SIM_CONFIG:
        memcpy((char*)&_config_uart, data.data(), sizeof(_config_uart));
        _uartWidget->setConfig(_config_uart);
        break;
    case UART_SIM_WRITE:
        _uartWidget->recFromUart(data.data());
        break;
    default:
        break;
    }
}

void SimModuleUart::sendData(QString str)
{
    QByteArray data;
    data.append(str.replace("\\t","\t").replace("\\n","\n").replace("\\r","\r"));
    writeData(UART_SIM_READ, data);
}
