#include "mainwindow.h"
#include "ui_mainwindow.h"




//#define TEST
//vector<double> data_buffer[15];
//double **data_buffer = new double[5][3];

const int row_Num = 5;
const int col_Num = 3;
double data_buffer[row_Num][col_Num];
double angle_data_buffer[4];
bool b_saving_file = false;

double* display_data;

enum Leg{LEFTTHIGH = 1, RIGHTTHIGH, LEFTSHANK, RIGHTSHANK};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer;


    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        list.append(info.portName());


    }
    ui->pushButton_newFile->setDisabled(true);
    ui->pushButton_saveFile->setDisabled(true);


    ui->comboBoxIMU_left_shank->addItems(list);
    ui->comboBoxIMU_left_thigh->addItems(list);
    ui->comboBoxIMU_right_shank->addItems(list);
    ui->comboBoxIMU_right_thigh->addItems(list);



    ui->comboBoxIMU_left_thigh->setCurrentText("COM3");
    ui->comboBoxIMU_right_thigh->setCurrentText("COM5");
    ui->comboBoxIMU_left_shank->setCurrentText("COM7");
    ui->comboBoxIMU_right_shank->setCurrentText("COM9");


//    ui->comboBoxIMU_left_thigh->setCurrentIndex(4);
//    ui->comboBoxIMU_right_thigh->setCurrentIndex(1);
//    ui->comboBoxIMU_left_shank->setCurrentIndex(12);
//    ui->comboBoxIMU_right_shank->setCurrentIndex(10);

    file = new QFile("out.txt");

    timer_ = new QTimer(this);
    timer_->stop();
    timer_->setInterval(20);

//    timer_file = new QTimer(this);
//    timer_file->stop();
//    timer_file->setInterval(10);

    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateView()));
//    QObject::connect(timer_file, SIGNAL(timeout()), this, SLOT(insertToTXT()));
}

MainWindow::~MainWindow()
{
#ifndef TEST
    //     Removes the initialized sensor
    manager->removeSensor(lpms_back);
    // Deletes LpmsSensorManager object
    delete manager;
    mpu9150_left_thigh->close();
    mpu9150_left_shank->close();
    mpu9150_right_thigh->close();
    mpu9150_right_shank->close();

#endif
    delete ui;
}

void MainWindow::updateView()
{
#ifndef TEST
    if (lpms_back->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED) {
        // Reads quaternion data
        d = lpms_back->getCurrentData();
        data_buffer[0][0] = d.r[0];
        data_buffer[0][1] = d.r[1];
        data_buffer[0][2] = d.r[2];
    }

    mpu9150_left_thigh->getAngle(&data_buffer[LEFTTHIGH][0], &data_buffer[LEFTTHIGH][1], &data_buffer[LEFTTHIGH][2]);
    mpu9150_right_thigh->getAngle(&data_buffer[RIGHTTHIGH][0], &data_buffer[RIGHTTHIGH][1], &data_buffer[RIGHTTHIGH][2]);
    mpu9150_left_shank->getAngle(&data_buffer[LEFTSHANK][0], &data_buffer[LEFTSHANK][1], &data_buffer[LEFTSHANK][2]);
    mpu9150_right_shank->getAngle(&data_buffer[RIGHTSHANK][0], &data_buffer[RIGHTSHANK][1], &data_buffer[RIGHTSHANK][2]);


#else
    qsrand(qrand());
    for(int row = 0; row < row_Num; row++)
        for(int col = 0; col < col_Num ; col++)
        {

            data_buffer[row][col] = qrand()%360;

        }
#endif
    double back, left_thigh, right_thigh, left_shank, right_shank;



    for(int i = 0; i < 5; i++)
    {
        if(data_buffer[i][0]<0)
            data_buffer[i][0] += 360;
    }


    back = data_buffer[0][0];
    left_thigh = data_buffer[LEFTTHIGH][0];
    right_thigh = data_buffer[RIGHTTHIGH][0];
    left_shank = data_buffer[LEFTSHANK][0];
    right_shank = data_buffer[RIGHTSHANK][0];


    ui->lcdNumber_back->display(back);
    ui->lcdNumber_left_thigh->display(left_thigh);
    ui->lcdNumber_right_thigh->display(right_thigh);
    ui->lcdNumber_left_shank->display(left_shank);
    ui->lcdNumber_right_shank->display(right_shank);


    enum legAngle{left_hip, right_hip, left_knee, right_knee};
    

    angle_data_buffer[left_hip] = -(left_thigh - back);
    angle_data_buffer[right_hip] = -(right_thigh - back);
    angle_data_buffer[left_knee] = left_shank - left_thigh;
    angle_data_buffer[right_knee] = right_shank - right_thigh;

    for(int i = 0; i< 4; i++)
    {
        if(angle_data_buffer[i] > 180)
            angle_data_buffer[i] -= 360;
        else if(angle_data_buffer[i] < -180)
            angle_data_buffer[i] +=360;

    }

    //    QString tmp;
    //    tmp.append("left_hip");
    //    tmp.append(QString::number(left_hip));
    //    tmp.append("right_hip");
    //    tmp.append(QString::number(right_hip));
    //    tmp.append("left_knee");
    //    tmp.append(QString::number(left_knee));
    //    tmp.append("right_knee");
    //    tmp.append(QString::number(right_knee));

    //    ui->textBrowser->append(tmp);





    ui->Dial_left_hip->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_left_hip->setValue(angle_data_buffer[left_hip]);
    ui->Dial_right_hip->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_right_hip->setValue(angle_data_buffer[right_hip]);
    ui->Dial_left_knee->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_left_knee->setValue(angle_data_buffer[left_knee]);
    ui->Dial_right_knee->setNeedle(new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Arrow ,true , Qt::red ));
    ui->Dial_right_knee->setValue(angle_data_buffer[right_knee]);


    ui->lcdNumber_left_hip->display(angle_data_buffer[left_hip]);
    ui->lcdNumber_right_hip->display(angle_data_buffer[right_hip]);
    ui->lcdNumber_left_knee->display(angle_data_buffer[left_knee]);
    ui->lcdNumber_right_knee->display(angle_data_buffer[right_knee]);

    insertToTXT();

}
void MainWindow::on_pushButton_deviceConnect_clicked()
{
    ui->comboBoxIMU_left_shank->setDisabled(true);
    ui->comboBoxIMU_left_thigh->setDisabled(true);
    ui->comboBoxIMU_right_shank->setDisabled(true);
    ui->comboBoxIMU_right_thigh->setDisabled(true);
    ui->pushButton_deviceConnect->setDisabled(true);


#ifndef TEST
    // Gets a LpmsSensorManager instance
    manager = LpmsSensorManagerFactory();
    cout<<"LpmsSensorManagerFactory"<<endl;
    // Connects to LPMS-B sensor with address 00:11:22:33:44:55
    lpms_back = manager->addSensor(DEVICE_LPMS_B, ui->lineEdit_lpmsPortName->text().toLocal8Bit());
    cout<<"addSensor"<<endl;
    lpms_back->getConnectionStatus();


    mpu9150_left_thigh = new MPU_9150();
    bool b_lh  = mpu9150_left_thigh->open(ui->comboBoxIMU_left_thigh->currentText().remove("COM").toInt(), "MPU9150-1.dll");
    ui->textBrowser->append("left_thigh : " + QString::number(ui->comboBoxIMU_left_thigh->currentIndex()));


    mpu9150_right_thigh = new MPU_9150();
    bool b_rh  =mpu9150_right_thigh->open(ui->comboBoxIMU_right_thigh->currentText().remove("COM").toInt(), "MPU9150-2.dll");
    ui->textBrowser->append("right_thigh : " + QString::number(ui->comboBoxIMU_right_thigh->currentIndex()));


    mpu9150_left_shank = new MPU_9150();
    bool b_lk  =mpu9150_left_shank->open(ui->comboBoxIMU_left_shank->currentText().remove("COM").toInt(), "MPU9150-3.dll");
    ui->textBrowser->append("left_shank : " + QString::number(ui->comboBoxIMU_left_shank->currentIndex()));


    mpu9150_right_shank = new MPU_9150();
    bool b_rk  =mpu9150_right_shank->open(ui->comboBoxIMU_right_shank->currentText().remove("COM").toInt(), "MPU9150-4.dll");
    ui->textBrowser->append("right_shank : " + QString::number(ui->comboBoxIMU_right_shank->currentIndex()));

    QString qs_tmp;
    qs_tmp = "Left thigh = ";qs_tmp.append(!b_lh? "OK":"Fail");
    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
    qs_tmp = "Left shank = ";qs_tmp.append(!b_lk? "OK":"Fail");
    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
    qs_tmp = "Right thigh = ";qs_tmp.append(!b_rh? "OK":"Fail");
    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
    qs_tmp = "Right thigh = ";qs_tmp.append(!b_rk? "OK":"Fail");
    ui->textBrowser->append(qs_tmp);qs_tmp.clear();

    if(!b_lh && !b_lk && !b_rh && !b_rk){
        cout<<"ALL device OK"<<endl;
        ui->textBrowser->append("ALL device OK");
        timer_->start();
    }

    ui->pushButton_newFile->setEnabled(true);

#else

    timer_->start();

#endif
}
void MainWindow::insertToTXT()
{
    if(b_saving_file)
    {
        if (file->open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(file);
        //    out << "The magic number is: " << 49 << "\n";
        for(int angle = 0; angle < 4; angle++)
        {
            out <<angle_data_buffer[angle]<<",";
        }


        for(int row = 0; row < row_Num; row++)
            for(int col = 0; col < col_Num ; col++)
            {

                out <<data_buffer[row][col]<<",";

            }

        out <<endl;
    }
}

void MainWindow::on_pushButton_newFile_clicked()
{
    //get current date
    QLocale locale  = QLocale(QLocale::English);
    QDate date = QDate::currentDate();
    QString dateString = locale.toString(date, "yyyyMMdd");
    QTime time = QTime::currentTime();
    QString timeString = locale.toString(time, "hhmmss");
    QString username = ui->lineEdit_username->text();
    QString filepath = "./Data/"+ username + "_" + dateString + "_" + timeString +".txt";
    ui->textBrowser->append(filepath);


    if(timer_->isActive())
    {
        file = new QFile(filepath);
//        timer_file->start();
        b_saving_file = true;

    }else
    {
        ui->textBrowser->append("Please open device first.");

    }

    ui->pushButton_newFile->setDisabled(true);
    ui->pushButton_saveFile->setEnabled(true);
}

void MainWindow::on_pushButton_saveFile_clicked()
{
//    timer_file->stop();
    b_saving_file = false;
    ui->textBrowser->append("File save");
    file->close();

    ui->pushButton_newFile->setEnabled(true);
    ui->pushButton_saveFile->setDisabled(true);


}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_PageUp && ui->pushButton_newFile->isEnabled())
    {
        ui->pushButton_newFile->click();
        ui->textBrowser->append("Recording");
        player->setMedia(QUrl::fromLocalFile("./ding.mp3"));
        player->setVolume(50);
        player->play();
    }
    else if(event->key() == Qt::Key_PageDown && ui->pushButton_saveFile->isEnabled())
    {
        ui->pushButton_saveFile->click();
        ui->textBrowser->append("Recorded OK");
        player->setMedia(QUrl::fromLocalFile("./ding.mp3"));
        player->setVolume(50);
        player->play();

    }

}
