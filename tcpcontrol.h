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
    bool state = false;

    void connectToHost();
    void disconnectToHost();
    void resetConnect();
    bool disconnect;

    //destructor
    ~TcpControl();


signals:
    void getError(QString err);
    void getLog(QString log);
    void getCommand(double axisLeftX = 0, double axisLeftY = 0, double axisRightX = 0, double axisRightY = 0);
    void getState(bool state);
    void getPositionInSpase(float x, float y, float z);



public slots:
    void sendCommand(/*double axisLeftX, double axisLeftY, double axisRightX, double axisRightY*/);
    void setCommand(double axisLeftX, double axisLeftY, double axisRightX, double axisRightY);
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
    explicit TcpControl(QObject *parent = nullptr);
    QTimer *timer;

    QByteArray intToArray(quint32 source);
    std::atomic_int axisLeftX, axisLeftY, axisRightX, axisRightY;
};

#endif // TCPCONTROL_H
