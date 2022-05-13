#ifndef PERIPHERICALHEADERCREATOR_H
#define PERIPHERICALHEADERCREATOR_H

#include "headercreator.h"

enum PeriphCap
{
    P_COUNT = 0x01,
    P_HAVE = 0x02,
    P_MAX = 0x04,
};

class PeriphericalHeaderCreator : public HeaderCreator
{
public:
    PeriphericalHeaderCreator(const EdcDb &db, const QString &picFilter, const QString &deviceName, const QString &sfrFilter, PeriphCap caps, const QString &fileName);
};

#endif // PERIPHERICALHEADERCREATOR_H
