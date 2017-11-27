#ifndef SIMPROJECT_H
#define SIMPROJECT_H

#include <QDir>
#include <QObject>
#include <QProcess>

#include "simclient.h"

class SimProject : public QObject
{
    Q_OBJECT
public:
    explicit SimProject(QObject *parent = nullptr);
    ~SimProject();

    QString exePath() const;
    bool setExePath(const QString &exePath);

    bool isValid() const;
    enum Status {
        Invalid,
        Stopped,
        Running
    };
    Status status() const;

    SimClient *client() const;
    void setClient(SimClient *client);

signals:
    void logAppended(QString log);

public slots:
    void start();

protected slots:
    void readProcess();

protected:
    QString _exePath;
    QDir _path;
    QProcess *_process;
    bool _valid;

    SimClient *_client;
};

#endif // SIMPROJECT_H
