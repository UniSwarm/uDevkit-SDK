#include "simmodulefactory.h"

#include "simmodule_uart.h"
#include "simmodule_gui.h"

SimModule *SimModuleFactory::getSimModule(uint16_t idModule, uint16_t idPeriph)
{
    SimModule *module;
    switch (idModule)
    {
    case UART_SIM_MODULE:
        module = new SimModuleUart(idPeriph);
        break;
    case GUI_SIM_MODULE:
        module = new SimModuleGui(idPeriph);
        break;
    default:
        module = NULL;
        break;
    }
    return module;
}
