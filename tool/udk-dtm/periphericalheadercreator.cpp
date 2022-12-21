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
    QMultiMap<QString, QString> adbuffCpu;
    QMultiMap<QString, QString> cpuAadbuff;

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
            cpuAadbuff.insert(parser->deviceName(), sfr);
        }

        QString adFilter = sfrFilter;
        adFilter.replace("\\.", ".");
        adFilter.remove(QRegularExpression("[\\^\\$]"));
        const QStringList sfrListFiltered = sfrList.filter(QRegularExpression(adFilter));
        for (const QString &def : sfrListFiltered)
        {
            adbuffCpu.insert(def, parser->deviceName());
        }
    }

    // Count reg
    QMultiMap<uint, QString> regCount;
    QMultiMap<uint, QString> regMax;
    const QList<QString> &cpuUniqueKeys = cpuAadbuff.uniqueKeys();
    for (const QString &cpu : qAsConst(cpuUniqueKeys))
    {
        const QStringList &adBuff = cpuAadbuff.values(cpu);

        int count = adBuff.count();
        regCount.insert(count, cpu);

        int max = 0;
        for (const QString &def : adBuff)
        {
            QRegularExpressionMatch match = sfrFullRegExp.match(def);
            QString matchPart = match.captured(1);
            if (matchPart.isEmpty())
            {
                continue;
            }
            int value = 0;
            if (matchPart[0].isLetter())
            {
                value = matchPart[0].toLatin1() - 'A';
            }
            else
            {
                value = match.captured(1).toInt() + 1;
            }
            if (max < value)
            {
                max = value;
            }
        }
        regMax.insert(max, cpu);
    }

    if ((caps & P_COUNT) != 0)
    {
        for (uint count : regCount.uniqueKeys())
        {
            writeIfDefList(regCount.values(count));

            QStringList defines;
            QStringList values;
            defines << deviceName + "_COUNT";
            values << QString::number(count);
            writeDefList(defines, values);
        }
        if (!regCount.uniqueKeys().isEmpty())
        {
            writeIfDefElse();
            QStringList defines;
            QStringList values;
            defines << deviceName + "_COUNT";
            values << "0";
            writeDefList(defines, values);
            writeIfDefListEnd();
            *this << "\n";
        }
    }

    // Max
    if ((caps & P_MAX) != 0)
    {
        for (uint max : regMax.uniqueKeys())
        {
            writeIfDefList(regMax.values(max));

            QStringList defines;
            QStringList values;
            defines << deviceName + "_MAX";
            values << QString::number(max);
            writeDefList(defines, values);
        }
        if (!regMax.uniqueKeys().isEmpty())
        {
            writeIfDefListEnd();
            *this << "\n";
        }
    }

    // have channel
    QString haveExpression = haveExp;
    if (haveExpression.isEmpty())
    {
        haveExpression = deviceName + "_HAVE_%1";
    }
    bool hasArg = haveExpression.contains("%1");
    if ((caps & P_HAVE) != 0)
    {
        QMultiMap<QStringList, QString> adbuffCpuList;
        for (const QString &adBuff : adbuffCpu.uniqueKeys())
        {
            adbuffCpuList.insert(adbuffCpu.values(adBuff), adBuff);
        }

        QList<QStringList> cpusKeys = adbuffCpuList.uniqueKeys();
        std::sort(cpusKeys.begin(), cpusKeys.end(), [&](const QStringList &s1, const QStringList &s2) {
            return s1.size() > s2.size();
        });

        for (const QStringList &cpus : cpusKeys)
        {
            bool allCPU = (cpus.count() == deviceCount);
            if (!allCPU)
            {
                writeIfDefList(cpus);
            }
            QStringList defines;
            for (const QString &def : adbuffCpuList.values(cpus))
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
}
