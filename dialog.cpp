#include "dialog.h"
#include "settingconst.h"
#include "ui_dialog.h"
#include <QTimer>
//#include <QProcess>
#include <QTextCodec>
#include <QDebug>

//using namespace  cv;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

   /* VideoThread * thVid = new VideoThread(this);
    connect(thVid,SIGNAL(send_frame(QImage *)),this,SLOT(processFrameAndUpdateGui(QImage *)));
    thVid->start();*/
    //parentWidget()->hide();

    //One thread video
    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *)
{
    parentWidget()->show();
}


void Dialog::startVideoThread()
{
    thVideo = new QThread;
    vidManagerCreator = new VideoManagegCreator();
    vidManagerCreator->moveToThread(thVideo);

    thVideo->start();
    QObject::connect(thVideo, SIGNAL(started()), vidManagerCreator, SLOT(create()));
    QObject::connect(thVideo, SIGNAL(finished()), vidManagerCreator, SLOT(deleteLater()));

    while(!vidManagerCreator->getManager()) { }
    QObject::connect(vidManagerCreator->getManager(),SIGNAL(frameReady(QImage)),this,SLOT(onFrame(QImage)));
}

void Dialog::stopVideoThread()
{
    if(thVideo->isRunning())
        thVideo->exit(0);

    this->close();
}
void Dialog::onFrame(QImage frame)
{
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(QPixmap::fromImage(frame.rgbSwapped()).scaled(w,h,Qt::KeepAspectRatio));
}
void Dialog::on_pushButton_clicked()
{
    startVideoThread();
    /*if(flag_ping_cam)
    {
        ui->plainTextEdit->appendPlainText("Host cam found");
        if(!cam.isOpened())
        {
            if(!cam.open(videoStreamAddress)) {
                 ui->plainTextEdit->appendPlainText("Error cam is not accessed successfully");
                 return;
            }
            else {
                 timer->start(10);
                 dWidth = cam.get(cv::CAP_PROP_FRAME_WIDTH); //задаем ширину
                 dHeight = cam.get(cv::CAP_PROP_FRAME_HEIGHT); //задаем высоту
                 fps = cam.get(cv::CAP_PROP_FPS);

                 //ui->label->setGeometry(800,600,800,600);

                 ui->plainTextEdit->appendPlainText("Width: " + QString::number(dWidth));
                 ui->plainTextEdit->appendPlainText("Height: " + QString::number(dHeight));
                 ui->plainTextEdit->appendPlainText("FPS: " + QString::number(fps));
                 ui->plainTextEdit->appendPlainText("Complete:))");
            }
        }
        else {
            if(timer->isActive() == true)
            {
                timer->stop();
                ui->pushButton->setText("Resume");
                ui->plainTextEdit->appendPlainText("Stop:))");
            }
            else
            {
                timer->start(10);
                ui->pushButton->setText("Stop");
                ui->plainTextEdit->appendPlainText("Start:))");
            }
        }
    }
    else
    {
        ui->plainTextEdit->appendPlainText("Host cam not found");
    }*/
}

void Dialog::on_pushButton_2_clicked()
{
    stopVideoThread();
}
