#ifndef OPENCVCAM_H
#define OPENCVCAM_H
#include "settingconst.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QTimer>
#include <QObject>
#include <QImage>
#include <QPixmap>


class OpenCvCam : public QObject
{
    Q_OBJECT
public:
    explicit OpenCvCam(QObject *parent = nullptr);

private:
    cv::VideoCapture cam;
    cv::Mat matOriginal;
    QImage qimgOriginal;
    QTimer * timer;
    QString videoStreamAddress = "rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
            + ":"
            + SettingConst::getInstance()->getPasswordIpcamera1()
            +"@"
            + SettingConst::getInstance()->getIpCamera1() +
            ":"
            + SettingConst::getInstance()->getPortCamera1();

static OpenCvCam *instance;
public:
    static OpenCvCam *getInstance();

signals:
    void getPixmap(QPixmap);
    void errorCam();

public slots:
    void processFrameAndUpdateGui();
public:
    void RunCam();
};

#endif // OPENCVCAM_H
