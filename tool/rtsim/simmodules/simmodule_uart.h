#ifndef SIMMODULEUART_H
#define SIMMODULEUART_H

#include <QObject>

#include "simmodule.h"

#include "driver/periph/uart/uart_sim.h"

class SimModuleUart : public SimModule
{
public:
    SimModuleUart(uint16_t idPeriph);

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);

protected:
    uart_dev _config_uart;
};

#endif // SIMMODULEUART_H
