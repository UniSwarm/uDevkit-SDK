#include "simmodule_uart.h"

#include <QDebug>

SimModuleUart::SimModuleUart(uint16_t idPeriph)
    : SimModule(idPeriph)
{

}

void SimModuleUart::pushData(uint16_t functionId, const QByteArray &data)
{
    qDebug()<<"I am UART sim!"<<_idPeriph<<functionId<<data.toHex()<<data.size();

    switch (functionId)
    {
    case UART_SIM_CONFIG:
        memcpy((char*)&_config_uart, data.data(), sizeof(_config_uart));

        /*qDebug()<<"baudSpeed: "<<_config_uart.baudSpeed;
        qDebug()<<"bitLenght: "<<_config_uart.bitLenght;
        qDebug()<<"bitParity: "<<_config_uart.bitParity;
        qDebug()<<"bitStop: "<<_config_uart.bitStop;
        qDebug()<<"enabled: "<<_config_uart.enabled;*/
        break;
    default:
        break;
    }

}
