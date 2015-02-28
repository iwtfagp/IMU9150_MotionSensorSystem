#include "mpu_9150.h"

MPU_9150::MPU_9150()
{

}
MPU_9150::~MPU_9150()
{
    CloseCom();
}
bool MPU_9150::open(double port, const char* dll_file)
{

    // Load IMU's dll file, and determint the IMU's functions
    const char* c_mpu1 = dll_file;
    WCHAR w_mpu1[14];
    swprintf(w_mpu1, L"%S", c_mpu1);
    LPCWSTR L_mp1 = w_mpu1;

    IMU_data=LoadLibrary(L_mp1);
    if (IMU_data == NULL)
    {
        QMessageBox::information(0,0,"MPU IMU Dll  Loading Fail =<") ;
    }
    (FARPROC &) OpenCom = GetProcAddress(IMU_data, "OpenCOM");
    (FARPROC &) CloseCom = GetProcAddress(IMU_data, "CloseCOM");
    (FARPROC &) GetAllAngle = GetProcAddress(IMU_data, "GetAllAngles");

    OpenCom(port) ;
    return MPU_OK;
}
void MPU_9150::getAngle(double* _roll, double* _yaw, double* _pitch)
{
    GetAllAngle(_roll, _yaw, _pitch);
}
void MPU_9150::getAngle()
{
    GetAllAngle(&roll, &yaw, &pitch);
}
double MPU_9150::get_roll()
{
    return roll;
}
double MPU_9150::get_yaw()
{
    return yaw;
}
double MPU_9150::get_pitch()
{
    return pitch;
}
