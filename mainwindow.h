#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcontrol.h>
#include <QGamepad>
#include <QLabel>
#include "mrvisuallib.h"

#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    TcpControl *tcpControl;
    QGamepad *gamepad;

    MRVisualLib *mrVisual;
    //OpenCvCam *openCam;


    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_stop_clicked();
    void on_setings_clicked();

    void appendText(QString text);

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



    //PING
    void ping_timer_server();
    void ping_timer_camera1();
    void ping_timer_camera2();
    void print_ping_server();
    void print_ping_camera1();
    void print_ping_camera2();
    //---------------------

    //MRVisual
    void handlerMRVisual(float x, float y, float z);
    //------------------------------

    //GAZ
    void handleGaz(int g1, int g2, int g3, int g4);
    //---------------
protected:
    //для обработки клавиатуры
//    bool eventFilter(QObject *obj, QEvent *event);
//    void updateKeys();

    virtual void resizeEvent(QResizeEvent *event) override;


private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QThread *threadTcpControl;

    void startTimerForSendStickCommand();
    //SERVER
    void startServer();
    void stopSocket();
    bool isTcpControlConnectedSignal = false;
    bool isTcpControlConnected = false;
    //--------------------

    //Отображение положения в пространстве!!!
    void startMRVisual();
    void stopMRVusual();
    bool isMRVisualConnectedSignal = false;
    //---------------------------------------

    //Отображение газов
    void startGaz();
    void stopGaz();
    bool isGazConnectedSignal = false;
    //---------------------------------------

    //PING
    void startPing();
    QProcess *pingServer, *pingCamera1, *pingCamera2;
    int count_signal_ping_Server, count_signal_ping_Camera_1, count_signal_ping_Camera_2;
    //--------------------------

    //Управление
    QLabel *redL,*redR; // красные квадратики
    bool isGamepadConnectedSignal = false;

    void startGamepad();
    void stopGamepad();
    void paintStick(); //рисует красный квадратики на изображении геймпада

    bool upKey, downKey, rightKey, leftKey;
    double axisLeftX=0, axisLeftY=0, axisRightX=0, axisRightY=0;
    //--------------------------------------------------------------------
};

#endif // MAINWINDOW_H
