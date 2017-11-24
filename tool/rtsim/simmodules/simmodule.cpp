#include "simmodule.h"

#include "simclient.h"

SimModule::SimModule(SimClient *client, uint16_t idModule, uint16_t idPeriph)
    : _client(client), _idModule(idModule), _idPeriph(idPeriph)
{
}

SimClient *SimModule::client() const
{
    return _client;
}

uint16_t SimModule::idModule() const
{
    return _idModule;
}

uint16_t SimModule::idPeriph() const
{
    return _idPeriph;
}

void SimModule::writeData(uint16_t functionId, const QByteArray &data)
{
    _client->writeData(_idModule, _idPeriph, functionId, data);
}
