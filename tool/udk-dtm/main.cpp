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

#ifdef WIN32
    QString edsPath = "C:/Program Files (x86)/Microchip/MPLABX/v5.40/packs/Microchip/";
#else
    QString edsPath = "/opt/microchip/mplabx/v5.40/packs/Microchip/";
    // QString edsPath = "/opt/microchip/mplabx/v5.25/packs/Microchip/";
#endif
    QString picFilter = "(DSPIC33|PIC24)[CE]";
    QString sfrFilter = "ADCBUF([0-9]+)";
    QString deviceName = "ADC";
    QString outputFileName = "adc_dspic33.h";

    QStringList fileList;
    QRegularExpression picFileRegExp(picFilter);
    QDirIterator it(edsPath, QStringList("*.PIC"), QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    int fileCount = 0;
    while (it.hasNext())
    {
        const QString &fileName = it.next();
        QFileInfo fileInfo(fileName);
        if (picFileRegExp.match(fileInfo.fileName()).hasMatch())
        {
            fileList << fileName;
        }
        fileCount++;
    }
    qDebug() << fileList.count() << "files matches on" << fileCount << "files.";

    QMultiMap<QString, QString> adbuffCpu;
    QMultiMap<QString, QString> cpuAadbuff;

    QRegularExpression sfrRegExp(sfrFilter);
    int fi = 0;
    for (const QString &fileName : fileList)
    {
        QFileInfo fileInfo(fileName);
        QStringList sfrList;
        qDebug() << ++fi << "/" << fileList.count() << fileInfo.fileName();
        EDCParser parser(fileName);
        for (const EDCSFRDef &sfr : parser.sfrs())
        {
            if (sfrRegExp.match(sfr.name).hasMatch())
            {
                sfrList << sfr.name;
            }
        }

        for (int i = 0; i < 64; i++)
        {
            QString adBuff = sfrFilter;
            adBuff.replace(QRegularExpression("\\(.*\\)"), QString::number(i));
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

    CWritter cwriter(outputFileName);

    // count / max
    QMultiMap<uint, QString> buffCount;
    QMultiMap<uint, QString> buffMax;
    for (const QString &cpu : cpuAadbuff.uniqueKeys())
    {
        QStringList adBuff = cpuAadbuff.values(cpu);
        QCollator coll;
        coll.setNumericMode(true);
        std::sort(adBuff.begin(), adBuff.end(), [&](const QString &s1, const QString &s2) { return coll.compare(s1, s2) < 0; });

        QRegularExpressionMatch match = sfrRegExp.match(adBuff.last());
        int max = match.captured(1).toInt() + 1;
        int count = adBuff.count();
        buffCount.insert(count, cpu);
        buffMax.insert(max, cpu);
    }
    for (uint count : buffCount.uniqueKeys())
    {
        cwriter.writeIfDefList(buffCount.values(count));

        QStringList defines, values;
        defines << deviceName + "_COUNT";
        values << QString::number(count);
        cwriter.writeDefList(defines, values);
    }
    if (!buffCount.uniqueKeys().isEmpty())
    {
        cwriter.writeIfDefListEnd();
        cwriter << "\n";
    }

    for (uint max : buffMax.uniqueKeys())
    {
        cwriter.writeIfDefList(buffMax.values(max));

        QStringList defines, values;
        defines << deviceName + "_CHANNEL_MAX";
        values << QString::number(max);
        cwriter.writeDefList(defines, values);
    }
    if (!buffMax.uniqueKeys().isEmpty())
    {
        cwriter.writeIfDefListEnd();
        cwriter << "\n";
    }

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
            QRegularExpressionMatch match = sfrRegExp.match(def);
            int idDef = match.captured(1).toInt();
            defines << QString("%1_HAVE_CH%2").arg(deviceName).arg(idDef);
        }
        cwriter.writeDefList(defines);
        cwriter.writeIfDefListEnd();
    }

    return 0;
}
