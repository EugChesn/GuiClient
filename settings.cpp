#include "settings.h"
#include "ui_settings.h"

#include <QRegExpValidator>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange + "$");

    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->ipControl->setValidator(ipValidator);
    ui->portControl->setValidator(new QIntValidator(0, 65535, this));

    ui->ipCamera1->setValidator(ipValidator);
    ui->portCamera1->setValidator(new QIntValidator(0, 65535, this));

    ui->ipCamera2->setValidator(ipValidator);
    ui->portCamera2->setValidator(new QIntValidator(0, 65535, this));


    ui->ControlMS->setValidator(new QIntValidator(250, 10000, this));
    ui->frameMS->setValidator(new QIntValidator(250, 10000, this));
    ui->pingMS->setValidator(new QIntValidator(250, 10000, this));

    sConst = SettingConst::getInstance();



    ui->ipControl->setText(sConst->getIpConrol());
    ui->portControl->setText(QString::number(sConst->getPortConrol()));

    ui->ipCamera1->setText(sConst->getIpCamera1());
    ui->portCamera1->setText(QString::number(sConst->getPortCamera1()));
    ui->loginCamera1->setText(sConst->getLoginIpCamera1());
    ui->passwordCamera1->setText(sConst->getPasswordIpcamera1());


    ui->ipCamera2->setText(sConst->getIpCamera2());
    ui->portCamera2->setText(QString::number(sConst->getPortCamera2()));
    ui->loginCamera2->setText(sConst->getLoginIpCamera2());
    ui->passwordCamera2->setText(sConst->getPasswordIpcamera2());

    ui->ControlMS->setText(QString::number(sConst->getControlMS()));
    ui->frameMS->setText(QString::number(sConst->getFrameMS()));
    ui->pingMS->setText(QString::number(sConst->getPingMS()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    sConst->setIpConrol(ui->ipControl->text());
    sConst->setPortConrol(ui->portControl->text().toInt());

    sConst->setIpCamera1(ui->ipCamera1->text());
    sConst->setPortCamera1(ui->portCamera1->text().toInt());
    sConst->setLoginIpCamera1(ui->loginCamera1->text());
    sConst->setPasswordIpcamera1(ui->passwordCamera1->text());

    sConst->setIpCamera2(ui->ipCamera2->text());
    sConst->setPortCamera2(ui->portCamera2->text().toInt());
    sConst->setLoginIpCamera2(ui->loginCamera2->text());
    sConst->setPasswordIpcamera2(ui->passwordCamera2->text());

    sConst->setControlMS(ui->ControlMS->text().toInt());
    sConst->setFrameMS(ui->frameMS->text().toInt());
    sConst->setPingMS(ui->pingMS->text().toInt());

    sConst->saveSettingToFile();

    //if(ipControl)
}
