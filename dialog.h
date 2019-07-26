#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Dialog *ui;
    cv::VideoCapture cam;
    cv::Mat matOriginal;
    QImage qimgOriginal;
    QTimer * timer;
    const std::string videoStreamAddress = "rtsp://admin:123456@192.168.1.13:554";
public slots:
    void processFrameAndUpdateGui();
private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_H
