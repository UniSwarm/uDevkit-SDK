#include "simserver.h"

#include "simclient.h"

#include <QDebug>

SimServer::SimServer(QObject *parent) : QObject(parent)
{
    _server = new QTcpServer();
    connect(_server, SIGNAL(newConnection()), this, SLOT(newClient()));
    _server->listen(QHostAddress::LocalHost, 1064);
}

void SimServer::newClient()
{
    QTcpSocket *socket = _server->nextPendingConnection();
    _simClients.append(new SimClient(socket));
    qDebug()<<"new connection";
}
