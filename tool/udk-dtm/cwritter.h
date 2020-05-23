#ifndef CWRITTER_H
#define CWRITTER_H

#include <QFile>
#include <QString>
#include <QTextStream>

class CWritter
{
public:
    CWritter(const QString &path);
    ~CWritter();

    void writeIfDefList(const QStringList &listDef);
    void writeIfDefListEnd();

    void writeDefList(const QStringList &listDef, const QStringList &values = QStringList());

    QTextStream &operator<<(const QString &s);

protected:
    QFile *_file;
    QTextStream *_stream;

    enum StateIfDef
    {
        StateIfDefNotStarted,
        StateIfDefFirst,
        StateIfDefMany
    };
    StateIfDef _ifDefState;
};

#endif // CWRITTER_H
