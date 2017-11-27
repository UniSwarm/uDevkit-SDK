#ifndef SIMSERVER_H
#define SIMSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>

class SimClient;

class SimServer : public QObject
{
    Q_OBJECT
protected:
    SimServer(QObject *parent = 0);

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

#endif // SIMSERVER_H
