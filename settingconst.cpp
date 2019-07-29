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

void SettingConst::saveSettingToFile()
{

}

void SettingConst::createSettingFile()
{

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

QString SettingConst::getIpCamera2()
{
    return ipCamera2;
}

quint16 SettingConst::getPortCamera2()
{
    return portCamera2;
}

SettingConst::SettingConst()
{

}
