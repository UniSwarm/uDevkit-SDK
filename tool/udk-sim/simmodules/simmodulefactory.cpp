/**
 ** This file is part of the UDK-SDK project.
 ** Copyright 2019 UniSwarm sebastien.caux@uniswarm.eu
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/

#include "simmodulefactory.h"

#include "simmodule_adc.h"
#include "simmodule_gui.h"
#include "simmodule_mrobot.h"
#include "simmodule_uart.h"

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
            module = new SimModuleMRobot(client, idPeriph);
            break;
        default:
            module = nullptr;
            break;
    }
    return module;
}
