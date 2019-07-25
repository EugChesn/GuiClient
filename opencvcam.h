#ifndef OPENCVCAM_H
#define OPENCVCAM_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QTimer>
#include <QObject>
#include <QImage>
#include <QPixmap>


class OpenCvCam : public QObject
{
    Q_OBJECT
public:
    explicit OpenCvCam(QObject *parent = nullptr);

private:
    cv::VideoCapture cam;
    cv::Mat matOriginal;
    QImage qimgOriginal;
    QTimer * timer;
    const std::string videoStreamAddress = "rtsp://admin:123456@192.168.1.13:554";

static OpenCvCam *instance;
public:
    static OpenCvCam *getInstance();

signals:
    void getPixmap(QPixmap);
    void errorCam();

public slots:
    void processFrameAndUpdateGui();
public:
    void RunCam();
};

#endif // OPENCVCAM_H
