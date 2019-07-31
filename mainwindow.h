#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcontrol.h>
#include <QGamepad>
#include <QLabel>
#include "mrvisuallib.h"

#include "dialog.h"
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

    MRVisualLib *mrVisual;
    //OpenCvCam *openCam;


    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_stop_clicked();


    //для геймпада
    void sendStickCommand();
    void axisLeftXChanged(double value);
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value);
    //------------------------
    //для сокета
    void onChangeStateServer(bool state);
    void onErrorTcpSocket(QString string);
    //------------------------------------

    //void errorReadCam();
    //void setPixmapOnLabel(QPixmap);
    //void on_btnCamera_clicked();

    void on_startCam_clicked();

    void on_setings_clicked();

    //PING
    void ping_timer_server();
    void ping_timer_camera1();
    void ping_timer_camera2();
    void print_ping_server();
    void print_ping_camera1();
    void print_ping_camera2();
    //---------------------

    void handlerMRVisual(float x, float y, float z);
protected:
    //для обработки клавиатуры
    bool eventFilter(QObject *obj, QEvent *event);
    void updateKeys();


private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QThread *threadTcpControl;



    void appendText(QString text);

    void startTimerForSendStickCommand();
    //SERVER
    void startServer();
    void stopSocket();
    //--------------------

    //Отображение положения в пространстве!!!
    void startMRVisual();
    void stopMRVusual();
    //---------------------------------------

    //PING
    void startPing();
    QProcess *pingServer, *pingCamera1, *pingCamera2;
    int count_signal_ping_Server, count_signal_ping_Camera_1, count_signal_ping_Camera_2;
    //--------------------------

    //Управление
    QLabel *redL,*redR;
    bool upKey, downKey, rightKey, leftKey;
    double axisLeftX=0, axisLeftY=0, axisRightX=0, axisRightY=0;
    bool isTcpControlConnectedSignal = false, isGamepadConnectedSignal = false, isMRVisualConnectedSignal = false;
    bool isTcpControlConnected = false;
    void startGamepad();
    void stopGamepad();
    void paintStick();
    //--------------------------------------------------------------------
};

#endif // MAINWINDOW_H
