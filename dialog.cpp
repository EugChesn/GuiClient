#include "dialog.h"
#include "settingconst.h"
#include "ui_dialog.h"
#include <QTimer>
//#include <QProcess>
#include <QTextCodec>
#include <QDebug>
#include <QThread>

//using namespace  cv;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //parentWidget()->hide();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));

    timer_image = new QTimer(this);
    connect(timer_image,SIGNAL(timeout()),this,SLOT(status_image()));
    timer_image->start(1000);

    pixOn = new QPixmap(":/images/pingON.png");
    pixOff = new QPixmap(":/images/pingOFF.png");

    ping = new QProcess ();
    count_signal_ping = 0;
    connect(ping, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping()) );
    connect(ping,SIGNAL(finished(int)),ping,SLOT(kill()));

    timer_ping = new QTimer(this);
    connect(timer_ping,SIGNAL(timeout()),this,SLOT(ping_timer()));
    timer_ping->start(2000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *)
{
    parentWidget()->show();
}

bool Dialog::check_ping()
{
    ping = new QProcess ();
    ping->start("ping", QStringList() << "vk.com"<<"-n"<<"1");

    if(ping->waitForFinished())
    {
        QByteArray      output;
        output = ping->readAllStandardOutput();
        QString res = QTextCodec::codecForName("IBM866")->toUnicode(output);

        const int percent = res.mid(res.indexOf('('), res.indexOf(')')).section('%', 0, 0).remove('(').toInt();
        if (percent > 50)return false;
        else return true;
    }
}

void Dialog::processFrameAndUpdateGui()
{
    cam.read(matOriginal);
    if(matOriginal.empty() == true) return;
    qimgOriginal = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, QImage::Format_RGB888).rgbSwapped();

    int w = ui->label->width();
    int h = ui->label->height();
    ui->label->setPixmap(QPixmap::fromImage(qimgOriginal).scaled(w,h,Qt::KeepAspectRatio));
}

void Dialog::print_ping()
{
    /*QByteArray      output;
    output = ping->readAllStandardOutput();
    QString res = QTextCodec::codecForName("IBM866")->toUnicode(output);*/

    count_signal_ping++;
    qDebug()<<count_signal_ping;
    if(count_signal_ping % 2 == 0)
    {
        QByteArray out = ping->readAllStandardOutput();
        QString res = QTextCodec::codecForName("IBM866")->toUnicode(out);
        int percent = res.mid(res.indexOf('('), res.indexOf(')')).section('%', 0, 0).remove('(').toInt();

        QRegExp re("(Среднее = )\S*(?:\s\S+)?");
        if(res.contains(re)){
            QString strping = res.mid(res.indexOf(re)).split("=").at(1);
            ui->plainTextEdit->appendPlainText("Средняя задержка = " + strping);
        }
        qDebug()<<percent;
        if (percent > 50)
        {
            //ui->plainTextEdit->appendPlainText("Not found");
            flag_ping_cam = false;
            timer->stop();
        }
        else //!ui->plainTextEdit->toPlainText().contains("Found")
        {
            //ui->plainTextEdit->appendPlainText("Found");
            flag_ping_cam = true;
            timer->start(20);
        }
    }
}

void Dialog::status_image()
{
    if(flag_ping_cam)
    {
        ui->label_2->setPixmap(*pixOn);
    }
    else {
        ui->label_2->setPixmap(*pixOff);
    }
}

void Dialog::ping_timer()
{
    if(!ping->state() == QProcess::Starting)
        ping->start("ping", QStringList() << SettingConst::getInstance()->getIpCamera1() <<"-n"<<"1");
}

void Dialog::finished()
{

}
void Dialog::on_pushButton_clicked()
{
    qDebug() << "Dialog" << QThread::currentThreadId();
    if(flag_ping_cam)
    {
        ui->plainTextEdit->appendPlainText("Host cam found");
        if(!cam.isOpened())
        {
            if(!cam.open(videoStreamAddress.toStdString())) {
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
    }
}
