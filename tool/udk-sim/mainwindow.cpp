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

#include "simserver.h"

MainWindow::MainWindow(QStringList args)
{
    _simProject = new SimProject(this);

    _logWidget = new QTextEdit();
    _logWidget->setReadOnly(true);
    setCentralWidget(_logWidget);
    createMenus();

    connect(SimServer::instance(), SIGNAL(clientAdded(SimClient *)), this, SLOT(setClient(SimClient *)));
    connect(_simProject, SIGNAL(logAppended(QString)), _logWidget, SLOT(insertHtml(QString)));

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
}

bool MainWindow::event(QEvent *event)
{
    if (event->type()==QEvent::Close)
    {
        QApplication::quit();
    }
    return QMainWindow::event(event);
}
