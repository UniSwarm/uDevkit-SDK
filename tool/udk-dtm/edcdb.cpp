#include "edcdb.h"

#include <QDebug>
#include <QDirIterator>
#include <QRegularExpression>

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

void EdcDb::loadDb(const QStringList &fileList)
{
    for (const QString &fileName : fileList)
    {
        QFileInfo fileInfo(fileName);
        _parsers.append(new EDCParser(fileName));
    }

    QFuture<void> thumbnails = QtConcurrent::map(_parsers, loadOne);
    thumbnails.waitForFinished();

    _parsersMap.clear();
    for (EDCParser *parser : _parsers)
    {
        _parsersMap.insert(parser->cpuName(), parser);
    }
}

EDCParser *EdcDb::parser(const QString &cpuName)
{
    return _parsersMap.value(cpuName);
}

const QList<EDCParser *> &EdcDb::parsers() const
{
    return _parsers;
}
