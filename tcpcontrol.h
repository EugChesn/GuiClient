#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include "server.h"

#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>


class TcpControl : public QObject
{
    Q_OBJECT
public:
    explicit TcpControl(quint16 port, QObject *parent = nullptr);
    ~TcpControl();
public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего
    //сокета (он нам важен, дабы у нас всегда был кто-то, кто будет вещать
private:
    QTcpServer *server; // указатель на сервер
    QTcpSocket *socket;
};

#endif // TCPCONTROL_H
