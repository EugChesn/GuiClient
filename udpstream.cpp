#include "udpstream.h"


UdpStream* UdpStream::instance = 0;

UdpStream *UdpStream::getInstance()
{
    if(!instance)
        instance = new UdpStream();
    return instance;
}

UdpStream::~UdpStream()
{
    camera->deleteLater();
    delete instance;
}

UdpStream::UdpStream(quint16 port, QObject *parent) : QObject(parent)
{
    this->port = port;

    camera = new QUdpSocket(this);

    camera->bind(QHostAddress::LocalHost, port);

    QString str1 = "Camera 1 listen port: " + QString::number(port);
    qDebug() << str1;
    emit getLog(str1);



    connect(camera, SIGNAL(readyRead()), this, SLOT(readyRead()));

    connect(camera, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    connect(camera, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));

}

void UdpStream::readyRead()
{
    if(camera->state() == QUdpSocket::ConnectedState) {

    }
}

QAbstractSocket::SocketState UdpStream::stateChanged(QAbstractSocket::SocketState state)
{
    if(camera == nullptr) {
        return QAbstractSocket::SocketState::ClosingState;
    }
    if(camera->state() == QUdpSocket::ConnectedState) {
        emit getState(0);
    } else {
        emit getState(1);
    }
    this->state = state;
    qDebug() << state;
    return state;
}

QAbstractSocket::SocketError UdpStream::onError(QAbstractSocket::SocketError socketError)
{
    QString strErorr = "ERROR: " + socketError;
    qDebug() << strErorr;
    emit getError(strErorr);
    return socketError;
}
