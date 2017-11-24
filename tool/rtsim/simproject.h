#ifndef SIMPROJECT_H
#define SIMPROJECT_H

#include <QDir>
#include <QObject>
#include <QProcess>

class SimProject : public QObject
{
    Q_OBJECT
public:
    explicit SimProject(QObject *parent = nullptr);
    ~SimProject();

    QString exePath() const;
    bool setExePath(const QString &exePath);

    bool isValid() const;
    enum {
        Running,
        Stopped
    } Status;

signals:

public slots:
    void start();

protected:
    QString _exePath;
    QDir _path;
    QProcess *_process;
    bool _valid;
};

#endif // SIMPROJECT_H
