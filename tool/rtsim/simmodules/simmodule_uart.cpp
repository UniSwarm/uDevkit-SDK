#include "simmodule_uart.h"

#include <QDebug>

SimModuleUart::SimModuleUart(SimClient *client, uint16_t idPeriph)
    : SimModule(client, UART_SIM_MODULE, idPeriph)
{
    _uartWidget = new UartWidget(idPeriph);
    connect(_uartWidget, SIGNAL(sendRequest(QString)), (SimModuleUart*)this, SLOT(sendData(QString)));
    _uartWidget->show();
}

QWidget *SimModuleUart::widget() const
{
    return _uartWidget;
}

void SimModuleUart::pushData(uint16_t functionId, const QByteArray &data)
{
    switch (functionId)
    {
    case UART_SIM_CONFIG:
        memcpy((char*)&_config_uart, data.data(), sizeof(_config_uart));
        _uartWidget->setConfig(_config_uart);
        break;
    case UART_SIM_WRITE:
        _uartWidget->recData(data.data());
        break;
    default:
        break;
    }
}

void SimModuleUart::sendData(QString str)
{
    QByteArray data;
    data.append(str.replace("\\t","\t").replace("\\n","\n").replace("\\r","\r"));
    writeData(UART_SIM_READ, data);
}
