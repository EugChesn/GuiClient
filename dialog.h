#ifndef DIALOG_H
#define DIALOG_H

#include "settingconst.h"

#include <QDialog>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QProcess>

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
    cv::VideoCapture cam;
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
    QString videoStreamAddress = "rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
            + ":"
            + SettingConst::getInstance()->getPasswordIpcamera1()
            +"@"
            + SettingConst::getInstance()->getIpCamera1() +
            ":"
            + SettingConst::getInstance()->getPortCamera1();
public:
    bool check_ping();
public slots:
    void processFrameAndUpdateGui();
    void print_ping();
    void status_image();
    void ping_timer();
    void finished();

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_H
