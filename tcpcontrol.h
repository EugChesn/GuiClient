#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>


class TcpControl : public QObject
{
    Q_OBJECT
public:
//    enum Command {
//      UP,
//      DOWN,
//      LEFT,
//      RIGHT
//    };


    static TcpControl* getInstance();
    //public
    quint16 port;
    QHostAddress address = QHostAddress::LocalHost;
    bool state = false;
    void connectToHost(QHostAddress address, quint16 port);
    void disconnectToHost();

    //destructor
    ~TcpControl();


signals:
    void getError(QString err);
    void getLog(QString log);
    void getCommand(double axisLeftX, double axisLeftY, double axisRightX, double axisRightY);
    void getState(bool state);



public slots:
    void sendCommand(/*Command command*/double axisLeftX, double axisLeftY, double axisRightX, double axisRightY);
    //void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState state); // обработчик изменения состояния вещающего
    QAbstractSocket::SocketError onError(QAbstractSocket::SocketError socketError);
    void connected();
    void disconnected();
    void hostFound();

    void sendCommandUsingTimer();


private:
    //local
  //  QTcpServer *server; // указатель на сервер
    QTcpSocket *socket;
//    QString error;
//    QString log;
//    QString command;

    //constructor
    static TcpControl *instance;
    TcpControl( const TcpControl& );
    TcpControl& operator=( TcpControl& );
    explicit TcpControl(quint16 port = 7676, QObject *parent = nullptr);

    double axisLeftX=0, axisLeftY=0, axisRightX=0, axisRightY=0;
    QString command = "lx:" + QString::number(int(axisLeftX*100)) + ",ly:" + QString::number(int(axisLeftY*100)) + ",rx:" + QString::number(int(axisRightX*100)) + ",ry:" + QString::number(int(axisRightY*100));


};

#endif // TCPCONTROL_H
