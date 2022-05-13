#include "edcparser.h"

#include <QCollator>
#include <QDebug>

EDCParser::EDCParser(const QString &path)
    : _filePath(path)
{
    _level = 1;
    _xml = nullptr;
}

bool EDCParser::parse()
{
    QFile xmlFile(_filePath);
    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    _level = 1;
    _xml = new QXmlStreamReader(&xmlFile);
    bool ok = parseDocument();

    xmlFile.close();

    return ok;
}

bool EDCParser::parseDocument()
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
    std::sort(_sfrs.begin(),
              _sfrs.end(),
              [&](const EDCSFRDef &sfr1, const EDCSFRDef &sfr2)
              {
                  return coll.compare(sfr1.name, sfr2.name) < 0;
              });

    return true;
}

bool EDCParser::parsePic()
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
                if (!parseProgramSubSpace())
                {
                    return false;
                }
            }
            if (_xml->name().endsWith("Sector"))
            {
                if (!parseProgramSector())
                {
                    return false;
                }
            }
        }
        if (_xml->isEndElement())
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
    sfrDef.adrr = _xml->attributes().value("edc:_addr").toUInt(&ok, 0);

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
    if (_xml->isEndElement())
    {
        _level--;
        if (_xml->name() == "SFRModeList")
        {
            return true;
        }
    }
    _sfrs.append(sfrDef);

    _xml->skipCurrentElement();
    return true;
}

bool EDCParser::parseProgramSubSpace()
{
    QString partitionmode = _xml->attributes().value("edc:partitionmode").toString();
    if (partitionmode.isEmpty() || partitionmode != "single")
    {
        _xml->skipCurrentElement();
        return true;
    }

    while (!_xml->atEnd())
    {
        _xml->readNext();

        if (_xml->isStartElement())
        {
            _level++;
            if (_xml->name().endsWith("Sector"))
            {
                if (!parseProgramSector())
                {
                    return false;
                }
            }
        }
        if (_xml->isEndElement())
        {
            _level--;
            if (_xml->name() == "ProgramSubspace")
            {
                return true;
            }
        }
    }

    return false;
}

bool EDCParser::parseProgramSector()
{
    bool ok;
    EDCProgramSpace programSpace;
    programSpace.name = _xml->attributes().value("edc:regionid").toString().toUpper();
    programSpace.beginaddr = _xml->attributes().value("edc:beginaddr").toUInt(&ok, 0);
    programSpace.endaddr = _xml->attributes().value("edc:endaddr").toUInt(&ok, 0);
    _programSpaces.insert(programSpace.name, programSpace);
    return true;
}

const QMap<QString, EDCProgramSpace> &EDCParser::programSpaces() const
{
    return _programSpaces;
}

bool EDCParser::parseSFRMode()
{
    return true;
}

const QString &EDCParser::cpuName() const
{
    return _cpuName;
}

const QString &EDCParser::deviceName() const
{
    return _deviceName;
}

const QList<EDCSFRDef> &EDCParser::sfrs() const
{
    return _sfrs;
}
