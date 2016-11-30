#ifndef SIMMODULE_MROBOT_H
#define SIMMODULE_MROBOT_H

#include <QObject>

#include "simmodule.h"

#include "driver/periph/uart/uart_sim.h"

class SimModuleMRobot : public SimModule
{
public:
    SimModuleMRobot(uint16_t idPeriph);

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);
};

#endif // SIMMODULE_MROBOT_H
