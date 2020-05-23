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

class EDCParser
{
public:
    EDCParser(const QString &path);

    QList<EDCSFRDef> sfrs() const;

    QString name() const;

protected:
    bool parseDocument();
    bool parsePic();
    bool parseSFRDef();

    QFile *_xmlFile;
    QXmlStreamReader *_xml;

    QString _name;
    QList<EDCSFRDef> _sfrs;
};

#endif // EDCPARSER_H
