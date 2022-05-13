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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>

#include "simproject.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QStringList args);
    ~MainWindow() override;

public slots:
    bool openProject(const QString &path = QString());
    void setClient(SimClient *client);

protected:
    void createMenus();

    SimProject *_simProject;
    QTextEdit *_logWidget;

    void writeSettings();
    void readSettings();
    QList<QString> _oldProjects;
    QList<QAction *> _oldProjectsActions;

protected slots:
    void openRecentFile();
    void updateOldProjects();
    void appendLog(const QString &log);

    // QObject interface
public:
    bool event(QEvent *event) override;
};

#endif  // MAINWINDOW_H
