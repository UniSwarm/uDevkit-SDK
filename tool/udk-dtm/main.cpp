#include <QCoreApplication>

#include "cwritter.h"
#include "edcparser.h"

#include <QCollator>
#include <QDebug>
#include <QDirIterator>
#include <QRegularExpression>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString picFilter = "DSPIC33(C|E.*GS)";
    QString sfrFilter = "ADCBUF[0-9]+";

    QStringList fileList;
    QRegularExpression picFileRegExp(picFilter);
    QDirIterator it("/opt/microchip/mplabx/v5.40/packs/Microchip/", QStringList("*.PIC"), QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        const QString &fileName = it.next();
        QFileInfo fileInfo(fileName);
        if (picFileRegExp.match(fileInfo.fileName()).hasMatch())
        {
            fileList << fileName;
        }
    }

    QMultiMap<QString, QString> adbuffCpu;
    QMultiMap<QString, QString> cpuAadbuff;

    QRegularExpression sfrRegExp(sfrFilter);
    for (const QString &fileName : fileList)
    {
        QStringList sfrList;
        EDCParser parser(fileName);
        for (const EDCSFRDef &sfr : parser.sfrs())
        {
            if (sfrRegExp.match(sfr.name).hasMatch())
            {
                sfrList << sfr.name;
            }
        }

        for (int i=0; i<64; i++)
        {
            QString adBuff = QString("ADCBUF%1").arg(i);
            if (sfrList.contains(adBuff))
            {
                QString deviceName = parser.name();
                deviceName.replace("DSPIC", "DEVICE_");
                deviceName.replace("PIC", "DEVICE_");
                adbuffCpu.insertMulti(adBuff, deviceName);
                cpuAadbuff.insertMulti(deviceName, adBuff);
            }
        }
    }

    CWritter cwriter("adBuff.c");

    // count / max
    QMultiMap<uint, QString> buffCount;
    QMultiMap<uint, QString> buffMax;
    for (const QString &cpu : cpuAadbuff.uniqueKeys())
    {
        QStringList adBuff = cpuAadbuff.values(cpu);
        QCollator coll;
        coll.setNumericMode(true);
        std::sort(adBuff.begin(), adBuff.end(), [&](const QString& s1, const QString& s2){ return coll.compare(s1, s2) < 0; });

        int max = adBuff.last().mid(6).toUInt() + 1;
        int count = adBuff.count();
        buffCount.insert(count, cpu);
        buffMax.insert(max, cpu);
    }
    for (uint count : buffCount.uniqueKeys())
    {
        cwriter.writeIfDefList(buffCount.values(count));

        QStringList defines, values;
        defines << "ADC_CHANNEL_COUNT";
        values << QString::number(count);
        cwriter.writeDefList(defines, values);
    }
    cwriter.writeIfDefListEnd();
    cwriter << "\n";

    for (uint max : buffMax.uniqueKeys())
    {
        cwriter.writeIfDefList(buffMax.values(max));

        QStringList defines, values;
        defines << "ADC_CHANNEL_MAX";
        values << QString::number(max);
        cwriter.writeDefList(defines, values);
    }
    cwriter.writeIfDefListEnd();
    cwriter << "\n";

    // have channel
    QMultiMap<QStringList, QString> adbuffCpuList;
    for (const QString &adBuff : adbuffCpu.uniqueKeys())
    {
        adbuffCpuList.insertMulti(adbuffCpu.values(adBuff), adBuff);
    }
    for (QStringList cpus : adbuffCpuList.uniqueKeys())
    {
        cwriter.writeIfDefList(cpus);
        QStringList defines;
        for (QString def : adbuffCpuList.values(cpus))
        {
            defines << "ADC_HAVE_CH" + def.mid(6);
        }
        cwriter.writeDefList(defines);
        cwriter.writeIfDefListEnd();
    }

    return 0;
}
