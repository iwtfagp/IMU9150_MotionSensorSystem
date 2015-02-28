#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include <QFile>
#include <QDir>

#include "mpu_9150.h"
#include <qwt_dial_needle.h>
#include <QTimer>
#include "stdio.h"
#include "LpmsSensorI.h"
#include "LpmsSensorManagerI.h"
#include <iostream>
#include <QDateTime>
#include <QMediaPlayer>
#include <QKeyEvent>
#include "my_qimu.h"


#include <QtConcurrent>
#include <Qfuture>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);

private slots:

    void updateView();
    void on_pushButton_deviceConnect_clicked();

    void on_pushButton_newFile_clicked();
    void on_pushButton_saveFile_clicked();
    void insertToTXT_Thread();

private:
    Ui::MainWindow *ui;
    QList<QString> list;
//    QTimer *timer_, *timer_file;
    QTimer *timer_;
    MPU_9150 *mpu9150_right_thigh, *mpu9150_right_shank, *mpu9150_left_thigh, *mpu9150_left_shank;
    LpmsSensorManagerI* manager;
    LpmsSensorI* lpms_back;
    ImuData d;
    QFile *file;
    QMediaPlayer *player,*player2;
    void insertToTXT();

};


#endif // MAINWINDOW_H
