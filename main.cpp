#include "mainwindow.h"
#include "tcpcontrol.h"
#include <QApplication>
#include <settingconst.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SettingConst::getInstance()->readSettingFromFile();
    w.show();




    return a.exec();
}
