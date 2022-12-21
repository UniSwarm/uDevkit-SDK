#ifndef EDCPARSER_H
#define EDCPARSER_H

#include <QFile>
#include <QList>
#include <QMap>
#include <QString>
#include <QXmlStreamReader>

struct EDCSFRFieldDef
{
    QString name;
    uint adrr;
    uint size;
};

struct EDCSFRDef
{
    QString name;
    uint adrr;
    uint impl;
    QList<EDCSFRFieldDef> fields;
};

struct EDCProgramSpace
{
    QString name;
    uint beginaddr;
    uint endaddr;
};

class EDCParser
{
public:
    EDCParser(QString path);

    bool parse();

    const QString &cpuName() const;
    const QString &deviceName() const;

    const QList<EDCSFRDef> &sfrs() const;
    const QMap<QString, EDCProgramSpace> &programSpaces() const;

protected:
    bool parseDocument();
    bool parsePic();
    bool parseDataSpace();
    bool parseSFRDef();
    bool parseProgramSubSpace();
    bool parseProgramSector();
    bool parseSFRMode(EDCSFRDef &sfrDef);

    QString _filePath;
    QXmlStreamReader *_xml;

    QString _cpuName;
    QString _deviceName;
    QList<EDCSFRDef> _sfrs;
    QMap<QString, EDCProgramSpace> _programSpaces;
};

#endif  // EDCPARSER_H
