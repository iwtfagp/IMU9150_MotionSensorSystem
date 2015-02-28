#ifndef MPU_9150_H
#define MPU_9150_H


#include "Windows.h"
#include <QtWidgets/QMessageBox>

#define MPU_OK 0
#define MPU_ERROR 1


class MPU_9150
{
public:
    MPU_9150();
    bool open(double port, const char *dll_file);
    bool close();
    void getAngle(double* _roll, double* _yaw, double* _pitch);
    void getAngle();
    double roll, yaw, pitch;
private:
    HINSTANCE IMU_data;
    int (*OpenCom)(unsigned short);
    void (*CloseCom)(void);
    void (*GetAllAngle)(double*, double*, double*) ;

};

#endif // MPU_9150_H
