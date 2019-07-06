#ifndef SIMMODULEFACTORY_H
#define SIMMODULEFACTORY_H

#include "simmodule.h"

class SimModuleFactory
{
public:
    static SimModule *getSimModule(SimClient *client, uint16_t idModule, uint16_t idPeriph);
};

#endif // SIMMODULEFACTORY_H
