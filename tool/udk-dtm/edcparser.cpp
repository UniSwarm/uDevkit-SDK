#include "edcparser.h"

#include <QCollator>
#include <QDebug>

EDCParser::EDCParser(const QString &path)
{
    _xmlFile = new QFile(path);
    _xmlFile->open(QIODevice::ReadOnly);

    _xml = new QXmlStreamReader(_xmlFile);
    parseDocument();

    _xmlFile->close();
}

bool EDCParser::parseDocument()
{
    while (!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->tokenType() == QXmlStreamReader::StartElement)
        {
            if (_xml->name() == "PIC")
            {
                parsePic();
            }
        }
    }

    QCollator coll;
    coll.setNumericMode(true);
    std::sort(_sfrs.begin(), _sfrs.end(), [&](const EDCSFRDef& s1, const EDCSFRDef& s2){ return coll.compare(s1.name, s2.name) < 0; });

    return false;
}

bool EDCParser::parsePic()
{
    _name = _xml->attributes().value("edc:name").toString();

    int level = 1;
    while (!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->tokenType() == QXmlStreamReader::StartElement)
        {
            level++;
            if (_xml->name() == "SFRDef")
            {
                parseSFRDef();
            }
        }
        if (_xml->tokenType() == QXmlStreamReader::EndElement)
        {
            level--;
            if (_xml->name() == "PIC" && level == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool EDCParser::parseSFRDef()
{
    EDCSFRDef sfrDef;
    sfrDef.name = _xml->attributes().value("edc:cname").toString();

    if (sfrDef.name.isEmpty())
    {
        _xml->skipCurrentElement();
        return false;
    }

    bool ok;
    sfrDef.adrr = _xml->attributes().value("edc:_addr").mid(2).toUInt(&ok, 16);

    _xml->skipCurrentElement();
    _sfrs.append(sfrDef);
    return true;
}

QString EDCParser::name() const
{
    return _name;
}

QList<EDCSFRDef> EDCParser::sfrs() const
{
    return _sfrs;
}
