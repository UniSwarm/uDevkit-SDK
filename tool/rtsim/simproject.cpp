#include "simproject.h"

#include <QFileInfo>
#include <QDebug>

SimProject::SimProject(QObject *parent)
    : QObject(parent)
{
    _process = new QProcess();
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
