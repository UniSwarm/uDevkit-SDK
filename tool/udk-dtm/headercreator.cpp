#include "headercreator.h"

#include <QCollator>
#include <QDebug>
#include <utility>

HeaderCreator::HeaderCreator(const EdcDb &db, QString picFilter, const QString &fileName)
    : CWritter(fileName),
      _db(db),
      _picFilter(std::move(picFilter))
{
}

HeaderCreator::~HeaderCreator()
{
}

void HeaderCreator::writeSwitchDefineValue(const QMultiMap<QString, QString> &mapValueCPU, const QString &defineName)
{
    auto keys = mapValueCPU.uniqueKeys();

    bool ok;
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(keys.begin(), keys.end(), [&](const QString &s1, const QString &s2) {
        if (s1.startsWith("0x") && s2.startsWith("0x"))
        {
            return s1.toInt(&ok, 16) < s2.toInt(&ok, 16);
        }

        return coll.compare(s1, s2) < 0;
    });

    for (const auto &key : qAsConst(keys))
    {
        writeIfDefList(mapValueCPU.values(key));

        QStringList defines;
        QStringList values;
        defines << defineName;
        values << key;
        writeDefList(defines, values);
    }
    writeIfDefListEnd();
}

QString HeaderCreator::hexVal(int val, uint width)
{
    return "0x" + QString::number(val, 16).rightJustified(width, '0').toUpper();
}
