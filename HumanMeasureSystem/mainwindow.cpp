#include "mainwindow.h"
#include "ui_mainwindow.h"



//vector<double> data_buffer[15];
//double **data_buffer = new double[5][3];

const int row_Num = 5;
const int col_Num = 3;
double data_buffer[row_Num][col_Num];




//data_buffer[0][0~2] is lpms_data
//data_buffer[1][0~2] is LEFTTHIGH
//data_buffer[2][0~2] is RIGHTTHIGH
//data_buffer[3][0~2] is LEFTSHANK
//data_buffer[4][0~2] is RIGHTSHANK

double angle_data_buffer[4];
bool b_saving_file = false;

double* display_data;

//enum Leg{BACK_REF, LEFT_THIGH, RIGH_TTHIGH, LEFT_SHANK, RIGHT_SHANK};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer; // make sound for remote controler.
    //make com port number list.
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        list.append(info.portName());
    }

    ui->comboBoxIMU_left_shank->addItems(list);
    ui->comboBoxIMU_left_thigh->addItems(list);
    ui->comboBoxIMU_right_shank->addItems(list);
    ui->comboBoxIMU_right_thigh->addItems(list);

    ui->comboBoxIMU_left_thigh->setCurrentText("COM3");
    ui->comboBoxIMU_right_thigh->setCurrentText("COM5");
    ui->comboBoxIMU_left_shank->setCurrentText("COM7");
    ui->comboBoxIMU_right_shank->setCurrentText("COM9");


    timer_ = new QTimer(this);
    timer_->stop();
    timer_->setInterval(20);

    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(updateView()));
    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(insertToTXT_Thread()));


    ui->pushButton_newFile->setDisabled(true);
    ui->pushButton_saveFile->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete mpuLpms_back;
    delete ui;
}

void MainWindow::updateView()
{


    mpuLpms_back->getAngle();

//    if (lpms_back->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED) {
//        // Reads quaternion data
//        d = lpms_back->getCurrentData();
////        back_ref.roll = d.r[0];
////        back_ref.yaw = d.r[1];
////        back_ref.pitch = d.r[2];
//        data_buffer[0][0] = d.r[0];
//        data_buffer[0][1] = d.r[1];
//        data_buffer[0][2] = d.r[2];
//    }

//    mpu9150_left_thigh->getAngle(&data_buffer[LEFTTHIGH][0], &data_buffer[LEFTTHIGH][1], &data_buffer[LEFTTHIGH][2]);
//    mpu9150_right_thigh->getAngle(&data_buffer[RIGHTTHIGH][0], &data_buffer[RIGHTTHIGH][1], &data_buffer[RIGHTTHIGH][2]);
//    mpu9150_left_shank->getAngle(&data_buffer[LEFTSHANK][0], &data_buffer[LEFTSHANK][1], &data_buffer[LEFTSHANK][2]);
//    mpu9150_right_shank->getAngle(&data_buffer[RIGHTSHANK][0], &data_buffer[RIGHTSHANK][1], &data_buffer[RIGHTSHANK][2]);
        mpu9150_left_thigh->getAngle();
        mpu9150_right_thigh->getAngle();
        mpu9150_left_shank->getAngle();
        mpu9150_right_shank->getAngle();


//    int back = data_buffer[0][0];
//    left_thigh = data_buffer[LEFTTHIGH][0];
//    right_thigh = data_buffer[RIGHTTHIGH][0];
//    left_shank = data_buffer[LEFTSHANK][0];
//    right_shank = data_buffer[RIGHTSHANK][0];


    ui->lcdNumber_back->display(mpuLpms_back->get_roll());
    ui->lcdNumber_left_thigh->display(mpu9150_left_thigh->get_roll());
    ui->lcdNumber_right_thigh->display(mpu9150_right_thigh->get_roll());
    ui->lcdNumber_left_shank->display(mpu9150_left_shank->get_roll());
    ui->lcdNumber_right_shank->display(mpu9150_right_shank->get_roll());


    enum legAngle{left_hip, right_hip, left_knee, right_knee};
    

    angle_data_buffer[left_hip] = -(mpu9150_left_thigh->get_roll() - mpuLpms_back->get_roll());
    angle_data_buffer[right_hip] = -(mpu9150_right_thigh->get_roll() - mpuLpms_back->get_roll());
    angle_data_buffer[left_knee] = mpu9150_left_shank->get_roll() - mpu9150_left_thigh->get_roll();
    angle_data_buffer[right_knee] = mpu9150_right_shank->get_roll() - mpu9150_right_thigh->get_roll();

    for(int i = 0; i< 4; i++)
    {
        if(angle_data_buffer[i] > 180)
            angle_data_buffer[i] -= 360;
        else if(angle_data_buffer[i] < -180)
            angle_data_buffer[i] +=360;

    }

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



//    // Gets a LpmsSensorManager instance
//    manager = LpmsSensorManagerFactory();
//    // Connects to LPMS-B sensor with address 00:11:22:33:44:55
//    lpms_back = manager->addSensor(DEVICE_LPMS_B, ui->lineEdit_lpmsPortName->text().toLocal8Bit());
//    lpms_back->getConnectionStatus();
    mpuLpms_back->ConnectIMU(ui->lineEdit_lpmsPortName->text().toLocal8Bit());


    mpu9150_left_thigh = new MPU_9150();
    bool b_lh  =mpu9150_left_thigh->open(ui->comboBoxIMU_left_thigh->currentText().remove("COM").toInt(), "MPU9150-1.dll");

    mpu9150_right_thigh = new MPU_9150();
    bool b_rh  =mpu9150_right_thigh->open(ui->comboBoxIMU_right_thigh->currentText().remove("COM").toInt(), "MPU9150-2.dll");

    mpu9150_left_shank = new MPU_9150();
    bool b_lk  =mpu9150_left_shank->open(ui->comboBoxIMU_left_shank->currentText().remove("COM").toInt(), "MPU9150-3.dll");

    mpu9150_right_shank = new MPU_9150();
    bool b_rk  =mpu9150_right_shank->open(ui->comboBoxIMU_right_shank->currentText().remove("COM").toInt(), "MPU9150-4.dll");


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
}

void MainWindow::insertToTXT_Thread()
{
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::insertToTXT);
    future.waitForFinished();




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
    QString filepath = "./DataXX/"+ username + "_" + dateString + "_" + timeString +".txt";
    ui->textBrowser->append(filepath);


    if(timer_->isActive())
    {
        if(!QDir("Folder").exists())
            QDir().mkdir("DataXX");
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
