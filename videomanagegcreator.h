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

signals:
public slots:
    void create();
};

#endif // VIDEOMANAGEGCREATOR_H
