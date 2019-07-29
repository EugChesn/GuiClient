#ifndef SETTINGCONST_H
#define SETTINGCONST_H
#include <QtNetwork>
#include <QMutex>

class SettingConst
{
public:
    static SettingConst *getInstance();

    void saveSettingToFile();
    void createSettingFile();

    void setIpConrol(QString ip);
    void setPortConrol(quint16 port);
    void setControlMS(int ms);

    void setIpCamera1(QString ip);
    void setPortCamera1(quint16 port);

    void setIpCamera2(QString ip);
    void setPortCamera2(quint16 port);

    QString getIpConrol();
    quint16 getPortConrol();
    int getControlMS();

    QString getIpCamera1();
    quint16 getPortCamera1();

    QString getIpCamera2();
    quint16 getPortCamera2();

private:
    QString ipConrol = "127.0.0.1";
    quint16 portConrol = 7676;
    int controlMS = 250;

    QString ipCamera1 = "192.168.1.13";
    quint16 portCamera1 = 554;

    QString ipCamera2 = "192.168.1.13";
    quint16 portCamera2 = 554;


    QMutex mutex;
    static SettingConst *instance;
    SettingConst( const SettingConst& );
    SettingConst& operator=( SettingConst& );
    SettingConst();
};

#endif // SETTINGCONST_H
