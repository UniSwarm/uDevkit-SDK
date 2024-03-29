#include "periphericalheadercreator.h"

#include <QCollator>
#include <QDebug>
#include <QMultiMap>
#include <QPair>
#include <QRegularExpression>

PeriphericalHeaderCreator::PeriphericalHeaderCreator(const EdcDb &db,
                                                     const QString &picFilter,
                                                     const QString &deviceName,
                                                     const QString &sfrFilter,
                                                     PeriphCap caps,
                                                     const QString &fileName,
                                                     const QString &haveExp)
    : HeaderCreator(db, picFilter, fileName)
{
    append(deviceName, sfrFilter, caps, haveExp);
}

void PeriphericalHeaderCreator::append(const QString &deviceName, const QString &sfrFilter, PeriphCap caps, const QString &haveExp)
{
    const QStringList &sfrFilterPart = sfrFilter.split("\\.");
    QString regFilter;
    QString fieldFilter;
    if (sfrFilterPart.count() > 1)
    {
        regFilter = sfrFilterPart[0];
        fieldFilter = sfrFilterPart[1];
    }
    else
    {
        regFilter = sfrFilter;
    }
    QRegularExpression sfrFullRegExp(sfrFilter);
    QRegularExpression sfrRegExp(regFilter);
    QRegularExpression sfrFieldRegExp(fieldFilter);

    // Get regs from Db
    int deviceCount = 0;
    QRegularExpression picFileRegExp(_picFilter);
    QMultiMap<QString, QString> sfrCpuListMap;
    QMultiMap<QString, QString> cpuSfrListMap;
    for (EDCParser *parser : _db.parsers())
    {
        if (!picFileRegExp.match(parser->cpuName()).hasMatch())
        {
            continue;
        }
        deviceCount++;

        QStringList sfrList;
        for (const EDCSFRDef &sfr : qAsConst(parser->sfrs()))
        {
            if (sfrRegExp.match(sfr.name).hasMatch())
            {
                if (fieldFilter.isEmpty())
                {
                    sfrList << sfr.name;
                    continue;
                }
                for (const EDCSFRFieldDef &field : qAsConst(sfr.fields))
                {
                    if (sfrFieldRegExp.match(field.name).hasMatch())
                    {
                        sfrList << sfr.name + '.' + field.name;
                    }
                }
            }
        }

        for (const QString &sfr : qAsConst(sfrList))
        {
            cpuSfrListMap.insert(parser->deviceName(), sfr);
        }

        QString adFilter = sfrFilter;
        adFilter.replace("\\.", ".");
        adFilter.remove(QRegularExpression("[\\^\\$]"));
        const QStringList sfrListFiltered = sfrList.filter(QRegularExpression(adFilter));
        for (const QString &def : sfrListFiltered)
        {
            sfrCpuListMap.insert(def, parser->deviceName());
        }
    }

    // Count sfr and process max
    QMultiMap<uint, QString> regCount;
    QMultiMap<uint, QString> regMax;
    const QList<QString> &cpuUniqueKeys = cpuSfrListMap.uniqueKeys();
    for (const QString &cpu : qAsConst(cpuUniqueKeys))
    {
        const QStringList &sfrList = cpuSfrListMap.values(cpu);

        int count = sfrList.count();
        regCount.insert(count, cpu);

        int max = proccessMax(sfrList, sfrFullRegExp);
        regMax.insert(max, cpu);
    }

    // Write count
    if ((caps & P_COUNT) != 0 && (caps & P_UNIQUE) == 0)
    {
        const QList<uint> &countList = regCount.uniqueKeys();
        for (uint count : countList)
        {
            writeIfDefList(regCount.values(count));
            writeDefList(QStringList() << deviceName + "_COUNT", QStringList() << QString::number(count));
        }
        if (!regCount.uniqueKeys().isEmpty())
        {
            writeIfDefElse();
            writeDefList(QStringList() << deviceName + "_COUNT", QStringList() << "0");
            writeIfDefListEnd();
            *this << "\n";
        }
    }

    // Write max
    if ((caps & P_MAX) != 0 && (caps & P_UNIQUE) == 0)
    {
        const QList<uint> &maxList = regMax.uniqueKeys();
        if (maxList.count() == 1 && regMax.values(maxList.first()).size() == deviceCount)
        {
            writeDefList(QStringList() << deviceName + "_MAX", QStringList() << QString::number(maxList.first()));
        }
        else
        {
            for (uint max : maxList)
            {
                writeIfDefList(regMax.values(max));
                writeDefList(QStringList() << deviceName + "_MAX", QStringList() << QString::number(max));
            }
        }
        if (maxList.size() > 1)
        {
            writeIfDefListEnd();
        }
        *this << "\n";
    }

    // Write have
    QString haveExpression = haveExp;
    if (haveExpression.isEmpty())
    {
        haveExpression = deviceName + "_HAVE_%1";
    }
    bool hasArg = haveExpression.contains("%1");
    if ((caps & P_HAVE) != 0 && (caps & P_UNIQUE) == 0)
    {
        const QStringList &regList = sfrCpuListMap.uniqueKeys();
        QMultiMap<QStringList, QString> regCpuList;
        for (const QString &reg : regList)
        {
            regCpuList.insert(sfrCpuListMap.values(reg), reg);
        }

        QList<QStringList> cpusKeys = regCpuList.uniqueKeys();
        std::sort(cpusKeys.begin(), cpusKeys.end(), [&](const QStringList &s1, const QStringList &s2) {
            return s1.size() > s2.size();
        });

        for (const QStringList &cpus : qAsConst(cpusKeys))
        {
            bool allCPU = (cpus.count() == deviceCount);
            if (!allCPU)
            {
                writeIfDefList(cpus);
            }
            QStringList defines;
            const QStringList &defCpus = regCpuList.values(cpus);
            for (const QString &def : defCpus)
            {
                QRegularExpressionMatch match = sfrFullRegExp.match(def);
                QString idDef = match.captured(1);
                if (hasArg)
                {
                    defines << haveExpression.arg(idDef);
                }
                else
                {
                    defines << haveExpression;
                }
            }

            QCollator coll;
            coll.setNumericMode(true);
            QStringList sortedDef = defines;
            std::sort(sortedDef.begin(), sortedDef.end(), [&](const QString &s1, const QString &s2) {
                return coll.compare(s1, s2) < 0;
            });
            writeDefList(sortedDef);
            if (!allCPU)
            {
                writeIfDefListEnd();
            }
        }
        *this << "\n";
    }

    if ((caps & P_UNIQUE) != 0)
    {
        const QStringList &cpuList = cpuSfrListMap.uniqueKeys();
        QMultiMap<QStringList, QString> cpuRegList;
        for (const QString &cpu : cpuList)
        {
            cpuRegList.insert(cpuSfrListMap.values(cpu), cpu);
        }

        QList<QStringList> regsKeys = cpuRegList.uniqueKeys();
        for (const QStringList &regs : qAsConst(regsKeys))
        {
            const QStringList &cpusList = cpuRegList.values(regs);
            writeIfDefList(cpusList);

            if ((caps & P_HAVE) != 0)
            {
                QStringList defines;
                uint64_t mask = 0;
                for (const QString &reg : regs)
                {
                    QRegularExpressionMatch match = sfrFullRegExp.match(reg);
                    QString idDef = match.captured(1);
                    if (hasArg)
                    {
                        defines << haveExpression.arg(idDef);
                    }
                    else
                    {
                        defines << haveExpression;
                    }
                    mask |= (1LU << (idValue(idDef) & 0x3F));
                }
                QCollator coll;
                coll.setNumericMode(true);
                QStringList sortedDef = defines;
                std::sort(sortedDef.begin(), sortedDef.end(), [&](const QString &s1, const QString &s2) {
                    return coll.compare(s1, s2) < 0;
                });
                writeDefList(sortedDef);

                if ((caps & P_HAVE_MASK) != 0)
                {
                    int max = proccessMax(regs, sfrFullRegExp);
                    int bits = 16;
                    if (max > bits)
                    {
                        bits = 32;
                    }
                    if (max > bits)
                    {
                        bits = 64;
                    }
                    writeDefList(QStringList() << deviceName + "_HAVE_MASK", QStringList() << hex(mask, bits));
                }
            }

            if ((caps & P_COUNT) != 0)
            {
                writeDefList(QStringList() << deviceName + "_COUNT", QStringList() << QString::number(regs.count()));
            }

            if ((caps & P_MAX) != 0)
            {
                int max = proccessMax(regs, sfrFullRegExp);
                writeDefList(QStringList() << deviceName + "_MAX", QStringList() << QString::number(max));
            }
        }
        writeIfDefListEnd();
        *this << "\n";
    }
}

int PeriphericalHeaderCreator::proccessMax(const QStringList &sfrList, const QRegularExpression &regExp)
{
    int max = 0;
    for (const QString &def : sfrList)
    {
        QRegularExpressionMatch match = regExp.match(def);
        QString matchPart = match.captured(1);
        if (matchPart.isEmpty())
        {
            continue;
        }
        int value = idValue(matchPart);
        if (max < value)
        {
            max = value;
        }
    }
    return max;
}

uint PeriphericalHeaderCreator::idValue(const QString &idString)
{
    if (idString[0].isLetter())
    {
        return idString[0].toLatin1() - 'A' + 1;
    }
    else
    {
        return idString.toUInt();
    }
}
