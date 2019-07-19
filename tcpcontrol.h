#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>


class TcpControl : public QObject
{
    Q_OBJECT
public:
    static TcpControl* getInstance();
    //public
    quint16 port;
    QAbstractSocket::SocketState state;

    //destructor
    ~TcpControl();


signals:
    void getError(QString err);
    void getLog(QString log);
    void getCommand(QString command);
    void getState(bool state);



public slots:
    void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего
    QAbstractSocket::SocketError onError(QAbstractSocket::SocketError socketError);



private:
    //local
    QTcpServer *server; // указатель на сервер
    QTcpSocket *socket;
//    QString error;
//    QString log;
//    QString command;

    //constructor
    static TcpControl *instance;
    TcpControl( const TcpControl& );
    TcpControl& operator=( TcpControl& );
    explicit TcpControl(quint16 port = 7676, QObject *parent = nullptr);


};

#endif // TCPCONTROL_H
