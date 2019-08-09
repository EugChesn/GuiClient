#include "videomanager.h"

VideoManager::VideoManager(std::string adress)
{
    this->adress = adress;
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
    //qDebug()<<"start read frame";
    if(original.empty() == true) return;

    //QImage  * qimgOriginal = new QImage(original.data, original.cols, original.rows, QImage::Format_RGB888);
     QImage fr(original.data, original.cols, original.rows, QImage::Format_RGB888);
    //qimgOriginal->rgbSwapped();


    //qDebug()<<"qimg frame";
    //qDebug()<< QThread::currentThreadId();

    //emit frameReady(qimgOriginal->copy());
     emit frameReady(fr.copy());
}

void VideoManager::start() //Настройки зависит от номера камеры (нужно при запуске передать)
{
    qDebug() <<"adress: "<< QString::fromStdString(adress);
    vc.open(adress);
    timerHandler->start();
}
void VideoManager::stop()
{
    timerHandler->stop();
}


