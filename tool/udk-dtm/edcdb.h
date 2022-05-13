#ifndef EDCDB_H
#define EDCDB_H

#include <QList>
#include <QMap>

#include "edcparser.h"

class EdcDb
{
public:
    EdcDb();
    ~EdcDb();

    void loadDb(const QStringList &fileList);

    EDCParser *parser(const QString &cpuName);
    [[nodiscard]] const QList<EDCParser *> &parsers() const;

private:
    QList<EDCParser *> _parsers;
    QMap<QString, EDCParser *> _parsersMap;
};

#endif  // EDCDB_H
