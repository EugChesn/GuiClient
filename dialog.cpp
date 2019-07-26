#include "dialog.h"
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
    //parentWidget()->hide();

        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));


        /*QString nParameter = "-n";
        QString pingCount = "1"; //(int)
        QString wParameter = "-w";
        QString pingWaitTime = "10"; //(ms)
        QProcess *pingProcess = new QProcess;
        int exitCode = pingProcess->execute("ping",QStringList()<<"vk.net"<<nParameter<<pingCount<<wParameter<<pingWaitTime);
        if (exitCode==0){

           //qDebug()<<"TEst";
        }*/
        ping = new QProcess ();
        ping->start("ping", QStringList() << "yandex.ru"  );
        connect(ping, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping()) );

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *)
{
    parentWidget()->show();
}

void Dialog::processFrameAndUpdateGui()
{
    cam.read(matOriginal);
    if(matOriginal.empty() == true) return;
    qimgOriginal = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, QImage::Format_RGB888).rgbSwapped();
    ui->label->setPixmap(QPixmap::fromImage(qimgOriginal));
}

void Dialog::print_ping()
{
    QByteArray      output;
    output = ping->readAllStandardOutput();
    int s = ping->state();
    QString res = QTextCodec::codecForName("IBM866")->toUnicode(output);
    ui->plainTextEdit->appendPlainText(res + QString::number(s));

}

void Dialog::on_pushButton_clicked()
{
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
