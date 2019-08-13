#ifndef VIDEOMANAGEGCREATOR_H
#define VIDEOMANAGEGCREATOR_H

#include <QObject>
#include "videomanager.h"

class VideoManagegCreator : public QObject
{
    Q_OBJECT
    VideoManager * vidManager;

private:
    int num_cam;
public:
    //explicit VideoManagegCreator(QObject *parent = nullptr);
    VideoManagegCreator(int number_cam);
    VideoManager * getManager();
    ~VideoManagegCreator();

signals:
    void sendFrame(QImage);
public slots:
    void create();
    void onFrame(QImage);

public:
    void stop();
};

#endif // VIDEOMANAGEGCREATOR_H
