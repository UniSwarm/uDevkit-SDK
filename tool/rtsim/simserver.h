#ifndef SIMSERVER_H
#define SIMSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>

class SimClient;

class SimServer : public QObject
{
    Q_OBJECT
public:
    explicit SimServer(QObject *parent = 0);

    bool isConnected() const;

signals:

public slots:

protected slots:
    void newClient();
    void deleteClient(QAbstractSocket::SocketError error);

protected:
    QTcpServer *_server;
    QList<SimClient *> _simClients;
};

#endif // SIMSERVER_H
