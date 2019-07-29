#include "opencvcam.h"
OpenCvCam *OpenCvCam::instance = nullptr;

OpenCvCam::OpenCvCam(QObject *parent) : QObject(parent)
{
    /*if(!cam.open(videoStreamAddress)) {
        //ui->plainTextEdit->appendPlainText("Error cam is not accessed successfully");
        emit errorCam();
        return;
    }*/
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));
    //timer->start(20);
}

OpenCvCam *OpenCvCam::getInstance()
{
    if(!instance)
        instance = new OpenCvCam();
        return instance;
}
void OpenCvCam::processFrameAndUpdateGui()
{
    cam.open(videoStreamAddress.toStdString());
    //if(!cam.open(videoStreamAddress)) {
    if(!cam.isOpened()) {
            //timer->stop();
            disconnect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));
            emit errorCam();
            return;
    }
    else
    {
        if(cam.read(matOriginal))
        {
            if(matOriginal.empty() == true) return;
            qimgOriginal = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, QImage::Format_RGB888).rgbSwapped();
            emit getPixmap(QPixmap::fromImage(qimgOriginal));
        }
        else
        {
            //timer->stop();
            disconnect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));
            emit errorCam();
        }
    }
}

void OpenCvCam::RunCam()
{
    if(timer->isActive() == true)
    {
        timer->stop();
    }
    else
    {
        timer->start(100);
    }
}

