#include "mainwindow.h"
#include "tcpcontrol.h"
#include <QApplication>
#include <settingconst.h>
#include "testguithread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // create holder
    /*testGuiThread gl;
    // move it to main thread
    gl.moveToThread(QApplication::instance()->thread());
    // send it event which will be posted from main thread
    QCoreApplication::postEvent(&gl, new QEvent(QEvent::User));*/

    SettingConst::getInstance()->readSettingFromFile();
    w.show();

    return a.exec();
}
