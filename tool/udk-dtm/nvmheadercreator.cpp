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

    QRegularExpression picFileRegExp(picFilter);
    for (EDCParser *parser : db.parsers())
    {
        if (!picFileRegExp.match(parser->cpuName()).hasMatch())
        {
            continue;
        }

        const EDCProgramSpace &flashSpace = parser->programSpaces()["PROGRAM"];
        programMemBeginMap.insert(hexVal(flashSpace.beginaddr, 6), parser->deviceName());
        programMemEndMap.insert(hexVal(flashSpace.endaddr, 6), parser->deviceName());
    }

    *this << "// NVM_PROGRAM_BEGIN"
          << "\n";
    writeSwitchDefineValue(programMemBeginMap, "NVM_PROGRAM_BEGIN");

    *this << "\n";
    *this << "// NVM_PROGRAM_END"
          << "\n";
    writeSwitchDefineValue(programMemEndMap, "NVM_PROGRAM_END");
}
