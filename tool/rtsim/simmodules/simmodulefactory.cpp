#include "simmodulefactory.h"

#include "simmodule_uart.h"
#include "simmodule_gui.h"

SimModule *SimModuleFactory::getSimModule(uint16_t idModule)
{
    SimModule *module;
    switch (idModule)
    {
    case UART_SIM_MODULE:
        module = new SimModuleUart();
        break;
    case GUI_SIM_MODULE:
        module = new SimModuleGui();
        break;
    default:
        module = NULL;
        break;
    }
    return module;
}
