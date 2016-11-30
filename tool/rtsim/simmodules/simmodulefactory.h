#ifndef SIMMODULEFACTORY_H
#define SIMMODULEFACTORY_H

#include "simmodule.h"

class SimModuleFactory
{
public:
    static SimModule *getSimModule(uint16_t idModule, uint16_t idPeriph);
};

#endif // SIMMODULEFACTORY_H
