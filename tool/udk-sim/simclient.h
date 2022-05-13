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

#ifndef SIMCLIENT_H
#define SIMCLIENT_H

#include <QMap>
#include <QObject>
#include <QTcpSocket>

#include "simmodules/simmodule.h"

class SimClient : public QObject
{
    Q_OBJECT
public:
    SimClient(QTcpSocket *socket);

    [[nodiscard]] SimModule *module(uint16_t idModule, uint16_t idPeriph) const;

    void writeData(uint16_t moduleId, uint16_t periphId, uint16_t functionId, const QByteArray &data);

signals:

protected slots:
    void readData();

protected:
    QTcpSocket *_socket;
    QMap<uint32_t, SimModule *> _modules;
    QByteArray _dataReceive;
};

#endif  // SIMCLIENT_H
