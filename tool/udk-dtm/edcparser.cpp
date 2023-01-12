#include "edcparser.h"

#include <QCollator>
#include <QDebug>
#include <utility>

EDCParser::EDCParser(QString path)
    : _filePath(std::move(path))
{
    _xml = nullptr;
}

bool EDCParser::parse()
{
    QFile xmlFile(_filePath);
    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    _xml = new QXmlStreamReader(&xmlFile);
    bool ok = parseDocument();

    xmlFile.close();

    return ok;
}

bool EDCParser::parseDocument()
{
    while (_xml->readNextStartElement())
    {
        if (_xml->name() == QStringLiteral("PIC"))
        {
            parsePic();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }

    QCollator coll;
    coll.setNumericMode(true);
    std::sort(_sfrs.begin(), _sfrs.end(), [&](const EDCSFRDef &sfr1, const EDCSFRDef &sfr2) {
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

    while (_xml->readNextStartElement())
    {
        // qDebug() << _xml->name();
        if (_xml->name() == QStringLiteral("DataSpace") || _xml->name() == QStringLiteral("PhysicalSpace"))
        {
            parseDataSpace();
        }
        else if (_xml->name() == QStringLiteral("ProgramSpace"))
        {
            parseProgramSpace();
        }
        else if (_xml->name().endsWith(QStringLiteral("Sector")))
        {
            parseProgramSector();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }
    return true;
}

bool EDCParser::parseDataSpace()
{
    while (_xml->readNextStartElement())
    {
        // qDebug() << "+ " << _xml->name();
        if (_xml->name().endsWith(QStringLiteral("SFRDef")))
        {
            parseSFRDef();
        }
        else if (_xml->name() == QStringLiteral("RegardlessOfMode") || _xml->name() == QStringLiteral("SFRDataSector"))
        {
            parseDataSpace();
        }
        else if (_xml->name().endsWith(QStringLiteral("Sector")))
        {
            parseProgramSector();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }
    return true;
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
    sfrDef.impl = _xml->attributes().value("edc:impl").toUInt(&ok, 0);

    while (_xml->readNextStartElement())
    {
        if (_xml->name() == QStringLiteral("SFRMode"))
        {
            parseSFRMode(sfrDef);
        }
        else if (_xml->name() == QStringLiteral("SFRModeList"))
        {
            continue;
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }
    _sfrs.append(sfrDef);

    _xml->skipCurrentElement();
    return true;
}

bool EDCParser::parseProgramSpace()
{
    while (_xml->readNextStartElement())
    {
        if (_xml->name() == QStringLiteral("ProgramSubspace"))
        {
            parseProgramSubSpace();
        }
        else if (_xml->name().endsWith(QStringLiteral("Sector")))
        {
            parseProgramSector();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }
    return true;
}

bool EDCParser::parseProgramSubSpace()
{
    QString partitionmode = _xml->attributes().value("edc:partitionmode").toString();
    // qDebug() << partitionmode;
    if (partitionmode.isEmpty() || partitionmode != "single")
    {
        _xml->skipCurrentElement();
        return true;
    }

    while (_xml->readNextStartElement())
    {
        if (_xml->name().endsWith(QStringLiteral("Sector")))
        {
            parseProgramSector();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }

    return true;
}

bool EDCParser::parseProgramSector()
{
    bool ok;
    EDCProgramSpace programSpace;
    programSpace.name = _xml->attributes().value("edc:regionid").toString().toUpper();
    programSpace.beginaddr = _xml->attributes().value("edc:beginaddr").toUInt(&ok, 0);
    programSpace.endaddr = _xml->attributes().value("edc:endaddr").toUInt(&ok, 0) - 1;
    // qDebug() << "programSpace" << programSpace.name << programSpace.beginaddr;
    _programSpaces.insert(programSpace.name, programSpace);
    _xml->skipCurrentElement();
    return true;
}

const QMap<QString, EDCProgramSpace> &EDCParser::programSpaces() const
{
    return _programSpaces;
}

bool EDCParser::parseSFRMode(EDCSFRDef &sfrDef)
{
    bool ok;
    int bitAddr = 0;
    while (_xml->readNextStartElement())
    {
        if (_xml->name().endsWith(QStringLiteral("AdjustPoint")))
        {
            bitAddr += _xml->attributes().value("edc:offset").toUInt(&ok, 0);
            _xml->skipCurrentElement();
        }
        else if (_xml->name().endsWith(QStringLiteral("SFRFieldDef")))
        {
            EDCSFRFieldDef field;
            field.name = _xml->attributes().value("edc:cname").toString();
            field.adrr = bitAddr;
            field.size = _xml->attributes().value("edc:nzwidth").toUInt(&ok, 0);
            sfrDef.fields.append(field);
            bitAddr += field.size;
            _xml->skipCurrentElement();
        }
        else
        {
            _xml->skipCurrentElement();
        }
    }

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
