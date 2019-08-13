#ifndef TESTGUITHREAD_H
#define TESTGUITHREAD_H

#include <QObject>
#include <QWidget>
#include <QEvent>

#include "videomanagegcreator.h"
#include "videomanager.h"
#include <QThread>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class testGuiThread : public QObject
{
    Q_OBJECT
public:
    explicit testGuiThread(QObject *parent = nullptr);
private:
    QThread *thVideo;
    VideoManagegCreator * vidManagerCreator;

    QWidget * wid;
    QLabel * label;
    QVBoxLayout * vlayout;
    QPushButton *butt;
    QPushButton *stop_butt;
public:
    virtual bool event( QEvent *ev );

signals:

private slots:
    void click_start();
    void click_stop();
    void onFrame(QImage);

};

#endif // TESTGUITHREAD_H
