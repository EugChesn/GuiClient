#ifndef VIDEOMANAGEGCREATOR_H
#define VIDEOMANAGEGCREATOR_H

#include <QObject>
#include "videomanager.h"

class VideoManagegCreator : public QObject
{
    Q_OBJECT
    VideoManager * vidManager;

public:
    //explicit VideoManagegCreator(QObject *parent = nullptr);
    VideoManagegCreator();
    VideoManager * getManager();
    ~VideoManagegCreator();

signals:
    void sendFrame(QImage);
public slots:
    void create();
    void onFrame(QImage);
};

#endif // VIDEOMANAGEGCREATOR_H
