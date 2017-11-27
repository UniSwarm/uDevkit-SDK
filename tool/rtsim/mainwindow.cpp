#include "mainwindow.h"

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
}

MainWindow::~MainWindow()
{
}

bool MainWindow::openProject(const QString &path)
{
    QString mpath = path;
    qDebug()<<path;
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
