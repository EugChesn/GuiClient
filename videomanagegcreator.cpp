#include "videomanagegcreator.h"

VideoManagegCreator::VideoManagegCreator(int number_cam)
{
    this->num_cam = number_cam;
    vidManager = nullptr;
}

VideoManager *VideoManagegCreator::getManager()
{
    return vidManager;
}

void VideoManagegCreator::create()
{
    std::string adress;
    if(num_cam == 1)
    {
        adress = ("rtsp://"+ SettingConst::getInstance()->getLoginIpCamera1()
                                  + ":"
                                  + SettingConst::getInstance()->getPasswordIpcamera1()
                                  +"@"
                                  + SettingConst::getInstance()->getIpCamera1() +
                                  ":"
                                  + QString::number(SettingConst::getInstance()->getPortCamera1())).toStdString();
    }
    else if(num_cam == 2)
    {
        adress = ("rtsp://"+ SettingConst::getInstance()->getLoginIpCamera2()
                                  + ":"
                                  + SettingConst::getInstance()->getPasswordIpcamera2()
                                  +"@"
                                  + SettingConst::getInstance()->getIpCamera2() +
                                  ":"
                                  + QString::number(SettingConst::getInstance()->getPortCamera2())).toStdString();
    }

    vidManager = new VideoManager(adress);
    QObject::connect(vidManager,SIGNAL(frameReady(QImage)),this,SLOT(onFrame(QImage)));
    vidManager->start();
}

void VideoManagegCreator::onFrame(QImage frame)
{
    //qDebug()<<"creator send";
    emit sendFrame(frame);
}

void VideoManagegCreator::stop()
{
    vidManager->stop();
}
VideoManagegCreator::~VideoManagegCreator()
{
    vidManager->~VideoManager();
}
