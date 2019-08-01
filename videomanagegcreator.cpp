#include "videomanagegcreator.h"

VideoManagegCreator::VideoManagegCreator()
{
    vidManager = nullptr;

}

VideoManager *VideoManagegCreator::getManager()
{
    return vidManager;
}

void VideoManagegCreator::create()
{
    //qDebug() << QThread::currentThreadId() << "PhysicsManagerCreator::Create Physics Manager";
    vidManager = new VideoManager();
    QObject::connect(vidManager,SIGNAL(frameReady(QImage)),this,SLOT(onFrame(QImage)));
    vidManager->start();
}

void VideoManagegCreator::onFrame(QImage frame)
{
    emit sendFrame(frame);
}
VideoManagegCreator::~VideoManagegCreator()
{
    vidManager->~VideoManager();
}
