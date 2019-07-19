#include "tcpcontrol.h"

TcpControl* TcpControl::instance = 0;

TcpControl* TcpControl::getInstance()
{
    if(!instance)
        instance = new TcpControl();
    return instance;
}

TcpControl::TcpControl(quint16 port, QObject *parent) : QObject(parent)
{
    this->port = port;
    server = new QTcpServer(this); 
    QString log = " server listen port = " + port;
    server->listen(QHostAddress::Any, port);
    qDebug() << log;
    emit getLog(log);
    connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

TcpControl::~TcpControl() {
    socket->deleteLater();
    server->deleteLater();
}


void TcpControl::incommingConnection() // обработчик подключений
{
    while (server->hasPendingConnections()) {
        socket = server->nextPendingConnection();
        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        socket->write("server hello");
        socket->flush();
        emit getState(1);
    }
}

void TcpControl::readyRead()
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QString command = QString::fromUtf8(socket->readAll());
        qDebug() << command;
        emit getCommand(command);
    }
}

QAbstractSocket::SocketState TcpControl::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    if(socket == nullptr) {
        return QAbstractSocket::SocketState::ClosingState;
    }
    if(state == QAbstractSocket::ClosingState & this->state != state || state == QAbstractSocket::UnconnectedState & this->state != state) {
        emit getState(0);
    } else {
        emit getState(1);
    }
    this->state = state;
    qDebug() << state;
    return state;
}

QAbstractSocket::SocketError TcpControl::onError(QAbstractSocket::SocketError error)
{
    QString strErorr = "ERROR: " + error;
    qDebug() << strErorr;
    emit getError(strErorr);
    return error;
}

