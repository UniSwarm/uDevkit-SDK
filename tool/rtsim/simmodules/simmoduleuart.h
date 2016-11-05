#ifndef SIMMODULEUART_H
#define SIMMODULEUART_H

#include <QObject>

#include "simmodule.h"

#include "driver/periph/uart/uart_sim.h"

class SimModuleUart : public SimModule
{
public:
    SimModuleUart();

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);
};

#endif // SIMMODULEUART_H
