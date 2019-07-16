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

#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QDebug>
#include <QSettings>

#include "simserver.h"

MainWindow::MainWindow(QStringList args)
{
    readSettings();

    _simProject = new SimProject(this);

    _logWidget = new QTextEdit();
    _logWidget->setReadOnly(true);
    setCentralWidget(_logWidget);
    createMenus();
    updateOldProjects();

    connect(SimServer::instance(), SIGNAL(clientAdded(SimClient *)), this, SLOT(setClient(SimClient *)));
    connect(_simProject, SIGNAL(logAppended(QString)), this, SLOT(appendLog(QString)));

    if (args.size()>1)
        openProject(args[1]);

    showMaximized();
}

MainWindow::~MainWindow()
{
}

bool MainWindow::openProject(const QString &path)
{
    QString mpath = path;
    if (mpath.isEmpty())
    {
        QFileDialog dialog(this);
        dialog.setOption(QFileDialog::DontUseNativeDialog);
        dialog.setFileMode(QFileDialog::ExistingFiles);
#if defined(Q_OS_WIN)
        dialog.setNameFilter(tr("Exe (*.exe)"));
#else
        //dialog.setFilter(QDir::Executable | QDir::Files | QDir::AllDirs);
#endif
        if (!dialog.exec())
            return false;
        mpath = dialog.selectedFiles().first();
    }
    if (!_simProject->setExePath(mpath))
        return false;
    _simProject->start();

    QString fullPath = QFileInfo(mpath).absoluteFilePath();
    _oldProjects.removeOne(fullPath);
    _oldProjects.prepend(fullPath);
    if (_oldProjects.size() > 8)
        _oldProjects.removeLast();
    updateOldProjects();

    return true;
}

void MainWindow::setClient(SimClient *client)
{
    _simProject->setClient(client);
}

void MainWindow::createMenus()
{
    setMenuBar(new QMenuBar(this));

    // ============= file =============
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openPrjAction = new QAction(tr("Open &project"), this);
    openPrjAction->setStatusTip(tr("Opens a project as directory"));
    openPrjAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openPrjAction);
    connect(openPrjAction, SIGNAL(triggered()), this, SLOT(openProject()));
    fileMenu->addSeparator();
    for (int i=0; i < 8; i++)
    {
        QAction *recentAction = new QAction(this);
        fileMenu->addAction(recentAction);
        recentAction->setVisible(false);
        connect(recentAction, SIGNAL(triggered()), this, SLOT(openRecentFile()));
        _oldProjectsActions.append(recentAction);
    }

    fileMenu->addSeparator();
    QAction *exitAction = new QAction(tr("E&xit"), this);
    exitAction->setStatusTip(tr("Exits uConfig"));
    exitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}

void MainWindow::writeSettings()
{
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());

    // old projects write
    settings.beginWriteArray("projects");
    for (int i = 0; i < _oldProjects.size() && i < 8; ++i)
    {
        settings.setArrayIndex(i);
        QString path = _oldProjects[i];
        settings.setValue("path", path);
    }
    settings.endArray();
}

void MainWindow::readSettings()
{
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());

    // old projects read
    int size = settings.beginReadArray("projects");
    for (int i = 0; i < size && i < 8; ++i)
    {
        settings.setArrayIndex(i);
        QString path = settings.value("path", "").toString();
        if (!_oldProjects.contains(path) && !path.isEmpty())
            _oldProjects.append(path);
    }
    settings.endArray();
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        openProject(action->data().toString());
}

void MainWindow::updateOldProjects()
{
    for (int i=0; i<_oldProjects.size() && i < 8; i++)
    {
        QString path = _oldProjects[i];
        _oldProjectsActions[i]->setVisible(true);
        _oldProjectsActions[i]->setData(path);
        _oldProjectsActions[i]->setText(QString("&%1. %2").arg(i+1).arg(path));
        _oldProjectsActions[i]->setStatusTip(tr("Open recent project '")+path+"'");
    }
}

void MainWindow::appendLog(const QString &log)
{
    _logWidget->moveCursor(QTextCursor::End);
    _logWidget->insertHtml(log);
    _logWidget->moveCursor(QTextCursor::End);
}

bool MainWindow::event(QEvent *event)
{
    if (event->type()==QEvent::Close)
    {
        writeSettings();
        QApplication::quit();
    }
    return QMainWindow::event(event);
}
