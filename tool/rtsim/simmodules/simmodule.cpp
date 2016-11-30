#include "simmodule.h"

SimModule::SimModule(uint16_t idPeriph)
    : _idPeriph(idPeriph)
{
}

uint16_t SimModule::idPeriph() const
{
    return _idPeriph;
}
