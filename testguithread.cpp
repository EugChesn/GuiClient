#include "testguithread.h"

testGuiThread::testGuiThread(QObject *parent) : QObject(parent)
{

}

bool testGuiThread::event(QEvent *ev)
{
    if(ev->type() == QEvent::User )
    {
        wid = new QWidget;
        vlayout = new QVBoxLayout;
        label = new QLabel;
        butt = new QPushButton("start");
        stop_butt = new QPushButton("stop");

        label->setGeometry(800,600,800,600);
        wid->setGeometry(900,700,900,700);

        vlayout->addWidget(label);
        vlayout->addWidget(butt);
        vlayout->addWidget(stop_butt);
        wid->setLayout(vlayout);


        QObject::connect(butt,SIGNAL(clicked()),this,SLOT(click_start()));
        QObject::connect(stop_butt,SIGNAL(clicked()),this,SLOT(click_stop()));
        wid->show();
        return true;
    }
    return false;
}

void testGuiThread::click_start()
{
    vidManagerCreator = new VideoManagegCreator(1);
    vidManagerCreator->create();
    QObject::connect(vidManagerCreator,SIGNAL(sendFrame(QImage)),this,SLOT(onFrame(QImage)));
}

void testGuiThread::click_stop()
{
    vidManagerCreator->stop();
}

void testGuiThread::onFrame(QImage frame)
{
    //qDebug()<<"on frame";
    int w = this->label->width();
    int h = this->label->height();
    this->label->setPixmap(QPixmap::fromImage(frame.rgbSwapped()).scaled(w,h,Qt::KeepAspectRatio));
}


