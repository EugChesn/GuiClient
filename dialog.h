#ifndef DIALOG_H
#define DIALOG_H

#include "settingconst.h"

#include <QDialog>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QProcess>
#include <QThread>
#include "videomanagegcreator.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Dialog *ui;

    VideoManagegCreator * vidManagerCreator;
    QThread * thVideo;

    /*cv::VideoCapture cam;
    double dWidth;
    double dHeight;
    double fps;
    cv::Mat matOriginal;
    QImage qimgOriginal;

    QProcess *ping;
    int count_signal_ping;
    bool flag_ping_cam;

    QPixmap *pixOn;
    QPixmap *pixOff;

    QTimer * timer;
    QTimer * timer_image;
    QTimer * timer_ping;
    std::string videoStreamAddress = ("rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
            + ":"
            + SettingConst::getInstance()->getPasswordIpcamera1()
            +"@"
            + SettingConst::getInstance()->getIpCamera1() +
            ":"
            + SettingConst::getInstance()->getPortCamera1()).toStdString();*/
public:
    //bool check_ping();

    void startVideoThread();
    void stopVideoThread();
public slots:
    //void processFrameAndUpdateGui();
    //void print_ping();
    //void status_image();
    //void ping_timer();
    //void finished();

    void onFrame(QImage frame);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // DIALOG_H
