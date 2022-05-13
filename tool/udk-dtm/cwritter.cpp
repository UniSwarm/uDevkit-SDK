#include "cwritter.h"

#include <QCollator>

CWritter::CWritter(const QString &fileName)
{
    _file = new QFile(fileName);
    _file->open(QIODevice::WriteOnly);
    _stream = new QTextStream(_file);

    _ifDefState = StateIfDefNotStarted;
}

CWritter::~CWritter()
{
    _file->close();
}

void CWritter::writeIfDefList(const QStringList &listDef)
{
    int i = 0;

    QStringList listDefSorted = listDef;
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(listDefSorted.begin(),
              listDefSorted.end(),
              [&](const QString &s1, const QString &s2)
              {
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
    for (const QString &def : listDefSorted)
    {
        i++;
        *_stream << "defined(" << def << ")";
        if (i < listDefSorted.count())
        {
            if (i % 3 == 0)
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
    QCollator coll;
    coll.setNumericMode(true);

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
