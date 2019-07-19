#include "TcpControl.h"

TcpControl::TcpControl(quint16 port, QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    qDebug() << "server listen = " << server->listen(QHostAddress::Any, port);
    connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
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
        socket->write("hello");
        socket->flush();

    }
}

void TcpControl::readyRead(QString text)
{
    QByteArray arr = text.toUtf8();
    if (socket->state() == QTcpSocket::ConnectedState)
        socket->write(arr);
}
QAbstractSocket::SocketState TcpControl::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    if(socket == nullptr) {
        return QAbstractSocket::SocketState::ClosingState;
    }
    this->state = state;
    qDebug() << state;
}

QAbstractSocket::SocketError TcpControl::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "ERROR:" << error;
    return error;
}


