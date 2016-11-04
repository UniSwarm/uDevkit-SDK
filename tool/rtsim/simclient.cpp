#include "simclient.h"

SimClient::SimClient(QTcpSocket *socket)
    : _socket(socket)
{
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SimClient::readData()
{
    qDebug()<<_socket->readAll();
}
