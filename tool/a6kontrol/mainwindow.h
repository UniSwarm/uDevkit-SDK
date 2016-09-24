#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "map.h"

#include "protocole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sendAx();
    void sendLed();
    void send();
    
private slots:
    void addAccel(int x, int y, int z);

private:
    Ui::MainWindow *ui;
    Protocole *port;
    Map *map;

    QVector<double> _ax;
    QVector<double> _ay;
    QVector<double> _az;
    QVector<double> _atime;
    int _time;
};

#endif // MAINWINDOW_H
