#ifndef EDCPARSER_H
#define EDCPARSER_H

#include <QFile>
#include <QList>
#include <QMap>
#include <QString>
#include <QXmlStreamReader>

struct EDCSFRDef
{
    QString name;
    uint adrr;
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
    EDCParser(const QString &path);

    bool parse();

    const QString &cpuName() const;
    const QString &deviceName() const;

    const QList<EDCSFRDef> &sfrs() const;
    const QMap<QString, EDCProgramSpace> &programSpaces() const;

protected:
    bool parseDocument();
    bool parsePic();
    bool parseSFRDef();
    bool parseProgramSubSpace();
    bool parseProgramSector();
    bool parseSFRMode();

    QString _filePath;
    QXmlStreamReader *_xml;

    QString _cpuName;
    QString _deviceName;
    QList<EDCSFRDef> _sfrs;
    QMap<QString, EDCProgramSpace> _programSpaces;

    int _level;
};

#endif  // EDCPARSER_H
