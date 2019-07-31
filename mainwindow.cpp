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

    //START PING
    startPing();
    //----------
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
    startMRVisual();
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
    redL->move((axisLeftX*50)+75, (axisLeftY*50)+75);
}

void MainWindow::axisLeftYChanged(double value)
{
    this->axisLeftY = value;
   sendStickCommand();
    redL->move((axisLeftX*50)+75, (axisLeftY*50)+75);
}

void MainWindow::axisRightXChanged(double value)
{
    this->axisRightX = value;
    sendStickCommand();
    redR->move((axisRightX*50)+75, (axisRightY*50)+75);
}

void MainWindow::axisRightYChanged(double value)
{
    this->axisRightY = value;
    sendStickCommand();
    redR->move((axisRightX*50)+75, (axisRightY*50)+75);
}

void MainWindow::onErrorTcpSocket(QString error)
{
    if(!isTcpControlConnectedSignal) {
        QString redText = "<span style=\" font-size:8pt; font-weight:600; color:#ff0000;\" >";
        redText.append(error);
        redText.append("</span>");
        QTime currTime = QTime::currentTime();
        ui->plainTextEdit->appendHtml("[" + currTime.toString("hh:mm:ss") + "]: " + redText);
    }
    if(isTcpControlConnectedSignal || isGamepadConnectedSignal)
        QTimer::singleShot(250, this, SLOT(on_pushButton_clicked()));
}

void MainWindow::startServer()
{
    tcpControl = TcpControl::getInstance();
    if(!isTcpControlConnected) {
        tcpControl->connectToHost();
        isTcpControlConnected = true;
        if(!isTcpControlConnectedSignal){
            connect(tcpControl, SIGNAL(getLog(QString)), this, SLOT(appendText(QString)));
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
            appendText("Геймпад подключён!");
            connect(gamepad, SIGNAL(axisLeftXChanged(double)), this, SLOT(axisLeftXChanged(double)));
            connect(gamepad, SIGNAL(axisLeftYChanged(double)), this, SLOT(axisLeftYChanged(double)));
            connect(gamepad, SIGNAL(axisRightXChanged(double)), this, SLOT(axisRightXChanged(double)));
            connect(gamepad, SIGNAL(axisRightYChanged(double)), this, SLOT(axisRightYChanged(double)));

            startTimerForSendStickCommand();
        }
        else {
            appendText("Подключите Геймпад!");
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

void MainWindow::appendText(QString text)
{
    QTime currTime = QTime::currentTime();
    ui->plainTextEdit->appendPlainText("[" + currTime.toString("hh:mm:ss") + "]: " + text);
}

void MainWindow::on_stop_clicked()
{
    stopGamepad();
    stopSocket();
    stopMRVusual();
    appendText("Все отключенно!");
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
        disconnect(tcpControl, SIGNAL(getLog(QString)), this, SLOT(appendText(QString)));
        disconnect(tcpControl, SIGNAL(getError(QString)), this, SLOT(onErrorTcpSocket(QString)));
        disconnect(tcpControl, SIGNAL(getState(bool)), this, SLOT(onChangeStateServer(bool)));
        isTcpControlConnectedSignal = false;
    }
}

//MRVisual-----------------------------------------
void MainWindow::startMRVisual()
{
    if(!isMRVisualConnectedSignal) {
        mrVisual = new MRVisualLib(this);
        connect(tcpControl, SIGNAL(getPositionInSpase(float,float,float)), this, SLOT(handlerMRVisual(float,float,float)));
        ui->gridLayoutMRVisual->addWidget(mrVisual);
        isMRVisualConnectedSignal = true;
    }
}

void MainWindow::stopMRVusual()
{
    if(isMRVisualConnectedSignal) {
        mrVisual->deleteLater();
        disconnect(tcpControl, SIGNAL(getPositionInSpase(float,float,float)), this, SLOT(handlerMRVisual(float,float,float)));
        isMRVisualConnectedSignal = false;
    }
}

void MainWindow::handlerMRVisual(float x, float y, float z)
{
    mrVisual->rotate(x,y,z);
}
//-------------------------------------

//PING------------------------------------------------
void MainWindow::startPing()
{
    //Ping to Server, Camera1, Camera2
    pingServer = new QProcess ();
    count_signal_ping_Server = 0;
    connect(pingServer, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_server()) );
    connect(pingServer,SIGNAL(finished(int)),pingServer,SLOT(kill()));

    pingCamera1 = new QProcess ();
    count_signal_ping_Camera_1 = 0;
    connect(pingCamera1, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_camera1()) );
    connect(pingCamera1,SIGNAL(finished(int)),pingCamera1,SLOT(kill()));

    pingCamera2 = new QProcess ();
    count_signal_ping_Camera_2 = 0;
    connect(pingCamera2, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_camera2()) );
    connect(pingCamera2,SIGNAL(finished(int)),pingCamera2,SLOT(kill()));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_server()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_camera1()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_camera2()));
    timer->start(SettingConst::getInstance()->getPingMS());
}

void MainWindow::ping_timer_server()
{
    if(!(pingServer->state() == QProcess::Starting))
        pingServer->start("ping", QStringList() << SettingConst::getInstance()->getIpConrol() <<"-n"<<"1");
}
void MainWindow::ping_timer_camera1()
{
    if(!(pingCamera1->state() == QProcess::Starting))
        pingCamera1->start("ping", QStringList() << SettingConst::getInstance()->getIpCamera1() <<"-n"<<"1");
}
void MainWindow::ping_timer_camera2()
{
    if(!(pingCamera2->state() == QProcess::Starting))
        pingCamera2->start("ping", QStringList() << SettingConst::getInstance()->getIpCamera2() <<"-n"<<"1");
}

void MainWindow::print_ping_server()
{
    count_signal_ping_Server++;
    if(count_signal_ping_Server % 2 == 0)
    {
        QByteArray out = pingServer->readAllStandardOutput();
        QString res = QTextCodec::codecForName("IBM866")->toUnicode(out);
        int percent = res.mid(res.indexOf('('), res.indexOf(')')).section('%', 0, 0).remove('(').toInt();
        QRegExp re("(Среднее = )\\S*(?:\\s\\S+)?");
        if(res.contains(re)){
            QString strping = res.mid(res.indexOf(re)).split("=").at(1);
            ui->pingTextServer->setText(strping);
        }
        if (percent > 50)
        {
            QPixmap pix(":/images/pingOFF.png");
            ui->pictureServerPing->setPixmap(pix);
            ui->pingTextServer->setText("");
        }
        else
        {
            QPixmap pix(":/images/pingON.png");
            ui->pictureServerPing->setPixmap(pix);
        }
    }
}

void MainWindow::print_ping_camera1()
{
    count_signal_ping_Camera_1++;
    if(count_signal_ping_Camera_1 % 2 == 0)
    {
        QByteArray out = pingCamera1->readAllStandardOutput();
        QString res = QTextCodec::codecForName("IBM866")->toUnicode(out);
        int percent = res.mid(res.indexOf('('), res.indexOf(')')).section('%', 0, 0).remove('(').toInt();

        QRegExp re("(Среднее = )\\S*(?:\\s\\S+)?");
        if(res.contains(re)){
            QString strping = res.mid(res.indexOf(re)).split("=").at(1);
            ui->pingTextCamera1->setText(strping);
        }
        if (percent > 50)
        {
            QPixmap pix(":/images/pingOFF.png");
            ui->pictureCamera1Ping->setPixmap(pix);
            ui->pingTextCamera1->setText("");
        }
        else
        {
            QPixmap pix(":/images/pingON.png");
            ui->pictureCamera1Ping->setPixmap(pix);
        }
    }
}

void MainWindow::print_ping_camera2()
{
    count_signal_ping_Camera_2++;
    if(count_signal_ping_Camera_2 % 2 == 0)
    {
        QByteArray out = pingCamera2->readAllStandardOutput();
        QString res = QTextCodec::codecForName("IBM866")->toUnicode(out);
        int percent = res.mid(res.indexOf('('), res.indexOf(')')).section('%', 0, 0).remove('(').toInt();
        QRegExp re("(Среднее = )\\S*(?:\\s\\S+)?");
        if(res.contains(re)){
            QString strping = res.mid(res.indexOf(re)).split("=").at(1);
            ui->pingTextCamera2->setText(strping);
        }
        if (percent > 50)
        {
            QPixmap pix(":/images/pingOFF.png");
            ui->pictureCamera2Ping->setPixmap(pix);
            ui->pingTextCamera2->setText("");
        }
        else
        {
            QPixmap pix(":/images/pingON.png");
            ui->pictureCamera2Ping->setPixmap(pix);
        }
    }
}
//------------------------------------------------------------------




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
        disconnect(pingServer, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_server()) );
        disconnect(pingServer,SIGNAL(finished(int)),pingServer,SLOT(kill()));
        disconnect(pingCamera1, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_camera1()) );
        disconnect(pingCamera1,SIGNAL(finished(int)),pingCamera1,SLOT(kill()));
        disconnect(pingCamera2, SIGNAL(readyReadStandardOutput ()), this, SLOT(print_ping_camera2()) );
        disconnect(pingCamera2,SIGNAL(finished(int)),pingCamera2,SLOT(kill()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_server()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_camera1()));
        disconnect(timer,SIGNAL(timeout()),this,SLOT(ping_timer_camera2()));


        startPing();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание!");
        msgBox.setText("Настройки применены.");
        msgBox.exec();
    }
}
