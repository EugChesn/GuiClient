#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "settingconst.h"

class VideoManager : public QObject
{
    Q_OBJECT
public:
    //explicit VideoManager(QObject *parent = nullptr);
    VideoManager();
    ~VideoManager();

private:
    QTimer * timerHandler;
    cv::VideoCapture vc;
    QImage *qimgOriginal;
    std::string adress = ("rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
                          + ":"
                          + SettingConst::getInstance()->getPasswordIpcamera1()
                          +"@"
                          + SettingConst::getInstance()->getIpCamera1() +
                          ":"
                          + SettingConst::getInstance()->getPortCamera1()).toStdString();


signals:
    void frameReady(QImage);

public slots:
    void handleFrame();
    void start();
    void stop();
};

#endif // VIDEOMANAGER_H
