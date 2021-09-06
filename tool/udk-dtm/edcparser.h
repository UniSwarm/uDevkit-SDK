#ifndef EDCPARSER_H
#define EDCPARSER_H

#include <QString>
#include <QFile>
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

    QList<EDCSFRDef> sfrs() const;

    QString name() const;

    const QList<EDCProgramSpace> &programSpace() const;

  protected:
    bool parseDocument();
    bool parsePic();
    bool parseSFRDef();
    bool parseProgramSpace();

    QFile *_xmlFile;
    QXmlStreamReader *_xml;

    QString _name;
    QList<EDCSFRDef> _sfrs;

    QList<EDCProgramSpace> _programSpace;
};

#endif // EDCPARSER_H
