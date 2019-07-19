#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    installEventFilter(this);
    upKey = downKey = rightKey = leftKey = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    startServer();

}

void MainWindow::onChangeStateServer(bool state)
{
    QString strState;
    if(state) {
        QPixmap pix(":/images/connect.png");
        strState = "connect";
        ui->label_3->setPixmap(pix);
    } else {
        QPixmap pix(":/images/disconnect.png");
        ui->label_3->setPixmap(pix);
        strState = "disconnect";
    }
    ui->plainTextEdit->appendPlainText(" State: " + strState);
}

void MainWindow::startServer()
{
    tcpControl = TcpControl::getInstance();
    ui->plainTextEdit->appendPlainText(" Server port: " + QString::number(tcpControl->port));
    connect(tcpControl, SIGNAL(getLog(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
    connect(tcpControl, SIGNAL(getError(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
    connect(tcpControl, SIGNAL(getState(bool)), this, SLOT(onChangeStateServer(bool)));
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        // bool b;
        //bool b = event->type() == QEvent::KeyPress;

        //bool b;
        //event->type() == QEvent::KeyPress ? b = true : b = false;

        switch(ke->key())
        {
            case Qt::Key_Up:
            upKey = true;
            break;
            case Qt::Key_Down:
            downKey = true;
            break;
            case Qt::Key_Right:
            rightKey = true;
            break;
            case Qt::Key_Left:
            leftKey = true;
            break;
        }
        updateKeys();
        return true;

    }

    return QObject::eventFilter(obj, event);
}
void MainWindow::updateKeys()
{
    QString text;
    if (upKey) text.append("Up");
    if (downKey) text.append("Down");
    if (rightKey) text.append("Right");
    if (leftKey) text.append("Left");
    qDebug() << text;
    ui->event_arrows->setText(text);

    leftKey = false;
    rightKey = false;
    downKey = false;
    upKey = false;
}
