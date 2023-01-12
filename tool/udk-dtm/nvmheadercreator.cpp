#include "nvmheadercreator.h"

#include <QDebug>
#include <QMultiMap>
#include <QPair>
#include <QRegularExpression>

NvmHeaderCreator::NvmHeaderCreator(const EdcDb &db, const QString &picFilter, const QString &fileName)
    : HeaderCreator(db, picFilter, fileName)
{
    QMultiMap<QString, QString> programMemBeginMap;
    QMultiMap<QString, QString> programMemEndMap;
    QMultiMap<QString, QString> programSize;

    QRegularExpression picFileRegExp(picFilter);
    for (EDCParser *parser : db.parsers())
    {
        if (!picFileRegExp.match(parser->cpuName()).hasMatch())
        {
            continue;
        }

        double coef = 1;
        QString flashSector = "CODE";
        if (parser->programSpaces().constFind(flashSector) == parser->programSpaces().constEnd())
        {
            flashSector = "PROGRAM";
            coef = 3.0 / 2.0;
        }
        const EDCProgramSpace &flashSpace = parser->programSpaces()[flashSector];
        programMemBeginMap.insert(hexVal(flashSpace.beginaddr, 6), parser->deviceName());
        programMemEndMap.insert(hexVal(flashSpace.endaddr, 6), parser->deviceName());
        programSize.insert(QString::number((flashSpace.endaddr - flashSpace.beginaddr) * coef, 'f', 0), parser->deviceName());
    }

    *this << "// NVM_PROGRAM_BEGIN"
          << "\n";
    writeSwitchDefineValue(programMemBeginMap, "NVM_PROGRAM_BEGIN");

    *this << "\n";
    *this << "// NVM_PROGRAM_END"
          << "\n";
    writeSwitchDefineValue(programMemEndMap, "NVM_PROGRAM_END");

    *this << "\n";
    *this << "// NVM_PROGRAM_SIZE"
          << "\n";
    writeSwitchDefineValue(programSize, "NVM_PROGRAM_SIZE");
}
