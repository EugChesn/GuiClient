#include "TcpControl.h"

TcpControl::TcpControl(quint16 port, QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    qDebug() << "server listen = " << server->listen(QHostAddress::Any, 7777);
    connect(server, SIGNAL(newConnection()), this, SLOT(incommingConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
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
    QTcpSocket * socket = (QTcpSocket*)sender();
    QByteArray arr = text.toUtf8();
    if (socket->state() == QTcpSocket::ConnectedState)
        socket->write(arr);
}
void TcpControl::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    QTcpSocket * socket = (QTcpSocket*)sender();
    if(socket == NULL) {
        return;
    }
    this->state = state;
    qDebug() << state;
}
