#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>


class TcpControl : public QObject
{
    Q_OBJECT
public:
    explicit TcpControl(quint16 port, QObject *parent = nullptr);
    QAbstractSocket::SocketState state;
    ~TcpControl();
public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(QString text); // обработчик входящих данных
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего
    QAbstractSocket::SocketError onError(QAbstractSocket::SocketError socketError);
private:
    QTcpServer *server; // указатель на сервер
    QTcpSocket *socket;
};

#endif // TCPCONTROL_H
