#include "mainwindow.h"
#include <QApplication>

#include "simserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create server and check if connected
    if(!SimServer::instance()->isConnected())
    {
        qErrnoWarning("Server cannot connect to port");
        exit(1);
    }

    MainWindow w(a.arguments());

    w.show();

    return a.exec();
}
