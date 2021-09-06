#ifndef EDCDB_H
#define EDCDB_H

#include "edcparser.h"

class EdcDb
{
public:
    EdcDb();
    ~EdcDb();

    void loadDb();

    const QList<EDCParser *> &parsers() const;

private:
    QList<EDCParser *> _parsers;
};

#endif // EDCDB_H
