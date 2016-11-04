#ifndef SIMCLIENT_H
#define SIMCLIENT_H

#include <QObject>
#include <QTcpSocket>

class SimClient : public QObject
{
    Q_OBJECT
public:
    SimClient(QTcpSocket *socket);

signals:

protected slots:
    void readData();

protected:
    QTcpSocket *_socket;
};

#endif // SIMCLIENT_H
