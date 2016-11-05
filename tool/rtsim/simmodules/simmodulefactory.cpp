#include "simmodulefactory.h"

#include "simmoduleuart.h"

SimModule *SimModuleFactory::getSimModule(uint16_t idModule)
{
    switch (idModule)
    {
    case UART_SIM_MODULE:
        return new SimModuleUart();
    default:
        break;
    }
    return NULL;
}
