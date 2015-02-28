#include "mpu_lpms.h"

MPU_LPMS::MPU_LPMS()
{

}

MPU_LPMS::~MPU_LPMS()
{
    manager->removeSensor(lpms);
    delete manager;
}


void MPU_LPMS::ConnectIMU(const char* IMU_ID)
{
    // Gets a LpmsSensorManager instance
    manager = LpmsSensorManagerFactory();
    // Connects to LPMS-B sensor with address 00:11:22:33:44:55
    lpms = manager->addSensor(DEVICE_LPMS_B, IMU_ID);
    lpms->getConnectionStatus();

}
void MPU_LPMS::getAngle(void)
{
    if (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED) {
        d = lpms->getCurrentData();
        roll = d.r[0];
        yaw = d.r[1];
        pitch = d.r[2];
    }
}

double MPU_LPMS::get_roll()
{
    return roll;
}
double MPU_LPMS::get_yaw()
{
    return yaw;
}
double MPU_LPMS::get_pitch()
{
    return pitch;
}
