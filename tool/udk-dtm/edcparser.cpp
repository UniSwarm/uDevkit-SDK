#include "edcparser.h"

#include <QCollator>
#include <QDebug>

EDCParser::EDCParser(const QString &path)
    : _filePath(path)
{
    _level = 1;
}

bool EDCParser::parse(void)
{
    _xmlFile = new QFile(_filePath);
    if (!_xmlFile->open(QIODevice::ReadOnly))
    {
        return false;
    }

    _xml = new QXmlStreamReader(_xmlFile);
    bool ok = parseDocument();

    _xmlFile->close();

    return ok;
}

bool EDCParser::parseDocument(void)
{
    while (!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->isStartElement())
        {
            if (_xml->name() == "PIC")
            {
                if (!parsePic())
                {
                    return false;
                }
            }
        }
    }

    QCollator coll;
    coll.setNumericMode(true);
    std::sort(_sfrs.begin(), _sfrs.end(), [&](const EDCSFRDef &s1, const EDCSFRDef &s2)
              {
                  return coll.compare(s1.name, s2.name) < 0;
              });

    return true;
}

bool EDCParser::parsePic(void)
{
    _cpuName = _xml->attributes().value("edc:name").toString();

    _deviceName = _cpuName;
    _deviceName.replace("DSPIC", "DEVICE_");
    _deviceName.replace("PIC", "DEVICE_");

    while (!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->isStartElement())
        {
            _level++;
            if (_xml->name() == "SFRDef")
            {
                if (!parseSFRDef())
                {
                    return false;
                }
            }
            if (_xml->name() == "ProgramSubspace")
            {
                if (!parseProgramSpace())
                {
                    return false;
                }
            }
        }
        if (_xml->tokenType() == QXmlStreamReader::EndElement)
        {
            _level--;
            if (_xml->name() == "PIC" && _level == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool EDCParser::parseSFRDef(void)
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

    _xml->readNext();

    if (_xml->isStartElement())
    {
        _level++;
        if (_xml->name() == "SFRMode")
        {
            if (!parseSFRMode())
            {
                return false;
            }
        }
    }
    if (_xml->tokenType() == QXmlStreamReader::EndElement)
    {
        _level--;
        if (_xml->name() == "SFRModeList")
        {
            return true;
        }
    }

    _xml->skipCurrentElement();
    _sfrs.append(sfrDef);
    return true;
}

bool EDCParser::parseProgramSpace(void)
{
    EDCProgramSpace programSpace;
    programSpace.name = _xml->attributes().value("edc:partitionmode").toString();

    if (programSpace.name.isEmpty() )
    {
        _xml->skipCurrentElement();
        return false;
    }

    if (programSpace.name != "single")
    {
        _xml->skipCurrentElement();
        return false;
    }
    bool ok;
    QString name("ACTIVE_PARTION");
    programSpace.name = name;
    programSpace.beginaddr = _xml->attributes().value("edc:beginaddr").mid(2).toUInt(&ok, 16);
    programSpace.endaddr = _xml->attributes().value("edc:endaddr").mid(2).toUInt(&ok, 16);
    _programSpace.append(programSpace);

    while(!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->isStartElement())
        {
            programSpace.name = _xml->attributes().value("edc:regionid").toString().toUpper();
            if (programSpace.name.isEmpty())
            {
                _xml->skipCurrentElement();
                return false;
            }
            programSpace.name.prepend(name + "_");
            programSpace.beginaddr = _xml->attributes().value("edc:beginaddr").mid(2).toUInt(&ok, 16);
            programSpace.endaddr = _xml->attributes().value("edc:endaddr").mid(2).toUInt(&ok, 16);
            _programSpace.append(programSpace);
        }
    }

    _xml->skipCurrentElement();
    _programSpace.append(programSpace);
    return true;
}

const QList<EDCProgramSpace> &EDCParser::programSpace(void) const
{
    return _programSpace;
}

bool EDCParser::parseSFRMode(void)
{
    return true;
}

const QString &EDCParser::cpuName(void) const
{
    return _cpuName;
}

const QString &EDCParser::deviceName(void) const
{
    return _deviceName;
}

const QList<EDCSFRDef> &EDCParser::sfrs(void) const
{
    return _sfrs;
}
