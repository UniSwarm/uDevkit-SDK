#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "simproject.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QStringList args);
    ~MainWindow();

public slots:
    bool openProject(const QString &path=QString());

protected:
    void createMenus();

    SimProject *_simProject;
};

#endif // MAINWINDOW_H
