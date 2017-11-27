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
    ~MainWindow();

public slots:
    bool openProject(const QString &path=QString());
    void setClient(SimClient *client);

protected:
    void createMenus();

    SimProject *_simProject;
    QTextEdit *_logWidget;
};

#endif // MAINWINDOW_H
