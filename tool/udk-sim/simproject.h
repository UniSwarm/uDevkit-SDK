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
    ~SimProject() override;

    QString exePath() const;
    bool setExePath(const QString &exePath, const QStringList &args);

    bool isValid() const;
    enum Status
    {
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
    void finish(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    QString _exePath;
    QDir _path;
    QProcess *_process;
    bool _valid;

    SimClient *_client;
};

#endif  // SIMPROJECT_H
