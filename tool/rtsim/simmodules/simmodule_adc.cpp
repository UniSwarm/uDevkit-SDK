#include "simmodule_adc.h"

#include <QDebug>

SimModuleAdc::SimModuleAdc(SimClient *client, uint16_t idPeriph)
    : SimModule(client, ADC_SIM_MODULE, idPeriph)
{
    _adcWidget = new AdcWidget(idPeriph);
    connect(_adcWidget, SIGNAL(sendRequest(QByteArray)), (SimModuleAdc*)this, SLOT(sendData(QByteArray)));
    _adcWidget->show();
}

QWidget *SimModuleAdc::widget() const
{
    return _adcWidget;
}

void SimModuleAdc::pushData(uint16_t functionId, const QByteArray &data)
{
    Q_UNUSED(functionId)
    Q_UNUSED(data)
}

void SimModuleAdc::sendData(QByteArray str)
{
    QByteArray data;
    data.append(str);
    writeData(ADC_SIM_READ, data);
}
