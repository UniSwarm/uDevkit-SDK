#include "simmodule_mrobot.h"

#include <QDebug>

SimModuleMRobot::SimModuleMRobot(uint16_t idPeriph)
    : SimModule(idPeriph)
{

}

void SimModuleMRobot::pushData(uint16_t functionId, const QByteArray &data)
{
    qDebug()<<"I am MROBOT sim!"<<functionId<<data.toHex()<<data.size();
}
