#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new Protocole;
    map = new Map();

    connect(port, SIGNAL(dataRec(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
    connect(port, SIGNAL(posChanged(int,int,int)), map, SLOT(setPosition(int,int,int)));
    connect(port, SIGNAL(accelChanged(int,int,int)), this, SLOT(addAccel(int,int,int)));

    ui->graphicsView->setScene(map);
    ui->graphicsView->setSceneRect(-100,-100,3100,2100);
    ui->graphicsView->scale(0.25,0.25);

    _time = 0;
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setAdaptiveSampling(true);
    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::green));
    ui->plot->graph(1)->setAdaptiveSampling(true);
    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::blue));
    ui->plot->graph(2)->setAdaptiveSampling(true);
    ui->plot->xAxis->setRange(0, 200);
    ui->plot->yAxis->setRange(-128, 128);

    //this->setGeometry(2500,300,500,600);

    connect(port, SIGNAL(sensor1Changed(int)), ui->horizontalSlider, SLOT(setValue(int)));
    connect(port, SIGNAL(sensor2Changed(int)), ui->horizontalSlider_2, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete port;
}


void MainWindow::send()
{

}

void MainWindow::addAccel(int x, int y, int z)
{
    if(_atime.count()>200)
    {
        _ax.pop_front();
        _ay.pop_front();
        _az.pop_front();
    }
    else
        _atime.push_back(_time);

    _ax.push_back(x);
    _ay.push_back(y);
    _az.push_back(z);

    ui->plot->graph(0)->setData(_atime, _ax, true);
    ui->plot->graph(1)->setData(_atime, _ay, true);
    ui->plot->graph(2)->setData(_atime, _az, true);
    ui->plot->replot();
    _time++;
}

void MainWindow::sendAx()
{

}

void MainWindow::sendLed()
{

}
