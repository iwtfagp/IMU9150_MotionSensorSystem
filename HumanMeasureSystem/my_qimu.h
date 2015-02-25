#ifndef MY_QIMU_H
#define MY_QIMU_H

#include "LpmsSensorI.h"
#include "LpmsSensorManagerI.h"
#include <vector>
#include <ctime>

class My_qIMU
{
public:
    My_qIMU();     // "00:06:66:4B:24:F2"
    ~My_qIMU() ;

    int ConnectIMU(int Try_limit, int TimeOut, const char* IMU_ID) ;
    void GetIMUData(void) ;


public:
    // IMU data
    ImuData d;

    // Gets a LpmsSensorManager instance
    LpmsSensorManagerI* manager ;
    LpmsSensorI* lpms ;

    bool fg_IMU ;

};

#endif // MY_QIMU_H
