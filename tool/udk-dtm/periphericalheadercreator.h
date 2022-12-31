#ifndef PERIPHERICALHEADERCREATOR_H
#define PERIPHERICALHEADERCREATOR_H

#include "headercreator.h"

enum PeriphCap
{
    P_COUNT = 0x01,
    P_HAVE = 0x02,
    P_HAVE_MASK = 0x04,
    P_MAX = 0x08,
    P_UNIQUE = 0x10,
};

class PeriphericalHeaderCreator : public HeaderCreator
{
public:
    PeriphericalHeaderCreator(const EdcDb &db,
                              const QString &picFilter,
                              const QString &deviceName,
                              const QString &sfrFilter,
                              PeriphCap caps,
                              const QString &fileName,
                              const QString &haveExp = QString());
    void append(const QString &deviceName, const QString &sfrFilter, PeriphCap caps, const QString &haveExp = QString());

    int proccessMax(const QStringList &sfrList, const QRegularExpression &regExp);
    uint idValue(const QString &idString);
};

#endif  // PERIPHERICALHEADERCREATOR_H
