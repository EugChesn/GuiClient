#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcontrol.h>
#include <QGamepad>
#include <QLabel>
#include "mrvisuallib.h"

#include "videomanagegcreator.h"
//#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    TcpControl *tcpControl;
    QGamepad *gamepad;
    MRVisualLib *mrVisual;

    //OpenCvCam *openCam;


    //~MainWindow();
private slots:
    void on_pushButton_clicked(); // это кнопка старт
    void on_stop_clicked();
    void on_setings_clicked(); // открыть диалоговое окно с настройками

    void appendText(QString text); // вывод в plainText

    //для геймпада
    void sendStickCommand(); // отправить их в сокет
    void axisLeftXChanged(double value); // получить изменение положения стиков
    void axisLeftYChanged(double value);
    void axisRightXChanged(double value);
    void axisRightYChanged(double value); // ------
    //------------------------
    //для сокета
    void onChangeStateServer(bool state); //мменяет картинку соеденения с сервером connect.png
    void onErrorTcpSocket(QString string);
    //------------------------------------

    // для камеры
    void onFrame(QImage frame);
    void onFrame2(QImage frame);

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

    //Battery
    void handlerBataryServer(int x);
    void handlerBataryCamera1(int x);
    void handlerBataryCamera2(int x);
    //Battery

    //MRVisual
    void handlerMRVisual(int x, int y, int z);
    //------------------------------

    //GAZ
    void handleGaz(int g1, int g2, int g3, int g4);
    //---------------
protected:
    //для обработки клавиатуры
//    bool eventFilter(QObject *obj, QEvent *event);
//    void updateKeys();

    //virtual void resizeEvent(QResizeEvent *event) override;
    //void closeEvent (QCloseEvent *event) override;


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

    //Camera
    QThread *thVideo;
    VideoManagegCreator * vidManagerCreator;
    bool start_Qthread = false;

    QThread *thVideo2;
    VideoManagegCreator * vidManagerCreator2;
    bool start_Qthread2 = false;
    void startCamera();


    //Battery
    void startBatteryServer();
    bool isBatteryServerSignal = false;
    void startBatteryCamera1();
    bool isBatteryCamera1Signal = false;
    void startBatteryCamera2();
    bool isBatteryCamera2Signal = false;
    void stopBatteryServer();
    void stopBatteryCamera1();
    void stopBatteryCamera2();
    //---------------------

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
