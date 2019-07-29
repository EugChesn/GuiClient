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


        /*QString nParameter = "-n";
        QString pingCount = "1"; //(int)
        QString wParameter = "-w";
        QString pingWaitTime = "10"; //(ms)
        QProcess *pingProcess = new QProcess;
        int exitCode = pingProcess->execute("ping",QStringList()<<"vk.net"<<nParameter<<pingCount<<wParameter<<pingWaitTime);
        if (exitCode==0){

           //qDebug()<<"TEst";
        }*/
        //connect(ping, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping()) );

        ui->plainTextEdit->appendPlainText("Push button and wait for ping camera before open camera");
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
        QRegExp re("(Среднее = )\S*(?:\s\S+)?");
        ui->plainTextEdit->appendPlainText(res.mid(res.indexOf(re)));
        qDebug() << res.mid(res.indexOf(re));
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
void Dialog::on_pushButton_clicked()
{
    if(check_ping())
    {
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
