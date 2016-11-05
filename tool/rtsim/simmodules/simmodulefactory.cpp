#include "simmodulefactory.h"

#include "simmodule_uart.h"
#include "simmodule_gui.h"

SimModule *SimModuleFactory::getSimModule(uint16_t idModule)
{
    switch (idModule)
    {
    case UART_SIM_MODULE:
        return new SimModuleUart();
    case GUI_SIM_MODULE:
        return new SimModuleGui();
    default:
        break;
    }
    return NULL;
}
