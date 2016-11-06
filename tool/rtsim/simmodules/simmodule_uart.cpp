#include "simmodule_uart.h"

#include <QDebug>

SimModuleUart::SimModuleUart()
{

}

void SimModuleUart::pushData(uint16_t functionId, const QByteArray &data)
{
    qDebug()<<"I am UART sim!"<<functionId<<data.toHex()<<data.size();
}
