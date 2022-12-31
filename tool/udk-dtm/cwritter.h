#ifndef CWRITTER_H
#define CWRITTER_H

#include <QFile>
#include <QString>
#include <QTextStream>

class CWritter
{
public:
    CWritter(const QString &fileName);
    ~CWritter();

    void close();

    void writeIfDefList(const QStringList &listDef);
    void writeIfDefElse();
    void writeIfDefListEnd();

    void writeDefList(const QStringList &listDef, const QStringList &values = QStringList());

    QTextStream &operator<<(const QString &s);

    QString hex(int64_t n, int bits = 0);
    QString hex(uint64_t n, int bits = 0);

protected:
    QFile *_file;
    QTextStream *_stream;

    enum StateIfDef
    {
        StateIfDefNotStarted,
        StateIfDefFirst,
        StateIfDefMany,
        StateIfDefElse
    };
    StateIfDef _ifDefState;
};

#endif  // CWRITTER_H
