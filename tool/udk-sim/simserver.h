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

#ifndef SIMSERVER_H
#define SIMSERVER_H

#include <QList>
#include <QObject>
#include <QTcpServer>

class SimClient;

class SimServer : public QObject
{
    Q_OBJECT
protected:
    SimServer(QObject *parent = Q_NULLPTR);

public:
    bool isConnected() const;
    static SimServer *instance();

signals:
    void clientAdded(SimClient *client);
    void clientClosed(SimClient *client);

protected slots:
    void newClient();
    void deleteClient(QAbstractSocket::SocketError error);

protected:
    QTcpServer *_server;
    QList<SimClient *> _simClients;
    static SimServer *server;
};

#endif  // SIMSERVER_H
