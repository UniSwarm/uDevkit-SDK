#include "cwritter.h"

#include <QCollator>
#include <QProcess>

CWritter::CWritter(const QString &fileName)
{
    _file = new QFile(fileName);
    _file->open(QIODevice::WriteOnly);
    _stream = new QTextStream(_file);

    _ifDefState = StateIfDefNotStarted;
}

CWritter::~CWritter()
{
    close();
}

void CWritter::close()
{
    _file->close();
    QProcess p;
    p.start("clang-format", QStringList() << "-i" << _file->fileName());
    p.waitForFinished(500);
}

void CWritter::writeIfDefList(const QStringList &listDef)
{
    QStringList listDefSorted = listDef;
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(listDefSorted.begin(), listDefSorted.end(), [&](const QString &s1, const QString &s2) {
        return coll.compare(s1, s2) < 0;
    });

    if (_ifDefState == StateIfDefNotStarted)
    {
        _ifDefState = StateIfDefFirst;
        *_stream << "#if ";
    }
    else
    {
        *_stream << "#elif ";
    }

    int i = 0;
    for (const QString &def : listDefSorted)
    {
        i++;
        *_stream << "defined(" << def << ")";
        if (i < listDefSorted.count())
        {
            if (i % 4 == 0)
            {
                *_stream << " \\\n";
            }
            *_stream << " || ";
        }
    }
    *_stream << "\n";
}

void CWritter::writeIfDefElse()
{
    *_stream << "#else\n";
    _ifDefState = StateIfDefElse;
}

void CWritter::writeIfDefListEnd()
{
    *_stream << "#endif\n";
    _ifDefState = StateIfDefNotStarted;
}

void CWritter::writeDefList(const QStringList &listDef, const QStringList &values)
{
    int i = 0;
    for (const QString &def : listDef)
    {
        *_stream << " #define " << def;
        if (i < values.count())
        {
            *_stream << " " << values[i];
        }
        *_stream << "\n";
        i++;
    }
}

QTextStream &CWritter::operator<<(const QString &s)
{
    *_stream << s;
    return *_stream;
}

QString CWritter::hex(int64_t n, int bits)
{
    return "0x" + QString::number(n, 16).toUpper().rightJustified(bits / 4, '0') + "L";
}

QString CWritter::hex(uint64_t n, int bits)
{
    return "0x" + QString::number(n, 16).toUpper().rightJustified(bits / 4, '0') + "LU";
}
