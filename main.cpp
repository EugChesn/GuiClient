#include "mainwindow.h"
#include "tcpcontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    quint16 port = 7676;
    TcpControl tcpControl(port);

    return a.exec();
}
