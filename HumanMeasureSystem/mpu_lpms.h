#ifndef MPU_LPMS_H
#define MPU_LPMS_H
#include "LpmsSensorI.h"
#include "LpmsSensorManagerI.h"

class MPU_LPMS
{
public:
    MPU_LPMS();
    ~MPU_LPMS();
    void ConnectIMU(const char* IMU_ID) ;
    void getAngle(void) ;
    double get_roll();
    double get_yaw();
    double get_pitch();

private:
    double roll, yaw, pitch;
    ImuData d;
    LpmsSensorManagerI* manager ;
    LpmsSensorI* lpms ;

};

#endif // MPU_LPMS_H
