#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcontrol.h>
#include <QGamepad>
#include <QLabel>

#include "opencvcam.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    TcpControl* tcpControl;
    QGamepad *gamepad;
    OpenCvCam *openCam;


    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void onChangeStateServer(bool state);
    void sendStickCommand();

    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value);

    void on_stop_clicked();
    void errorReadCam();

    void setPixmapOnLabel(QPixmap);

    void on_btnCamera_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void updateKeys();


private:
    Ui::MainWindow *ui;

    QTimer *timer;

    void startServer();
    void startGamepad();
    void appendText(QString text);
    void paintStick();
    void startTimerForSendStickCommand();

    QLabel *redL,*redR;
    bool upKey, downKey, rightKey, leftKey;
    double axisLeftX=0, axisLeftY=0, axisRightX=0, axisRightY=0;
    bool isTcpControlConnectedSignal = false, isGamepadConnectedSignal = false;
    bool isTcpControlConnected = false;
};

#endif // MAINWINDOW_H
