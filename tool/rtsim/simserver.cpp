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
    if (!server)
        server = new SimServer();

    return server;
}

void SimServer::newClient()
{
    //qDebug()<<"new connection";
    QTcpSocket *socket = _server->nextPendingConnection();
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteClient(QAbstractSocket::SocketError)));
    _simClients.append(new SimClient(socket));
}

void SimServer::deleteClient(QAbstractSocket::SocketError error)
{
    /*if(error == QAbstractSocket::RemoteHostClosedError)
        qDebug()<<"end connection";*/
}
