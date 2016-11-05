#include "simclient.h"

#include "simmodules/simmodulefactory.h"

SimClient::SimClient(QTcpSocket *socket)
    : _socket(socket)
{
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

SimModule *SimClient::module(uint16_t idModule) const
{
    QMap<uint16_t, SimModule*>::const_iterator localConstFind = _modules.constFind(idModule);
    if(localConstFind != _modules.constEnd())
        return *localConstFind;
    return NULL;
}

void SimClient::readData()
{
    QByteArray dataReceive = _socket->readAll();
    short moduleId = *((short*)dataReceive.mid(0,2).data());
    short functionId = *((short*)dataReceive.mid(2,2).data());
    QByteArray data = dataReceive.mid(4);

    SimModule *modulePtr = module(moduleId);
    if(!modulePtr)
    {
        modulePtr = SimModuleFactory::getSimModule(moduleId);
        if(!modulePtr)
            return;

        _modules.insert(moduleId, modulePtr);
    }
    modulePtr->pushData(functionId, data);
}
