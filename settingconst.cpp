#include "settingconst.h"

SettingConst* SettingConst::instance = nullptr;

SettingConst *SettingConst::getInstance()
{
    //QMutex mutex;
    if(!instance)
        //mutex.lock();
        instance = new SettingConst();
        //mutex.unlock();
    return instance;
}

QString SettingConst::getAllToString()
{
    QStringList strList;
    strList.append("ipConrol:" + ipConrol);
    strList.append("portConrol:" + QString::number(portConrol));
    strList.append("controlMS:" + QString::number(controlMS));
    strList.append("ipCamera1:" + ipCamera1);
    strList.append("portCamera1:" + QString::number(portCamera1));
    strList.append("loginIpCamera1:" + loginIpCamera1);
    strList.append("passwordIpCamera1:" + passwordIpCamera1);
    strList.append("ipCamera2:" + ipCamera2);
    strList.append("portCamera2:" + QString::number(portCamera2));
    strList.append("loginIpCamera2:" + loginIpCamera2);
    strList.append("passwordIpCamera2:" + passwordIpCamera2);
    strList.append("сontrolMS:" + QString::number(controlMS));
    strList.append("frameMS:" + QString::number(frameMS));

    return strList.join("\n");
}

void SettingConst::saveSettingToFile()
{
    QFile file("setting.txt");


    if(file.open(QIODevice::WriteOnly))
    {
        file.write(getAllToString().toUtf8());
    }
    file.close();
}

void SettingConst::readSettingFromFile()
{
    QFile file("setting.txt");

    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd()) {
            QString line = file.readLine();
            QStringList str= line.split(":");
            if(str.at(0) == "ipConrol") {
                setIpConrol(str.at(1));
            }
            if(str.at(0) == "portConrol") {
                setPortConrol(str.at(1).toInt());
            }
            if(str.at(0) == "controlMS") {
                setControlMS(str.at(1).toInt());
            }
            if(str.at(0) == "ipCamera1") {
                setIpCamera1(str.at(1));
            }
            if(str.at(0) == "portCamera1") {
                setPortCamera1(str.at(1).toInt());
            }
            if(str.at(0) == "loginIpCamera1") {
                setLoginIpCamera1(str.at(1));
            }
            if(str.at(0) == "passwordIpCamera1") {
                setPasswordIpcamera1(str.at(1));
            }
            if(str.at(0) == "ipCamera2") {
                setIpCamera2(str.at(1));
            }
            if(str.at(0) == "portCamera2") {
                setPortCamera2(str.at(1).toInt());
            }
            if(str.at(0) == "loginIpCamera2") {
                setLoginIpCamera2(str.at(1));
            }
            if(str.at(0) == "passwordIpCamera2") {
                setPasswordIpcamera2(str.at(1));
            }
            if(str.at(0) == "сontrolMS") {
                setControlMS(str.at(1).toInt());
            }
            if(str.at(0) == "frameMS") {
                setFrameMS(str.at(1).toInt());
            }
        }
    }
}

void SettingConst::setIpConrol(QString ip)
{
    mutex.lock();
    this->ipConrol = ip;
    mutex.unlock();
}

void SettingConst::setPortConrol(quint16 port)
{
    mutex.lock();
    this->portConrol = port;
    mutex.unlock();
}

void SettingConst::setControlMS(int ms)
{
    mutex.lock();
    this->controlMS = ms;
    mutex.unlock();
}

void SettingConst::setIpCamera1(QString ip)
{
    mutex.lock();
    this->ipCamera1 = ip;
    mutex.unlock();
}

void SettingConst::setPortCamera1(quint16 port)
{
    mutex.lock();
    this->portCamera1 = port;
    mutex.unlock();
}

void SettingConst::setLoginIpCamera1(QString login)
{
    mutex.lock();
    this->loginIpCamera1 = login;
    mutex.unlock();
}

void SettingConst::setPasswordIpcamera1(QString password)
{
    mutex.lock();
    this->passwordIpCamera1 = password;
    mutex.unlock();
}

void SettingConst::setIpCamera2(QString ip)
{
    mutex.lock();
    this->ipCamera2 = ip;
    mutex.unlock();
}

void SettingConst::setPortCamera2(quint16 port)
{
    mutex.lock();
    this->portCamera2 = port;
    mutex.unlock();
}

void SettingConst::setLoginIpCamera2(QString login)
{
    mutex.lock();
    this->loginIpCamera2 = login;
    mutex.unlock();
}

void SettingConst::setPasswordIpcamera2(QString password)
{
    mutex.lock();
    this->passwordIpCamera2 = password;
    mutex.unlock();
}

void SettingConst::setFrameMS(int frameMS)
{
    mutex.lock();
    this->frameMS = frameMS;
    mutex.unlock();
}

QString SettingConst::getIpConrol()
{
    return ipConrol;
}

quint16 SettingConst::getPortConrol()
{
    return portConrol;
}

int SettingConst::getControlMS()
{
    return controlMS;
}

QString SettingConst::getIpCamera1()
{
    return ipCamera1;
}

quint16 SettingConst::getPortCamera1()
{
    return portCamera1;
}

QString SettingConst::getLoginIpCamera1()
{
    return loginIpCamera1;
}

QString SettingConst::getPasswordIpcamera1()
{
    return passwordIpCamera1;
}

QString SettingConst::getIpCamera2()
{
    return ipCamera2;
}

quint16 SettingConst::getPortCamera2()
{
    return portCamera2;
}

QString SettingConst::getLoginIpCamera2()
{
    return loginIpCamera2;
}

QString SettingConst::getPasswordIpcamera2()
{
    return passwordIpCamera2;
}

int SettingConst::getFrameMS()
{
    return frameMS;
}

SettingConst::SettingConst()
{

}
