#include "edcdb.h"

#include <QDirIterator>
#include <QRegularExpression>
#include <QDebug>

#include <QtConcurrent>

EdcDb::EdcDb()
{

}

EdcDb::~EdcDb()
{
    qDeleteAll(_parsers);
}

void loadOne(EDCParser *parser)
{
    parser->parse();
}

void EdcDb::loadDb()
{
#ifdef WIN32
    QString edsPath = "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/";
#else
    QString edsPath = "/opt/microchip/mplabx/v5.50/packs/Microchip/";
#endif
    QString picFilter = "^(DS)?PIC(30|33|24|32)";
    QStringList excludeDeviceList("PIC32MZ1025W104132");

    QStringList fileList;
    QRegularExpression picFileRegExp(picFilter);
    QDirIterator it(edsPath, QStringList("*.PIC"), QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    int fileCount = 0;
    while (it.hasNext())
    {
        const QString &fileName = it.next();
        QFileInfo fileInfo(fileName);
        fileCount++;

        if (excludeDeviceList.contains(fileInfo.baseName()))
        {
            continue;
        }
        if (picFileRegExp.match(fileInfo.fileName()).hasMatch())
        {
            fileList << fileName;
        }
    }
    qDebug() << fileList.count() << "files matches on" << fileCount << "files.";

    int fi = 0;
    for (const QString &fileName : fileList)
    {
        QFileInfo fileInfo(fileName);
        qDebug() << ++fi << "/" << fileList.count() << fileInfo.fileName();
        _parsers.append(new EDCParser(fileName));
    }

    QFuture<void> thumbnails = QtConcurrent::map(_parsers, loadOne);
    thumbnails.waitForFinished();
}

const QList<EDCParser *> &EdcDb::parsers() const
{
    return _parsers;
}
