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
                                                     const QString &fileName)
    : HeaderCreator(db, picFilter, fileName)
{
    QMultiMap<QString, QString> adbuffCpu;
    QMultiMap<QString, QString> cpuAadbuff;

    QRegularExpression sfrRegExp(sfrFilter);

    // Get regs from Db
    QRegularExpression picFileRegExp(picFilter);
    for (EDCParser *parser : db.parsers())
    {
        if (!picFileRegExp.match(parser->cpuName()).hasMatch())
        {
            continue;
        }

        QStringList sfrList;
        for (const EDCSFRDef &sfr : qAsConst(parser->sfrs()))
        {
            if (sfrRegExp.match(sfr.name).hasMatch())
            {
                sfrList << sfr.name;
            }
        }

        for (const QString &sfr : qAsConst(sfrList))
        {
            cpuAadbuff.insert(parser->deviceName(), sfr);
        }

        QString adFilter = sfrFilter;
        adFilter.remove(QRegularExpression("[\\^\\$]"));
        for (int i = 0; i < 64; i++)
        {
            QString adBuff = adFilter;
            adBuff.replace(QRegularExpression("\\(.*\\)"), QString::number(i));
            if (sfrList.contains(adBuff))
            {
                adbuffCpu.insert(adBuff, parser->deviceName());
            }
        }
    }

    // Count reg
    QMultiMap<uint, QString> regCount;
    QMultiMap<uint, QString> regMax;
    const QList<QString> &cpuUniqueKeys = cpuAadbuff.uniqueKeys();
    for (const QString &cpu : qAsConst(cpuUniqueKeys))
    {
        QStringList adBuff = cpuAadbuff.values(cpu);
        QCollator coll;
        coll.setNumericMode(true);
        std::sort(adBuff.begin(), adBuff.end(), [&](const QString &s1, const QString &s2) { return coll.compare(s1, s2) < 0; });

        QRegularExpressionMatch match = sfrRegExp.match(adBuff.last());
        int max = match.captured(1).toInt() + 1;
        int count = adBuff.count();
        regCount.insert(count, cpu);
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
            _cWritter->writeIfDefList(regMax.values(max));

            QStringList defines;
            QStringList values;
            defines << deviceName + "_MAX";
            values << QString::number(max);
            _cWritter->writeDefList(defines, values);
        }
        if (!regMax.uniqueKeys().isEmpty())
        {
            _cWritter->writeIfDefListEnd();
            (*_cWritter) << "\n";
        }
    }

    // have channel
    if ((caps & P_HAVE) != 0)
    {
        QMultiMap<QStringList, QString> adbuffCpuList;
        for (const QString &adBuff : adbuffCpu.uniqueKeys())
        {
            adbuffCpuList.insert(adbuffCpu.values(adBuff), adBuff);
        }
        for (const QStringList &cpus : adbuffCpuList.uniqueKeys())
        {
            _cWritter->writeIfDefList(cpus);
            QStringList defines;
            for (const QString &def : adbuffCpuList.values(cpus))
            {
                QRegularExpressionMatch match = sfrRegExp.match(def);
                QString idDef = match.captured(1);
                defines << QString("%1_HAVE_PORT%2").arg(deviceName).arg(idDef);
            }
        }
        *this << "\n";
    }
}
