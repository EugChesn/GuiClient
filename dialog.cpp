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
    start_Qthread = false;
    start_Qthread2 = false;

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
    if(start_Qthread)
        thVideo->~QThread();
    if(start_Qthread2)
        thVideo2->~QThread();
}

void Dialog::closeEvent(QCloseEvent *)
{
    parentWidget()->show();
    if(start_Qthread && start_Qthread2)
    {
         thVideo->exit(0); thVideo2->exit(0);
         while(!thVideo->isFinished() && !thVideo2->isFinished()) {} // ждем пока потоки закончат свое выполнение
    }
    start_Qthread = false;
    start_Qthread2 = false;
    this->~Dialog();
}


void Dialog::startVideoThread()
{
    thVideo = new QThread; // camera 1
    vidManagerCreator = new VideoManagegCreator(1);
    vidManagerCreator->moveToThread(thVideo);

    thVideo2 = new QThread; //camera 2
    vidManagerCreator2 = new VideoManagegCreator(2);
    vidManagerCreator2->moveToThread(thVideo2);

    thVideo->start(); // camera 1
    start_Qthread = true;

    thVideo2->start(); //camera 2
    start_Qthread2 = true;

    QObject::connect(thVideo, SIGNAL(started()), vidManagerCreator, SLOT(create())); // camera 1
    QObject::connect(thVideo, SIGNAL(finished()), vidManagerCreator, SLOT(deleteLater()));
    QObject::connect(vidManagerCreator,SIGNAL(sendFrame(QImage)),this,SLOT(onFrame(QImage)));

    QObject::connect(thVideo2, SIGNAL(started()), vidManagerCreator2, SLOT(create())); //camera 2
    QObject::connect(thVideo2, SIGNAL(finished()), vidManagerCreator2, SLOT(deleteLater()));
    QObject::connect(vidManagerCreator2,SIGNAL(sendFrame(QImage)),this, SLOT(onFrame2(QImage)));
}

void Dialog::stopVideoThread()
{
    if(start_Qthread)
        thVideo->exit(0);
    if(start_Qthread2)
        thVideo2->exit(0);
}
void Dialog::onFrame(QImage frame)
{
    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(QPixmap::fromImage(frame.rgbSwapped()).scaled(w,h,Qt::KeepAspectRatio));
}

void Dialog::onFrame2(QImage frame)
{
    int w = ui->label_2->width();
    int h = ui->label_2->height();
    ui->label_2->setPixmap(QPixmap::fromImage(frame.rgbSwapped()).scaled(w,h,Qt::KeepAspectRatio));
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
