#ifndef SIMCLIENT_H
#define SIMCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>

#include "simmodules/simmodule.h"

class SimClient : public QObject
{
    Q_OBJECT
public:
    SimClient(QTcpSocket *socket);

    SimModule *module(uint16_t idModule, uint16_t idPeriph) const;

signals:

protected slots:
    void readData();

protected:
    QTcpSocket *_socket;
    QMap<uint32_t, SimModule*> _modules;
    QByteArray _dataReceive;
};

#endif // SIMCLIENT_H
