#ifndef HEADERCREATOR_H
#define HEADERCREATOR_H

#include "cwritter.h"
#include "edcdb.h"

class HeaderCreator
{
public:
    HeaderCreator(const EdcDb &db, QString picFilter, const QString &fileName);
    ~HeaderCreator();

protected:
    const EdcDb &_db;
    QString _picFilter;
    CWritter *_cWritter;

    void writeSwitchDefineValue(const QMultiMap<QString, QString> &mapValueCPU, const QString &defineName);

    QString hexVal(int val, uint width = 0);
};

#endif  // HEADERCREATOR_H
