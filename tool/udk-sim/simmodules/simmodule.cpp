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

#include "simmodule.h"

#include "simclient.h"

SimModule::SimModule(SimClient *client, uint16_t idModule, uint16_t idPeriph)
    : _client(client), _idModule(idModule), _idPeriph(idPeriph)
{
}

SimClient *SimModule::client() const
{
    return _client;
}

uint16_t SimModule::idModule() const
{
    return _idModule;
}

uint16_t SimModule::idPeriph() const
{
    return _idPeriph;
}

void SimModule::writeData(uint16_t functionId, const QByteArray &data)
{
    _client->writeData(_idModule, _idPeriph, functionId, data);
}
