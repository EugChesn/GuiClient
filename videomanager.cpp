#include "videomanager.h"

VideoManager::VideoManager()
{
    timerHandler = new QTimer();
    timerHandler->setInterval(SettingConst::getInstance()->getFrameMS());
    connect(timerHandler,SIGNAL(timeout()),this,SLOT(handleFrame()));
}

VideoManager::~VideoManager()
{
    timerHandler->deleteLater();
}

void VideoManager::handleFrame()
{
    cv::Mat original;
    vc.read(original);
    qDebug()<<"start read frame";
    if(original.empty() == true) return;

    QImage  * qimgOriginal = new QImage(original.data, original.cols, original.rows, QImage::Format_RGB888);
    //qimgOriginal->rgbSwapped();


    qDebug()<<"qimg frame";
    //qDebug()<< QThread::currentThreadId();

    emit frameReady(qimgOriginal->copy());
}

void VideoManager::start()
{
    adress =("rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
                              + ":"
                              + SettingConst::getInstance()->getPasswordIpcamera1()
                              +"@"
                              + SettingConst::getInstance()->getIpCamera1() +
                              ":"
                              + SettingConst::getInstance()->getPortCamera1()).toStdString();
    vc.open(adress);
    timerHandler->start();
}
void VideoManager::stop()
{
    timerHandler->stop();
}


