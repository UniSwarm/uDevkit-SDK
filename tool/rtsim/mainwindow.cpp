#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QStringList args) :
    ui(new Ui::MainWindow)
{
    Q_UNUSED(args)
    ui->setupUi(this);

    _simServer = new SimServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}
