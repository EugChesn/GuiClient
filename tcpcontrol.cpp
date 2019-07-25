#include "tcpcontrol.h"

TcpControl* TcpControl::instance = nullptr;

TcpControl* TcpControl::getInstance()
{
    if(!instance)
        instance = new TcpControl();
    return instance;
}

void TcpControl::connectToHost(QHostAddress address, quint16 port)
{
    socket->connectToHost(QHostAddress::LocalHost, port);
    state = true;
    emit getState(true);
}

void TcpControl::disconnectToHost()
{
    emit getState(false);
    state = false;
    socket->close();
}

void TcpControl::sendCommand(double axisLeftX, double axisLeftY, double axisRightX, double axisRightY)
{
    this->axisLeftX = axisLeftX;
    this->axisLeftY = axisLeftY;
    this->axisRightX = axisRightX;
    this->axisRightY = axisRightY;
    QByteArray byteArray;
    byteArray = command.toUtf8();
    socket->write(byteArray);
    socket->flush();
}

TcpControl::TcpControl(quint16 port, QObject *parent) : QObject(parent)
{
    this->port = port;
    //server = new QTcpServer(this);
    socket = new QTcpSocket(this);
    QString log = " Socket init";

    qDebug() << log;
    emit getLog(log);
    //connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(hostFound()), this, SLOT(hostFound()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
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
//    if (socket->state() == QTcpSocket::ConnectedState) {
//        QString command = QString::fromUtf8(socket->readAll());
//        qDebug() << command;
//        emit getCommand(command);
//    }
    emit getLog("Socket ready Read!");
    qDebug() << "Socket ready read";
    socket->waitForReadyRead(1000);
    QByteArray data = socket->readAll();

    qDebug() << data;
    emit getLog(data);
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
    QString strErorr = " ERROR: " + error;
    qDebug() << strErorr;
    emit getError(strErorr);
    emit getState(false);
    return error;
}

void TcpControl::connected()
{
    emit getState(true);
    state = true;
}

void TcpControl::disconnected()
{
    emit getState(false);
    state = false;
    connectToHost(address, port);
}

void TcpControl::hostFound()
{

}

void TcpControl::sendCommandUsingTimer()
{

}

