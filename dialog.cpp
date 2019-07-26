#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //parentWidget()->hide();

        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGui()));
        //timer->start(20);
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

void Dialog::on_pushButton_clicked()
{
    if(!cam.isOpened())
    {
        if(!cam.open(videoStreamAddress)) {
             ui->plainTextEdit->appendPlainText("Error cam is not accessed successfully");
             return;
        }
        else {
             timer->start(20);
             ui->plainTextEdit->appendPlainText("Complete:))");
        }
    }
    else {
        if(timer->isActive() == true)
        {
            timer->stop();
            ui->plainTextEdit->appendPlainText("Stop:))");
        }
        else
        {
            timer->start(20);
            ui->plainTextEdit->appendPlainText("Start:))");
        }
    }
}
