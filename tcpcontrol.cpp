#include "settingconst.h"
#include "tcpcontrol.h"

TcpControl* TcpControl::instance = nullptr;

TcpControl* TcpControl::getInstance()
{
    if(!instance)
        instance = new TcpControl();
    return instance;
}

void TcpControl::connectToHost()
{
    socket->connectToHost(SettingConst::getInstance()->getIpConrol(), SettingConst::getInstance()->getPortConrol());
    state = true;
    emit getState(true);
    //emit getLog(" Socket connect to host");
    disconnect = false;
//    if(disconnect)
//        disconnect = false;
}

void TcpControl::disconnectToHost()
{
    setCommand(0,0,0,0);
    sendCommand();
    emit getState(false);
    state = false;
    socket->close();
    disconnect = true;
    timer->stop();
    timer->deleteLater();
}

void TcpControl::resetConnect()
{
//    if (!socket->reset()) {
//        connectToHost();
//        emit getLog(" Socket reset");
//    }
//    emit getLog(" Socket not reset");
}

void TcpControl::setCommand(double axisLeftX, double axisLeftY, double axisRightX, double axisRightY)
{
    this->axisLeftX = int(axisLeftX*100);
    this->axisLeftY = int(axisLeftY*100);
    this->axisRightX = int(axisRightX*100);
    this->axisRightY = int(axisRightY*100);
}
void TcpControl::sendCommand(/*double axisLeftX, double axisLeftY, double axisRightX, double axisRightY*/)
{
    QByteArray byteArray;
    QString command = "MOVE=lx:" + QString::number((axisLeftX)) + ",ly:" + QString::number((axisLeftY)) + ",rx:" + QString::number((axisRightX)) + ",ry:" + QString::number((axisRightY)) + ";";
    byteArray = command.toUtf8();
    socket->write(byteArray);
    socket->flush();
}

TcpControl::TcpControl(QObject *parent) : QObject(parent)
{
    //server = new QTcpServer(this);
    socket = new QTcpSocket(this);
    QString log = " Socket init";

    qDebug() << log;
    emit getLog(log);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(hostFound()), this, SLOT(hostFound()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->axisLeftX = 0;
    this->axisLeftY = 0;
    this->axisRightX = 0;
    this->axisRightY = 0;
}

QByteArray TcpControl::intToArray(quint32 source)
{
   QByteArray temp;
   QDataStream data(&temp, QIODevice::ReadWrite);
   data << source;
   return temp;
}

TcpControl::~TcpControl() {
    socket->deleteLater();
    //server->deleteLater();
    delete instance;
}




//void TcpControl::incommingConnection() // обработчик подключений
//{
//    while (server->hasPendingConnections()) {
//        socket = server->nextPendingConnection();
//        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
//        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
//        //socket->write("server hello");
//        socket->flush();
//        emit getState(1);
//    }
//}

void TcpControl::readyRead()
{
    QByteArray data = socket->readAll();
    QString commandServer = data;
    //qDebug() << "SERVER SEND:" << commandServer;
    if(commandServer.contains("POS=")) {
        int pos = 0;
        QRegExp rx("((\\d{1,3}\\.\\d{1,3})|(\\d{1,3}))");
        QStringList line;
        while ((pos = rx.indexIn(commandServer, pos)) != -1) {
            line.append(rx.cap(1));
            pos += rx.matchedLength();
        }
        float x = !line.at(0).isNull()? line.at(0).toFloat() > 0? line.at(0).toFloat() : 0 : 0;
        float y = !line.at(1).isNull()? line.at(1).toFloat() > 0? line.at(1).toFloat() : 0 : 0;
        float z = !line.at(2).isNull()? line.at(2).toFloat() > 0? line.at(2).toFloat() : 0 : 0;
        emit getPositionInSpase(x,y,z);
    }
    socket->flush();
}

QAbstractSocket::SocketState TcpControl::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    if(socket == nullptr) {
        emit getState(0);
        return QAbstractSocket::SocketState::ClosingState;
    }
    if(socket->state() == QTcpSocket::ConnectedState) {
        emit getState(1);
        this->state = true;
    } else {
        emit getState(0);
        this->state = false;
    }
    emit getLog("Socket status:" + QVariant::fromValue(state).toString());
    //this->state = state;
    qDebug() << state;
    return state;
}

QAbstractSocket::SocketError TcpControl::onError(QAbstractSocket::SocketError error)
{
    QString strErorr = "SOCKET ERROR: " + QVariant::fromValue(error).toString() + " dis: " +disconnect;
    qDebug() << strErorr;
    if(!disconnect){
        emit getError(strErorr);
        //disconnect = false;
    }
    emit getState(false);
//    if(!socket->reset())
//        resetConnect();
    return error;
}

void TcpControl::connected()
{
    emit getState(true);
    state = true;
    emit getLog(" Socket connected!");
}

void TcpControl::disconnected()
{
    emit getState(false);
    state = false;
    if(!disconnect){
         emit getError(" Socket disconnected!");
        //disconnect = false;
    }
//    if(!this->disconnect) {
//        connectToHost()
//    }
}

void TcpControl::hostFound()
{

}



void TcpControl::sendCommandUsingTimer()
{
    if(timer != nullptr)
        timer = new QTimer(this);
    if(!timer->isActive()) {
        if(!disconnect)
            connect(timer, SIGNAL(timeout()), this, SLOT(sendCommand()));
        timer->start(SettingConst::getInstance()->getControlMS());
    }
}

