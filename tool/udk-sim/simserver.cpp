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

#include "simserver.h"

#include "simclient.h"

#include "archi/simulator/simulator.h"

#include <QDebug>

SimServer *SimServer::server = Q_NULLPTR;

SimServer::SimServer(QObject *parent)
    : QObject(parent)
{
    _server = new QTcpServer(this);
    connect(_server, SIGNAL(newConnection()), this, SLOT(newClient()));
    _server->listen(QHostAddress::LocalHost, SIM_SOCKET_PORT);
}

bool SimServer::isConnected() const
{
    return _server->isListening();
}

SimServer *SimServer::instance()
{
    if (server == nullptr)
    {
        server = new SimServer();
    }

    return server;
}

void SimServer::newClient()
{
    // qDebug()<<"new connection";
    QTcpSocket *socket = _server->nextPendingConnection();
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteClient(QAbstractSocket::SocketError)));

    SimClient *client = new SimClient(socket);
    _simClients.append(client);
    emit clientAdded(client);
}

void SimServer::deleteClient(QAbstractSocket::SocketError error)
{
    SimClient *client = static_cast<SimClient *>(sender());
    /*if(error == QAbstractSocket::RemoteHostClosedError)
        qDebug()<<"end connection";*/

    emit clientClosed(client);
}
