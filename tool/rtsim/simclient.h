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

    SimModule *module(uint16_t idModule) const;

signals:

protected slots:
    void readData();

protected:
    QTcpSocket *_socket;
    QMap<uint16_t, SimModule*> _modules;
};

#endif // SIMCLIENT_H
