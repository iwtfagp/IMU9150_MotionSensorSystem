#include "my_qimu.h"
#include <iostream>
using namespace std;

My_qIMU::My_qIMU()
{
    // Initialize IMU
    fg_IMU = false ;
    manager = LpmsSensorManagerFactory();
}

My_qIMU::~My_qIMU()
{
    delete manager;
}

int My_qIMU::ConnectIMU(int TryLimit, int TimeOut, const char* IMU_ID)
{
    int tmp = -1 ;
    int i_index = -1 ;
    for(int i=0; i< TryLimit; ++i)
    {
        i_index = i ;
        lpms = manager->addSensor(DEVICE_LPMS_B, IMU_ID);
        tmp = lpms->getConnectionStatus() ;
        if(lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTING)
        {
            // delay
            clock_t now = clock() ;
            while((clock() - now) <= TimeOut) ;

            tmp = lpms->getConnectionStatus() ;
            if(lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED)
                break ;
            else
            {
                // remove sensor registration from manager
                manager->removeSensor(lpms);
            }
            cout<<"try"<<endl;
        }
    }

    if(tmp == SENSOR_CONNECTION_CONNECTED)
        fg_IMU = true ;
    else
        fg_IMU = false ;

    return i_index ;

}

void My_qIMU::GetIMUData(void)
{
    d = lpms->getCurrentData() ;
}
