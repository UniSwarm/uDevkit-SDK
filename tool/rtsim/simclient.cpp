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
    _dataReceive.append(_socket->readAll());
    while(_dataReceive.size()>6)
    {
        unsigned short sizePacket = *((short*)_dataReceive.mid(0,2).data());

        if(sizePacket>_dataReceive.size())
            return;

        unsigned short moduleId = *((short*)_dataReceive.mid(2,2).data());
        unsigned short functionId = *((short*)_dataReceive.mid(4,2).data());
        QByteArray data = _dataReceive.mid(6, sizePacket-6);

        SimModule *modulePtr = module(moduleId);
        if(!modulePtr)
        {
            modulePtr = SimModuleFactory::getSimModule(moduleId);
            if(!modulePtr)
            {
                qDebug()<<"Unknow module"<<moduleId<<sizePacket;
                _dataReceive = _dataReceive.mid(sizePacket);
                continue;
            }

            _modules.insert(moduleId, modulePtr);
        }

        modulePtr->pushData(functionId, data);

        _dataReceive = _dataReceive.mid(sizePacket);
    }
}
