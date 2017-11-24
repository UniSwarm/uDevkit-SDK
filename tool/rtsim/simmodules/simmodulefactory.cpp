#include "simmodulefactory.h"

#include "simmodule_uart.h"
#include "simmodule_adc.h"
#include "simmodule_gui.h"
#include "simmodule_mrobot.h"

SimModule *SimModuleFactory::getSimModule(SimClient *client, uint16_t idModule, uint16_t idPeriph)
{
    SimModule *module;
    switch (idModule)
    {
    case UART_SIM_MODULE:
        module = new SimModuleUart(client, idPeriph);
        break;
    case ADC_SIM_MODULE:
        module = new SimModuleAdc(client, idPeriph);
        break;
    case GUI_SIM_MODULE:
        module = new SimModuleGui(client, idPeriph);
        break;
    case MROBOT_SIM_MODULE:
        module = new SimModuleGui(client, idPeriph);
        break;
    default:
        module = NULL;
        break;
    }
    return module;
}
