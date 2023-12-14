/**
 ** This file is part of the UDK-SDK project.
 ** Copyright 2019 UniSwarm sebastien.caux@uniswarm.eu
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/

#include "simproject.h"

#include <QDebug>
#include <QFileInfo>

SimProject::SimProject(QObject *parent)
    : QObject(parent)
{
    _process = new QProcess();
    connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readProcess()));
    connect(_process, SIGNAL(readyReadStandardError()), this, SLOT(readProcess()));
    connect(_process, SIGNAL(channelReadyRead(int)), this, SLOT(readProcess()));
    connect(_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finish(int, QProcess::ExitStatus)));
    _valid = false;
}

SimProject::~SimProject()
{
    if (_process->state() == QProcess::Running)
    {
        _process->kill();
    }
}

QString SimProject::exePath() const
{
    return _exePath;
}

bool SimProject::setExePath(const QString &exePath, const QStringList &args)
{
    QFileInfo file(exePath);
    if (!file.exists())
    {
        return false;
    }

    _exePath = exePath;
    _path = file.absoluteDir();
    _process->setWorkingDirectory(_path.path());
    _process->setProgram(file.absoluteFilePath());
    _process->setArguments(args);

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
    {
        return Invalid;
    }
    if (_process->state() == QProcess::Running)
    {
        return Running;
    }
    return Stopped;
}

void SimProject::start()
{
    if (!_valid)
    {
        return;
    }

    _process->start(QProcess::Unbuffered | QProcess::ReadWrite);
    _process->waitForStarted(200);
    if (_process->state() != QProcess::Running)
    {
        qDebug() << _process->errorString() << _process->program();
        return;
    }
}

void SimProject::readProcess()
{
    QString log;

    QString error = _process->readAllStandardError();
    if (!error.isEmpty())
    {
        log.append("<span color='red'>" + error + "</span>");
    }

    QString out = _process->readAllStandardOutput();
    if (!out.isEmpty())
    {
        log.append(out);
    }

    log.replace('\n', "<br></br>");
    log.replace('\r', "");
    emit logAppended(log);
}

void SimProject::finish(int exitCode, QProcess::ExitStatus exitStatus)
{
    readProcess();
    QString log;
    if (exitStatus == QProcess::CrashExit)
    {
        log.append(QString("<span color='red'>Process crashed with error code %1</span>").arg(exitCode));
    }
    else
    {
        log.append(QString("<span color='0xFF0000'>Process finished with exitCode code %1</span>").arg(exitCode));
    }
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
