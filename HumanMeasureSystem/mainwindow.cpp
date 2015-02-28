#include "mainwindow.h"
#include "ui_mainwindow.h"



//vector<double> data_buffer[15];
//double **data_buffer = new double[5][3];

//const int row_Num = 5;
//const int col_Num = 3;
//double data_buffer[row_Num][col_Num];

const int data_buffer_number = 15+4;
double data_buffer[data_buffer_number] = {0};

bool dataIn = false;

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


//    mpuLpms_back->getAngle();

//    mpu9150_left_thigh->getAngle();
//    mpu9150_right_thigh->getAngle();
//    mpu9150_left_shank->getAngle();
//    mpu9150_right_shank->getAngle();



    enum LEG_ANGLE{left_hip, right_hip, left_knee, right_knee};
    
//    angle_data_buffer[left_hip] = -(mpu9150_left_thigh->get_roll() - mpuLpms_back->get_roll());
//    angle_data_buffer[right_hip] = -(mpu9150_right_thigh->get_roll() - mpuLpms_back->get_roll());
//    angle_data_buffer[left_knee] = mpu9150_left_shank->get_roll() - mpu9150_left_thigh->get_roll();
//    angle_data_buffer[right_knee] = mpu9150_right_shank->get_roll() - mpu9150_right_thigh->get_roll();

//    for(int i = 0; i< 4; i++)
//    {
//        if(angle_data_buffer[i] > 180)
//            angle_data_buffer[i] -= 360;
//        else if(angle_data_buffer[i] < -180)
//            angle_data_buffer[i] +=360;

//        data_buffer[i] = angle_data_buffer[i];
//    }
//    data_buffer[4] = mpuLpms_back->get_roll();
//    data_buffer[4+1] = mpuLpms_back->get_yaw();
//    data_buffer[4+2] = mpuLpms_back->get_pitch();

//    data_buffer[7] = mpu9150_left_thigh->get_roll();
//    data_buffer[7+1] = mpu9150_left_thigh->get_yaw();
//    data_buffer[7+2] = mpu9150_left_thigh->get_pitch();

//    data_buffer[10] = mpu9150_right_thigh->get_roll();
//    data_buffer[10+1] = mpu9150_right_thigh->get_yaw();
//    data_buffer[10+2] = mpu9150_right_thigh->get_pitch();

//    data_buffer[13] = mpu9150_left_shank->get_roll();
//    data_buffer[13+1] = mpu9150_left_shank->get_yaw();
//    data_buffer[13+2] = mpu9150_left_shank->get_pitch();

//    data_buffer[16] = mpu9150_right_shank->get_roll();
//    data_buffer[16+1] = mpu9150_right_shank->get_yaw();
//    data_buffer[16+2] = mpu9150_right_shank->get_pitch();



    ui->lcdNumber_back->display(data_buffer[4]);
    ui->lcdNumber_left_thigh->display(data_buffer[7]);
    ui->lcdNumber_right_thigh->display(data_buffer[10]);
    ui->lcdNumber_left_shank->display(data_buffer[13]);
    ui->lcdNumber_right_shank->display(data_buffer[16]);

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


//    mpuLpms_back->ConnectIMU(ui->lineEdit_lpmsPortName->text().toLocal8Bit());

//    mpu9150_left_thigh = new MPU_9150();
//    bool b_lh  =mpu9150_left_thigh->open(ui->comboBoxIMU_left_thigh->currentText().remove("COM").toInt(), "MPU9150-1.dll");
//    mpu9150_right_thigh = new MPU_9150();
//    bool b_rh  =mpu9150_right_thigh->open(ui->comboBoxIMU_right_thigh->currentText().remove("COM").toInt(), "MPU9150-2.dll");
//    mpu9150_left_shank = new MPU_9150();
//    bool b_lk  =mpu9150_left_shank->open(ui->comboBoxIMU_left_shank->currentText().remove("COM").toInt(), "MPU9150-3.dll");
//    mpu9150_right_shank = new MPU_9150();
//    bool b_rk  =mpu9150_right_shank->open(ui->comboBoxIMU_right_shank->currentText().remove("COM").toInt(), "MPU9150-4.dll");


//    QString qs_tmp;
//    qs_tmp = "Left thigh = ";qs_tmp.append(!b_lh? "OK":"Fail");
//    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
//    qs_tmp = "Left shank = ";qs_tmp.append(!b_lk? "OK":"Fail");
//    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
//    qs_tmp = "Right thigh = ";qs_tmp.append(!b_rh? "OK":"Fail");
//    ui->textBrowser->append(qs_tmp);qs_tmp.clear();
//    qs_tmp = "Right thigh = ";qs_tmp.append(!b_rk? "OK":"Fail");
//    ui->textBrowser->append(qs_tmp);qs_tmp.clear();

//    if(!b_lh && !b_lk && !b_rh && !b_rk){
//        cout<<"ALL device OK"<<endl;
//        ui->textBrowser->append("ALL device OK");
//        timer_->start();
//    }

    timer_->start();

    ui->pushButton_newFile->setEnabled(true);
    ui->comboBoxIMU_left_shank->setDisabled(true);
    ui->comboBoxIMU_left_thigh->setDisabled(true);
    ui->comboBoxIMU_right_shank->setDisabled(true);
    ui->comboBoxIMU_right_thigh->setDisabled(true);
    ui->pushButton_deviceConnect->setDisabled(true);
}

void MainWindow::insertToTXT_Thread()
{
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::insertToTXT);
    future.waitForFinished();
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
        if(!QDir("Folder").exists())
            QDir().mkdir("Data");
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

void MainWindow::insertToTXT()
{



    if(b_saving_file)
    {
        if (file->open(QFile::WriteOnly | QIODevice::Text)) {
            QTextStream out(file);
            out << "The answer is " << 42;
        }
//        if (!file->open(QIODevice::WriteOnly | QIODevice::Append)){
//        QTextStream out(file);
//        if(!dataIn)
//        {
//            out <<"Left Hip"<<","
//               <<"Right Hip"<<","
//              <<"Left Knee"<<","
//             <<"Right Knee"<<","
//            <<"Back"<<" Roll"<<","<<"Back"<<" yaw"<<","<<"Back"<<" Pitch"<<","
//            <<"Left Thigh"<<" Roll"<<","<<"Left Thigh"<<" yaw"<<","<<"Left Thigh"<<" Pitch"<<","
//            <<"Right Thigh"<<" Roll"<<","<<"Right Thigh"<<" yaw"<<","<<"Right Thigh"<<" Pitch"<<","
//            <<"Left Shank"<<" Roll"<<","<<"Left Shank"<<" yaw"<<","<<"Left Shank"<<" Pitch"<<","
//            <<"Right Shank"<<" Roll"<<","<<"Right Shank"<<" yaw"<<","<<"Right Shank"<<" Pitch"<<endl;
//            dataIn = true;

//        }


////        for(int angle = 0; angle < data_buffer_number; angle++)
////        {
////            out <<data_buffer[angle]<<",";
////        }


////        for(int angle = 0; angle < 4; angle++)
////        {
////            out <<data_buffer[angle]<<",";
////        }


//        out<<1<<endl;
//        }
    }
}

void MainWindow::on_pushButton_saveFile_clicked()
{
    //    timer_file->stop();
    dataIn = false;
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
