#ifndef EDCPARSER_H
#define EDCPARSER_H

#include <QFile>
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

    bool parse(void);

    const QList<EDCSFRDef> &sfrs(void) const;

    const QString &cpuName(void) const;
    const QString &deviceName(void) const;

    const QList<EDCProgramSpace> &programSpace(void) const;

protected:
    bool parseDocument(void);
    bool parsePic(void);
    bool parseSFRDef(void);
    bool parseProgramSpace(void);
    bool parseSFRMode(void);

    QString _filePath;
    QFile *_xmlFile;
    QXmlStreamReader *_xml;

    QString _cpuName;
    QString _deviceName;
    QList<EDCSFRDef> _sfrs;

    QList<EDCProgramSpace> _programSpace;

    int _level;
};

#endif // EDCPARSER_H
