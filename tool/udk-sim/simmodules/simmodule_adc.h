#ifndef SIMMODULE_ADC_H
#define SIMMODULE_ADC_H

#include <QObject>

#include "simmodule.h"
#include "widgets/adcwidget/adcwidget.h"

#include "driver/adc/adc.h"
#include "driver/adc/adc_sim.h"

class SimModuleAdc : public SimModule
{
    Q_OBJECT
public:
    SimModuleAdc(SimClient *client, uint16_t idPeriph);

    [[nodiscard]] QWidget *widget() const override;

public slots:
    void pushData(uint16_t functionId, const QByteArray &data) override;

protected slots:
    void sendData(const QByteArray &str);

protected:
    AdcWidget *_adcWidget;
};

#endif  // SIMMODULE_ADC_H
