#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QtNetwork"
#include "settings.h"

#include <QPainter>
#include <QGamepad>
#include <QGamepadManager>
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Костыль!!
    paintStick();

    QGamepadManager * gamepadManager =  QGamepadManager::instance();
    int deviceId = gamepadManager->connectedGamepads().length() >0 ? gamepadManager->connectedGamepads()[0] : -1;
    gamepad = new QGamepad(deviceId, this);
    installEventFilter(this);
    upKey = downKey = rightKey = leftKey = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpControl;
    delete gamepad;
    delete timer;
}

void MainWindow::on_pushButton_clicked()
{
    startServer();
    startGamepad();
}

void MainWindow::onChangeStateServer(bool state)
{
    QString strState;
    isTcpControlConnected = state;
    if(state) {
        QPixmap pix(":/images/connect.png");
        strState = "connect";
        ui->label_3->setPixmap(pix);
    } else {
        QPixmap pix(":/images/disconnect.png");
        ui->label_3->setPixmap(pix);
        strState = "disconnect";
    }
}

void MainWindow::sendStickCommand()
{
    tcpControl->setCommand(axisLeftX, axisLeftY, axisRightX, axisRightY);
}

void MainWindow::axisLeftXChanged(double value)
{
    this->axisLeftX = value;
    sendStickCommand();
    //ui->plainTextEdit->appendPlainText("axisLeftX: " + QString::number(value));
    redL->move((axisLeftX*50)+75, (axisLeftY*50)+75);
}

void MainWindow::axisLeftYChanged(double value)
{
    this->axisLeftY = value;
   sendStickCommand();
    //ui->plainTextEdit->appendPlainText("axisLeftY: " + QString::number(value));
    redL->move((axisLeftX*50)+75, (axisLeftY*50)+75);
}

void MainWindow::axisRightXChanged(double value)
{
    this->axisRightX = value;
    sendStickCommand();
    //ui->plainTextEdit->appendPlainText("axisRightX: " + QString::number(value));
    redR->move((axisRightX*50)+75, (axisRightY*50)+75);
}

void MainWindow::axisRightYChanged(double value)
{
    this->axisRightY = value;
    sendStickCommand();
    //ui->plainTextEdit->appendPlainText("axisRightY: " + QString::number(value));
    redR->move((axisRightX*50)+75, (axisRightY*50)+75);
}

void MainWindow::onErrorTcpSocket(QString error)
{
    QString redText = "<span style=\" font-size:8pt; font-weight:600; color:#ff0000;\" >";
    redText.append(error);
    redText.append("</span>");
    ui->plainTextEdit->appendHtml(redText);
    QTimer::singleShot(250, this, SLOT(on_pushButton_clicked()));
}

void MainWindow::startServer()
{
    tcpControl = TcpControl::getInstance();
    if(!isTcpControlConnected) {
        tcpControl->connectToHost();
        isTcpControlConnected = true;
//        if(timer != nullptr && timer->isActive()) {
//            disconnect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));
//            timer->stop();
//        }
        ui->plainTextEdit->appendPlainText(" Server port: " + SettingConst::getInstance()->getPortConrol());
        if(!isTcpControlConnectedSignal){
            connect(tcpControl, SIGNAL(getLog(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
            connect(tcpControl, SIGNAL(getError(QString)), this, SLOT(onErrorTcpSocket(QString)));
            connect(tcpControl, SIGNAL(getState(bool)), this, SLOT(onChangeStateServer(bool)));
            isTcpControlConnectedSignal = true;
            onChangeStateServer(true);
            tcpControl->sendCommandUsingTimer();
        }
    }

}

void MainWindow::startGamepad()
{
    if(!isGamepadConnectedSignal) {
        isGamepadConnectedSignal = true;
        redL->setVisible(true);
        redR->setVisible(true);
        QGamepadManager * gamepadManager =  QGamepadManager::instance();
        int deviceId = gamepadManager->connectedGamepads().length() >0 ? gamepadManager->connectedGamepads()[0] : -1;
        gamepad = new QGamepad(deviceId, this);
        if(gamepad->isConnected()) {
            ui->plainTextEdit->appendPlainText("Геймпад подключён!");
            connect(gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(axisLeftXChanged(double)));
            connect(gamepad, SIGNAL(axisLeftYChanged(double)), this, SLOT(axisLeftYChanged(double)));
            connect(gamepad, SIGNAL(axisRightXChanged(double)), this, SLOT(axisRightXChanged(double)));
            connect(gamepad, SIGNAL(axisRightYChanged(double)), this, SLOT(axisRightYChanged(double)));
            startTimerForSendStickCommand();
        }
        else {
            ui->plainTextEdit->appendPlainText("Подключите Геймпад!");
        }
    }
}


void MainWindow::paintStick()
{
    QPixmap pix(":/images/red.png");
    redL = new QLabel(ui->leftStick);
    redL->setAlignment( Qt::AlignCenter);
    redL->setGeometry(7,7,7,7);
    redL->setPixmap(pix);
    redL->setVisible(false);
    redL->move(75,75);
    redR = new QLabel(ui->rightStick);
    redR->setAlignment( Qt::AlignCenter);
    redR->setGeometry(7,7,7,7);
    redR->setPixmap(pix);
    redR->setVisible(false);
    redR->move(75,75);
}

void MainWindow::startTimerForSendStickCommand()
{

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
    if (upKey) {
        text.append("Up");
    }
    if (downKey) {
        text.append("Down");
    }
    if (rightKey) {

        text.append("Right");
    }
    if (leftKey) {

        text.append("Left");
    }
    qDebug() << text;
    ui->event_arrows->setText(text);

    leftKey = false;
    rightKey = false;
    downKey = false;
    upKey = false;
}

void MainWindow::on_stop_clicked()
{
    stopGamepad();
    stopSocket();
    ui->plainTextEdit->appendPlainText("Все отключенно!");
}

void MainWindow::stopGamepad()
{
    if(isGamepadConnectedSignal) {
        disconnect(gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(axisLeftXChanged(double)));
        disconnect(gamepad, SIGNAL(axisLeftYChanged(double)), this, SLOT(axisLeftYChanged(double)));
        disconnect(gamepad, SIGNAL(axisRightXChanged(double)), this, SLOT(axisRightXChanged(double)));
        disconnect(gamepad, SIGNAL(axisRightYChanged(double)), this, SLOT(axisRightYChanged(double)));
        gamepad->deleteLater();
        redL->setVisible(false);
        redR->setVisible(false);
        isGamepadConnectedSignal = false;
    }
}

void MainWindow::stopSocket()
{
    if(isTcpControlConnected) {
        tcpControl->disconnect = true;
        tcpControl->disconnectToHost();
        isTcpControlConnected = false;
    }
    if(isTcpControlConnectedSignal) {
        onChangeStateServer(false);
        disconnect(tcpControl, SIGNAL(getLog(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
        disconnect(tcpControl, SIGNAL(getError(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
        disconnect(tcpControl, SIGNAL(getState(bool)), this, SLOT(onChangeStateServer(bool)));
        isTcpControlConnectedSignal = false;
    }
}

void MainWindow::on_startCam_clicked()
{
    /*QThread * start_dialog = new QThread;
    Dialog *mDialog = new Dialog(this);
    mDialog->moveToThread(start_dialog);*/

    Dialog *mDialog = new Dialog(this);
    mDialog->show();
}

void MainWindow::on_setings_clicked()
{
    Settings *dialogSettings = new Settings(this);
    dialogSettings->show();
    if (dialogSettings->exec() == QDialog::Accepted) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание!");
        msgBox.setText("Настройки применены.");
        msgBox.exec();
    }
}
