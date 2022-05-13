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

#include "simclient.h"

#include "simmodules/simmodulefactory.h"

SimClient::SimClient(QTcpSocket *socket)
    : _socket(socket)
{
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

SimModule *SimClient::module(uint16_t idModule, uint16_t idPeriph) const
{
    uint32_t key = static_cast<uint32_t>((idModule << 16) + idPeriph);
    QMap<uint32_t, SimModule *>::const_iterator localConstFind = _modules.constFind(key);
    if (localConstFind != _modules.constEnd())
    {
        return *localConstFind;
    }
    return Q_NULLPTR;
}

void SimClient::writeData(uint16_t moduleId, uint16_t periphId, uint16_t functionId, const QByteArray &data)
{
    char header[8];
    QByteArray packet;

    (reinterpret_cast<uint16_t *>(header))[0] = static_cast<uint16_t>(data.size()) + 8;
    (reinterpret_cast<uint16_t *>(header))[1] = moduleId;
    (reinterpret_cast<uint16_t *>(header))[2] = periphId;
    (reinterpret_cast<uint16_t *>(header))[3] = functionId;
    packet.append(header, 8);
    packet.append(data);

    _socket->write(packet);
}

void SimClient::readData()
{
    _dataReceive.append(_socket->readAll());
    while (_dataReceive.size() > 6)
    {
        unsigned short sizePacket = *(reinterpret_cast<unsigned short *>(_dataReceive.mid(0, 2).data()));

        if (sizePacket > _dataReceive.size())
        {
            return;
        }

        unsigned short moduleId = *(reinterpret_cast<unsigned short *>(_dataReceive.mid(2, 2).data()));
        unsigned short periphId = *(reinterpret_cast<unsigned short *>(_dataReceive.mid(4, 2).data()));
        unsigned short functionId = *(reinterpret_cast<unsigned short *>(_dataReceive.mid(6, 2).data()));
        QByteArray data = _dataReceive.mid(8, sizePacket - 8);

        SimModule *modulePtr = module(moduleId, periphId);
        if (modulePtr == nullptr)
        {
            modulePtr = SimModuleFactory::getSimModule(this, moduleId, periphId);
            if (modulePtr == nullptr)
            {
                qDebug() << "Unknow module" << moduleId << sizePacket;
                _dataReceive = _dataReceive.mid(sizePacket);
                continue;
            }

            _modules.insert(static_cast<uint32_t>((moduleId << 16) + periphId), modulePtr);
        }

        modulePtr->pushData(functionId, data);

        _dataReceive = _dataReceive.mid(sizePacket);
    }
}
