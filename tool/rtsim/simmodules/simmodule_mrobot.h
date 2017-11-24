#ifndef SIMMODULE_MROBOT_H
#define SIMMODULE_MROBOT_H

#include <QObject>

#include "simmodule.h"

#include "module/mrobot/mrobot.h"
#include "module/mrobot/mrobot_sim.h"

class SimModuleMRobot : public SimModule
{
    Q_OBJECT
public:
    SimModuleMRobot(SimClient *client, uint16_t idPeriph);

    QWidget *widget() const;

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);
};

#endif // SIMMODULE_MROBOT_H
