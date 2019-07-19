#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpcontrol.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    TcpControl* tcpControl;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onChangeStateServer(bool state);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void updateKeys();

private:
    Ui::MainWindow *ui;
    void startServer();

    bool upKey, downKey, rightKey, leftKey;
};

#endif // MAINWINDOW_H
