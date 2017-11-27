#include "simproject.h"

#include <QFileInfo>
#include <QDebug>

SimProject::SimProject(QObject *parent)
    : QObject(parent)
{
    _process = new QProcess();
    connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readProcess()));
    connect(_process, SIGNAL(readyReadStandardError()), this, SLOT(readProcess()));
    _valid = false;
}

SimProject::~SimProject()
{
    if (_process->state() == QProcess::Running)
        _process->kill();
}

QString SimProject::exePath() const
{
    return _exePath;
}

bool SimProject::setExePath(const QString &exePath)
{
    QFileInfo file(exePath);
    if (!file.exists())
        return false;

    _exePath = exePath;
    _path = file.absoluteDir();
    _process->setWorkingDirectory(_path.path());
    _process->setProgram(file.absoluteFilePath());

    _valid = true;
    return true;
}

bool SimProject::isValid() const
{
    return _valid;
}

SimProject::Status SimProject::status() const
{
    if (!_valid)
        return Invalid;
    if (_process->state() == QProcess::Running)
        return Running;
    else
        return Stopped;
}

void SimProject::start()
{
    if (!_valid)
        return;

    _process->start();
    _process->waitForStarted(200);
    if (_process->state() != QProcess::Running)
    {
        qDebug()<<_process->errorString()<<_process->program();
        return;
    }
}

void SimProject::readProcess()
{
    QString log;

    QString error = _process->readAllStandardError();
    if (!error.isEmpty())
        log.append("<span color='red'>" + error + "</span>");

    QString out = _process->readAllStandardOutput();
    if (!out.isEmpty())
        log.append(out);

    log.replace('\n', "<br></br>");
    log.replace('\r', "");
    emit logAppended(log);
}

SimClient *SimProject::client() const
{
    return _client;
}

void SimProject::setClient(SimClient *client)
{
    _client = client;
}
