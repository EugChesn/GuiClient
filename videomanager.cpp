#include "videomanager.h"

VideoManager::VideoManager()
{
    timerHandler = new QTimer();
    timerHandler->setInterval(20);
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
    vc.open("rtsp://admin:123456@192.168.1.13:554");
    timerHandler->start();
}
void VideoManager::stop()
{
    timerHandler->stop();
}


