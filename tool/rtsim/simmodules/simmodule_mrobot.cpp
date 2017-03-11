#include "simmodule_mrobot.h"

#include <QDebug>

SimModuleMRobot::SimModuleMRobot(SimClient *client, uint16_t idPeriph)
    : SimModule(client, MROBOT_SIM_MODULE, idPeriph)
{

}

QWidget *SimModuleMRobot::widget() const
{
    return NULL;
}

void SimModuleMRobot::pushData(uint16_t functionId, const QByteArray &data)
{
    qDebug()<<"I am MROBOT sim!"<<functionId<<data.toHex()<<data.size();
}
