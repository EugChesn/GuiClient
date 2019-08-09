#ifndef SETTINGCONST_H
#define SETTINGCONST_H
#include <QtNetwork>
#include <QMutex>

class SettingConst
{
public:
    static SettingConst *getInstance();

    QString getAllToString();
    void saveSettingToFile();
    void readSettingFromFile();

    void setIpConrol(QString ip);
    void setPortConrol(quint16 port);
    void setControlMS(int ms);

    void setIpCamera1(QString ip);
    void setPortCamera1(quint16 port);
    void setLoginIpCamera1(QString login);
    void setPasswordIpcamera1(QString password);

    void setIpCamera2(QString ip);
    void setPortCamera2(quint16 port);
    void setLoginIpCamera2(QString login);
    void setPasswordIpcamera2(QString password);

    void setFrameMS(int frameMS);

    void setPingMS(int pingMS);

    QString getIpConrol();
    quint16 getPortConrol();
    int getControlMS();

    QString getIpCamera1();
    quint16 getPortCamera1();
    QString getLoginIpCamera1();
    QString getPasswordIpcamera1();

    QString getIpCamera2();
    quint16 getPortCamera2();
    QString getLoginIpCamera2();
    QString getPasswordIpcamera2();

    int getFrameMS();

    int getPingMS();

private:
    QString ipConrol = "127.0.0.1";
    quint16 portConrol = 7676;
    int controlMS = 250;

    /*QString ipCamera1 = "192.168.1.13";
    quint16 portCamera1 = 554;
    QString loginIpCamera1 = "admin";
    QString passwordIpCamera1 = "123456";

    QString ipCamera2 = "192.168.1.13";
    quint16 portCamera2 = 554;
    QString loginIpCamera2 = "admin";
    QString passwordIpCamera2 = "123456";*/

    QString ipCamera1 = "192.168.1.64";
    quint16 portCamera1 = 554;
    QString loginIpCamera1 = "admin";
    QString passwordIpCamera1 = "qwerty123";

    QString ipCamera2 = "192.168.1.64";
    quint16 portCamera2 = 554;
    QString loginIpCamera2 = "admin";
    QString passwordIpCamera2 = "qwerty123";

    int frameMS = 50;
    int pingMS = 2000;


    QMutex mutex;
    static SettingConst *instance;
    SettingConst( const SettingConst& );
    SettingConst& operator=( SettingConst& );
    SettingConst();
};

#endif // SETTINGCONST_H
