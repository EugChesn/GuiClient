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
    vidManager->start();
}
VideoManagegCreator::~VideoManagegCreator()
{
    vidManager->~VideoManager();
}
