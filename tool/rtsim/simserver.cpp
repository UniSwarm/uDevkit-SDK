#include "simserver.h"

#include "simclient.h"

#include "archi/simulator/simulator.h"

#include <QDebug>

SimServer::SimServer(QObject *parent) : QObject(parent)
{
    _server = new QTcpServer();
    connect(_server, SIGNAL(newConnection()), this, SLOT(newClient()));
    _server->listen(QHostAddress::LocalHost, SIM_SOCKET_PORT);
}

bool SimServer::isConnected() const
{
    return _server->isListening();
}

void SimServer::newClient()
{
    qDebug()<<"new connection";
    QTcpSocket *socket = _server->nextPendingConnection();
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteClient()));
    _simClients.append(new SimClient(socket));
}

void SimServer::deleteClient()
{
    qDebug()<<"end connection";

}
