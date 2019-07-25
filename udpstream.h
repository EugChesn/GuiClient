#ifndef UDPSTREAM_H
#define UDPSTREAM_H

#include <QObject>
#include <QUdpSocket>


class UdpStream : QObject
{
    Q_OBJECT
public:
    static UdpStream* getInstance();
    //public
    quint16 port;

    QAbstractSocket::SocketState state;

    ~UdpStream();

signals:
    void getError(QString err);
    void getLog(QString log);
    void getCommand(QString command);
    void getState(bool state);

public slots:
    void readyRead(); // обработчик входящих данных
    QAbstractSocket::SocketState stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего
    QAbstractSocket::SocketError onError(QAbstractSocket::SocketError socketError);

private:
    QUdpSocket *camera;



    static UdpStream *instance;
    UdpStream( const UdpStream& );
    UdpStream& operator=( UdpStream& );

    explicit UdpStream(quint16 port = 7670, QObject *parent = nullptr);
};

#endif // UDPSTREAM_H
