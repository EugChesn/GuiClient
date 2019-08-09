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
    bool state = false; // это для  отображения connect.png в mainwindow

    void connectToHost(); // используется для коннекта к серверу в mainwindow
    void disconnectToHost(); // аналогично
    void resetConnect(); // хотела быть фичей, но стала багом, поэтому не используется
    bool disconnect; // как же без неё? bool всегда надежно!


    QByteArray compressData(const QVariant &var);
    //QVariant uncompressData(const QByteArray &data);

    //destructor
    ~TcpControl();


signals:
    void getError(QString err);
    void getLog(QString log);
    void getCommand(double axisLeftX = 0, double axisLeftY = 0, double axisRightX = 0, double axisRightY = 0);
    void getState(bool state);
    void getPositionInSpase(float x, float y, float z);
    void getGaz(int g1, int g2, int g3, int g4);
    void getBattaryServer(int x);
    void getBattaryCamera1(int x);
    void getBattaryCamera2(int x);



public slots:
    void sendCommand(/*double axisLeftX, double axisLeftY, double axisRightX, double axisRightY*/); // отправляет команду на сервер по таймеру
    void setCommand(double axisLeftX, double axisLeftY, double axisRightX, double axisRightY); // получает от mainwindow по сигналу изменение положение стиков геймпада
    //void incommingConnection(); // обработчик входящего подключения
    void readyRead(); // обработчик входящих данных и получение команд от сервера(скорее всего нужно будет переписать или добавлять обертку)
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState state); // обработчик изменения состояния вещающего .. фигово работает лучше не надеятся на него
    void onError(QAbstractSocket::SocketError socketError); // он помимо ошибок кидает ещё и сигнал о состоянии Сокета. Майнвиндов  его отлавливает и пытается перезапустить клиент. Тут возможна ошибка со сложностью нажатия кнопки STOP.
    void connected(); // стандартый метод, не всегда срабатывает при кратковременном отключении сервака
    void disconnected();  // тоже не всегда срабатывает ошибка надежней
    void hostFound(); // плохо работает и не используется

    void sendCommandUsingTimer(); // запуск таймера для использования слота sendCommand()


private:
    QTcpSocket *socket;
    quint32     _nextBlockSize;

    //constructor
    static TcpControl *instance;
    TcpControl( const TcpControl& );
    TcpControl& operator=( TcpControl& );
    explicit TcpControl(QObject *parent = nullptr);

    QTimer *timer;

    QByteArray intToArray(quint32 source); // лишняя функция для подсчета кол-ва отправляемых данных

    void socketSendMessage(const QVariant &var);

    std::atomic_int axisLeftX, axisLeftY, axisRightX, axisRightY; // стики геймпада для отправки на сервер. Они Атомарные, вдруг будет многопоточность.
};

#endif // TCPCONTROL_H
